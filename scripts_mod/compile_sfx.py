#!/usr/bin/env python3
import os
import stat
import tempfile
import subprocess
import re
import shutil
from pathlib import Path

def log(msg: str, indent=0):
    indent_padding = " " * indent
    print(f"[{__file__}]:{indent_padding} {msg}")

def wav2aifc(z64audio, vadpcm_enc, wav_path, aiff_callback, aifc_callback):
    with tempfile.TemporaryDirectory() as working_dir:
        c_file = os.path.join(working_dir, "output.c")
        aiff_file = os.path.join(working_dir, "output.aiff")
        aifc_file = os.path.join(working_dir, "output.aifc")
        subprocess.run(
            [z64audio, "-i", wav_path, "-o", aiff_file],
            cwd=working_dir, stdout=subprocess.DEVNULL, stderr=subprocess.DEVNULL
        )
        subprocess.run(
            [z64audio, "-i", aiff_file, "-o", c_file],
            cwd=working_dir, stdout=subprocess.DEVNULL, stderr=subprocess.DEVNULL
        )

        book_active = False
        order, npredictors = None, None
        book = []
        with open(os.path.join(working_dir, c_file)) as c_output:
            for line in c_output.readlines():
                if book_active:
                    if "};" in line:
                        break
                    elif re.match(""".*\d.*""", line):
                        values = re.sub("""\s""", "", line).split(",")
                        book.append([it for it in values if re.match("""-?\d.*""", it)])
                
                if ".order" in line:
                    order = re.sub("""[^\d]""", "", line)
                elif ".npredictors" in line:
                    npredictors = re.sub("""[^\d]""", "", line)
                elif ".book" in line:
                    book_active = True
        
        with tempfile.NamedTemporaryFile() as table:
            table.write(f"{order}\n".encode())
            table.write(f"{npredictors}\n".encode())
            for book_line in book:
                str_line = " ".join(it.rjust(5) for it in book_line)
                table.write(f"{str_line}\n".encode())
            table.seek(0)

            result = subprocess.run(
                [vadpcm_enc, "-c", table.name, aiff_file, aifc_file],
                cwd=working_dir,
                stdout=subprocess.PIPE,
                stderr=subprocess.PIPE,
                text=True
            )

            if "only 1 channel supported" in result.stderr:
                log(f"Error: {os.path.basename(wav_path)} is stereo, but should be mono.")
                return

        aiff_callback(aiff_file)
        aifc_callback(aifc_file)


def find_sfx_wavs(dir_path):
    wav_files = []
    pattern = ".*?\.wav$"
    for filename in os.listdir(dir_path):
        if re.match(pattern, filename):
            log(f"Found WAV file: {filename}")
            wav_files.append(filename)
        else:
            continue
    
    return wav_files

def find_sfx_aifx(dir_path):
    wav_files = []
    pattern = ".*?\.aif.*$"
    for filename in os.listdir(dir_path):
        if re.match(pattern, filename):
            wav_files.append(filename)
        else:
            continue
    
    return wav_files

def main(root):
    z64audio = os.path.join(root, "tools", "bin", "z64audio", "z64audio")
    vadpcm_enc = os.path.join(root, "tools", "sdk-tools", "adpcm", "vadpcm_enc_native")
    mod_assets_samples = os.path.join(root, "mod_assets", "samples")
    assets_samples = os.path.join(root, "assets", "samples")

    # Gets rid of any pesky execution permission errors, hopefully
    st = os.stat(z64audio)
    os.chmod(z64audio, st.st_mode | stat.S_IEXEC)
    st = os.stat(vadpcm_enc)
    os.chmod(vadpcm_enc, st.st_mode | stat.S_IEXEC)

    for src_dir, _, _ in os.walk(mod_assets_samples):
        if src_dir == mod_assets_samples:
            continue
        font_name = os.path.basename(src_dir)
        for wav in find_sfx_wavs(src_dir):
            Path(os.path.join(assets_samples, font_name)).mkdir(parents=True, exist_ok=True)
            wav2aifc(
                z64audio,
                vadpcm_enc,
                wav_path=os.path.join(src_dir, wav),
                aiff_callback=lambda it: shutil.copy2(it, os.path.join(assets_samples, font_name, wav[:-3] + "aiff")),
                aifc_callback=lambda it: shutil.copy2(it, os.path.join(assets_samples, font_name, wav[:-3] + "aifc")),
            )
        for aifx in find_sfx_aifx(src_dir):
            Path(os.path.join(assets_samples, font_name)).mkdir(parents=True, exist_ok=True)
            shutil.copy2(os.path.join(src_dir, aifx), os.path.join(assets_samples, font_name))

if __name__ == "__main__":
    root = os.path.dirname(os.path.realpath(__file__))
    root = os.path.abspath(os.path.join(root, os.pardir))
    main(root)
