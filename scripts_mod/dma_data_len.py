import os
from elftools.elf.elffile import ELFFile
from elftools.elf.sections import SymbolTableSection

def main(elf_path):

    with open(elf_path, "rb") as fd:
        elf = ELFFile(fd)
        dmadata_start, dmadata_end = None, None

        for section in elf.iter_sections():
            if not isinstance(section, SymbolTableSection):
                continue

            for sym in section.iter_symbols():
                if sym.name == "_dmadataSegmentRomStart":
                    dmadata_start = sym['st_value']
                elif sym.name == "_dmadataSegmentRomEnd":
                    dmadata_end = sym['st_value']
                if dmadata_start is not None and dmadata_end is not None:
                    break

    return dmadata_start, (dmadata_end - dmadata_start)//0x10

if __name__ == "__main__":
    root = os.path.dirname(os.path.realpath(__file__))
    root = os.path.abspath(os.path.join(root, os.pardir))
    elf_path = os.path.join(root, "zelda_ocarina_mq_dbg.elf")
    dma_start, dma_len = main(elf_path)
    print(f"0x{dma_start:06X},{dma_len}")
