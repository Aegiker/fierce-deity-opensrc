#!/usr/bin/env python3
"""
copies mod_assets into assets. assumes file is located in `scripts_mod/`
"""
import os
import shutil
import time
import glob
import typing as T
from pathlib import Path
import compile_sfx


def log(msg: str, indent=0):
    indent_padding = " " * indent
    print(f"[{__file__}]:{indent_padding} {msg}")


def remove_stale_assets(files: T.List[str], root: str):
    log(f"Removing stale build objects for {len(files)} file(s)s")
    removed_count = 0
    for file in files:
        rel = os.path.relpath(file, root)
        pattern = os.path.join(root, "build", os.path.dirname(rel), "*")
        for match in glob.glob(pattern, recursive=True):
            os.remove(match)
            removed_count += 1

    log(f"Removed {removed_count} stale object(s) from {root}")


def find_stale_files(files: T.List[str], last_build_time):
    modified_times: T.Dict[str, int] = { file: int(os.path.getmtime(file)) for file in files }
    changed = [file for file, ts in modified_times.items() if ts > last_build_time]
    return changed


def copy_all(root: str) -> T.List[str]:
    src_root = os.path.join(root, "mod_assets")
    dst_root = os.path.join(root, "assets")
    copied_files: T.List[str] = []
    for src_dir, _, file_names in os.walk(src_root):
        #if "mod_assets/samples/" in src_dir:
            # handle samples separately
        #    continue
        #if "mod_assets/midi/" in src_dir or src_dir.endswith("mod_assets/midi"):
            # handle midis separately
        #    continue
        dst_dir = src_dir.replace(src_root, dst_root, 1)
        Path(dst_dir).mkdir(parents=True, exist_ok=True)
        for file_name in file_names:
            src_file = os.path.join(src_dir, file_name)
            dst_file = os.path.join(dst_dir, file_name)
            shutil.copy2(src_file, dst_file)
            copied_files.append(dst_file)

    log(f"Copied {len(copied_files)} file(s) from mod_assets")
    return copied_files


def update_cache_time(root: str) -> int:
    cache_file = os.path.join(root, "build", ".mod_assets_cache")
    if os.path.exists(cache_file):
        with open(cache_file) as fd:
            last_time = int(fd.read().strip())
    else:
        last_time = 0
    
    with open(cache_file, "w") as fd:
        fd.write(f"{int(time.time())}")
        log(f"Updated {cache_file}")
    return last_time


def main():
    root = os.path.dirname(os.path.realpath(__file__))
    root = os.path.abspath(os.path.join(root, os.pardir))
    last_cache_time = update_cache_time(root)

    copied_files = copy_all(root)
    compile_sfx.main(root)


    stale = find_stale_files(copied_files, last_cache_time)
    if len(stale) > 0:
        remove_stale_assets(stale, root)
    else:
        log(f"No stale assets since last build")


if __name__ == "__main__":
    main()