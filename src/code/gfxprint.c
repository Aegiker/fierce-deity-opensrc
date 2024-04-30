#include "global.h"

u16 sGfxPrintFontTLUT[64] = {
    0x0000, 0xFFFF, 0x0000, 0xFFFF, 0x0000, 0xFFFF, 0x0000, 0xFFFF, 0x0000, 0xFFFF, 0x0000, 0xFFFF, 0x0000,
    0xFFFF, 0x0000, 0xFFFF, 0x0000, 0x0000, 0xFFFF, 0xFFFF, 0x0000, 0x0000, 0xFFFF, 0xFFFF, 0x0000, 0x0000,
    0xFFFF, 0xFFFF, 0x0000, 0x0000, 0xFFFF, 0xFFFF, 0x0000, 0x0000, 0x0000, 0x0000, 0xFFFF, 0xFFFF, 0xFFFF,
    0xFFFF, 0x0000, 0x0000, 0x0000, 0x0000, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0x0000, 0x0000, 0x0000, 0x0000,
    0x0000, 0x0000, 0x0000, 0x0000, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF,
};

u16 sGfxPrintRainbowTLUT[16] = {
    0xF801, 0xFBC1, 0xFFC1, 0x07C1, 0x0421, 0x003F, 0x803F, 0xF83F,
    0xF801, 0xFBC1, 0xFFC1, 0x07C1, 0x0421, 0x003F, 0x803F, 0xF83F,
};

u8 sGfxPrintRainbowData[8] = { 0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77 };

u8 sGfxPrintFontData[(16 * 256) / 2] = {
    0x00, 0xDF, 0xFD, 0x00, 0x0A, 0xEE, 0xFF, 0xA0, 0x0D, 0xF2, 0x2D, 0xD0, 0x06, 0x61, 0x1D, 0xC0, 0x01, 0x12, 0x2D,
    0xD0, 0x06, 0x71, 0x99, 0x00, 0x01, 0x1E, 0xED, 0x10, 0x07, 0x7E, 0xF7, 0x00, 0x01, 0x56, 0x29, 0x90, 0x05, 0x58,
    0x97, 0x60, 0x0D, 0xD2, 0x29, 0x90, 0x05, 0x59, 0x97, 0x70, 0x04, 0xDF, 0xFD, 0x40, 0x02, 0x6E, 0xF7, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0xBF, 0xFB, 0x00, 0x0E, 0xFF, 0xFF, 0xC0, 0x0B, 0xF0, 0x0F, 0xB0,
    0x0F, 0xF0, 0x03, 0x30, 0x0F, 0xF0, 0x0F, 0xF0, 0x0F, 0xF0, 0x02, 0x20, 0x0C, 0xFB, 0xBF, 0x60, 0x0F, 0xFC, 0xCE,
    0x20, 0x0D, 0xD4, 0x4F, 0xF0, 0x0F, 0xF0, 0x02, 0x20, 0x0F, 0xF0, 0x0F, 0xF0, 0x0F, 0xF0, 0x03, 0x30, 0x0C, 0xFB,
    0xBF, 0x40, 0x0E, 0xF7, 0x77, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xDF, 0xFD, 0x00, 0x0A,
    0xEE, 0xFF, 0xA0, 0x0D, 0xF2, 0x2D, 0xD0, 0x06, 0x61, 0x1D, 0xC0, 0x01, 0x12, 0x2D, 0xD0, 0x06, 0x71, 0x99, 0x00,
    0x01, 0x1E, 0xED, 0x10, 0x07, 0x7E, 0xF7, 0x00, 0x01, 0x56, 0x29, 0x90, 0x05, 0x58, 0x97, 0x60, 0x0D, 0xD2, 0x29,
    0x90, 0x05, 0x59, 0x97, 0x70, 0x04, 0xDF, 0xFD, 0x40, 0x02, 0x6E, 0xF7, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x08, 0xBF, 0xFB, 0x00, 0x00, 0x0D, 0xE0, 0x00, 0x0B, 0xF0, 0x0F, 0xB0, 0x00, 0x5D, 0xE6, 0x00, 0x0F,
    0xF0, 0x0F, 0xF0, 0x05, 0x5C, 0xC6, 0x60, 0x0C, 0xFB, 0xBF, 0x60, 0x77, 0x3F, 0xF3, 0x77, 0x0D, 0xD4, 0x4F, 0xF0,
    0xBB, 0x3F, 0xF3, 0xBB, 0x0F, 0xF0, 0x0F, 0xF0, 0x09, 0x9C, 0xCA, 0xA0, 0x0C, 0xFB, 0xBF, 0x40, 0x00, 0x9D, 0xEA,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0D, 0xE0, 0x00, 0x04, 0xC2, 0x2C, 0x40, 0x02, 0x8D, 0x50, 0x20, 0x0C, 0xCA,
    0xAC, 0xC0, 0x21, 0xF9, 0x17, 0x10, 0x04, 0xC2, 0x2C, 0x40, 0x12, 0x49, 0x34, 0x00, 0x00, 0x82, 0x08, 0x00, 0x01,
    0x97, 0x51, 0x10, 0x08, 0x8A, 0x88, 0x80, 0x04, 0x61, 0x52, 0x41, 0x00, 0x80, 0x08, 0x00, 0x43, 0x11, 0x75, 0x30,
    0x00, 0xA2, 0x08, 0x00, 0x60, 0x05, 0x56, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x40, 0x00, 0x40, 0x00, 0x22, 0x11,
    0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x0F, 0xB0, 0x00, 0x00, 0x00, 0x08, 0x80, 0x04, 0x0D, 0xA4, 0x00, 0x00, 0x00,
    0x88, 0x00, 0x08, 0xCD, 0xE8, 0x80, 0x02, 0x2A, 0xA2, 0x20, 0x08, 0xCD, 0xE8, 0x80, 0x02, 0xAA, 0x22, 0x20, 0x04,
    0x0D, 0xA4, 0x00, 0x0C, 0xD1, 0x00, 0x00, 0x00, 0x0F, 0xB0, 0x00, 0x8C, 0x51, 0x00, 0x00, 0x00, 0x22, 0x11, 0x00,
    0x81, 0x10, 0x00, 0x00, 0x00, 0xDF, 0xFD, 0x00, 0x0A, 0xEE, 0xFF, 0xA0, 0x0D, 0xF2, 0x2D, 0xD0, 0x06, 0x61, 0x1D,
    0xC0, 0x01, 0x12, 0x2D, 0xD0, 0x06, 0x71, 0x99, 0x00, 0x01, 0x1E, 0xED, 0x10, 0x07, 0x7E, 0xF7, 0x00, 0x01, 0x56,
    0x29, 0x90, 0x05, 0x58, 0x97, 0x60, 0x0D, 0xD2, 0x29, 0x90, 0x05, 0x59, 0x97, 0x70, 0x04, 0xDF, 0xFD, 0x40, 0x02,
    0x6E, 0xF7, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x33, 0x33, 0x00, 0x04, 0x48, 0x99, 0x80,
    0x03, 0x3C, 0xC3, 0x30, 0x00, 0xCD, 0x10, 0x88, 0x03, 0x3C, 0xC3, 0x30, 0x02, 0xBF, 0x62, 0xA8, 0x00, 0x33, 0x33,
    0x20, 0x01, 0x10, 0x4C, 0x80, 0x01, 0x10, 0x03, 0x30, 0x00, 0x15, 0xC8, 0x00, 0x03, 0x3C, 0xC3, 0x30, 0x02, 0x67,
    0x32, 0x20, 0x00, 0x3F, 0xF3, 0x00, 0x04, 0x40, 0x99, 0x00, 0x00, 0x88, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x05,
    0xDF, 0xFD, 0x10, 0x07, 0xFF, 0xFF, 0x60, 0x1C, 0xE0, 0x0E, 0xC1, 0x0F, 0xF0, 0x09, 0x90, 0x1E, 0xE1, 0x16, 0x61,
    0x0F, 0xF0, 0x01, 0x10, 0x1E, 0xF4, 0x56, 0x21, 0x0F, 0xF6, 0x67, 0x10, 0x1E, 0xF2, 0x36, 0x61, 0x0F, 0xF0, 0x89,
    0x90, 0x1E, 0xF1, 0x0F, 0xE1, 0x0F, 0xF0, 0x09, 0x90, 0x16, 0xEC, 0xCE, 0x21, 0x07, 0xFB, 0xBB, 0x20, 0x01, 0x11,
    0x11, 0x10, 0x00, 0x00, 0x00, 0x00, 0x09, 0xB6, 0x6F, 0xD0, 0x27, 0xD8, 0x8E, 0x60, 0x09, 0x92, 0xED, 0x10, 0x2F,
    0xF0, 0x2E, 0xE0, 0x09, 0x9A, 0xE5, 0x10, 0x2F, 0xF6, 0x2E, 0xE0, 0x09, 0x9B, 0x75, 0x10, 0x2F, 0xD6, 0x4E, 0xE0,
    0x0D, 0xDA, 0xE5, 0x10, 0x2F, 0xD0, 0x4E, 0xE0, 0x0D, 0xD2, 0xED, 0x10, 0x2F, 0xD0, 0x0E, 0xE0, 0x09, 0xF6, 0x6F,
    0x90, 0x27, 0xD9, 0x9F, 0x70, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0xFF, 0xFF, 0x00, 0x8F, 0x71,
    0x1F, 0xF0, 0x2F, 0xD0, 0x0F, 0xF0, 0x8F, 0x71, 0x1F, 0xF0, 0x2F, 0xD0, 0x07, 0x70, 0x8E, 0x61, 0x1E, 0xE0, 0x27,
    0xDD, 0xDF, 0x60, 0x8E, 0x69, 0x1E, 0xE0, 0x27, 0x76, 0x4A, 0xA0, 0x8E, 0xE9, 0x9E, 0xE0, 0x2F, 0xD0, 0x6E, 0x80,
    0x8A, 0xE7, 0xFE, 0xA0, 0x07, 0xFA, 0x8E, 0x60, 0x88, 0x27, 0x7A, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x07, 0x7C, 0xCF, 0xF0, 0x13, 0x26, 0x60, 0x11, 0x07, 0x7C, 0xCF, 0xF0, 0x03, 0x76, 0x65, 0x10, 0x02, 0x39,
    0xD7, 0x20, 0x04, 0x53, 0x35, 0x40, 0x00, 0x2F, 0xF2, 0x00, 0x01, 0x13, 0x31, 0x10, 0x00, 0x5F, 0xB1, 0x00, 0x00,
    0x03, 0x30, 0x00, 0x05, 0x5E, 0xE5, 0x50, 0x01, 0x13, 0x31, 0x10, 0x05, 0x5E, 0xED, 0xD0, 0x02, 0x23, 0x30, 0x00,
    0x00, 0x08, 0x88, 0x80, 0x8A, 0xAB, 0xB8, 0x88, 0x00, 0x00, 0x11, 0x00, 0x00, 0x04, 0x45, 0x10, 0x04, 0x62, 0x33,
    0x20, 0x00, 0x44, 0x01, 0x10, 0x04, 0xC8, 0x9A, 0xA0, 0x00, 0xEE, 0xAB, 0x10, 0x0C, 0xE6, 0x67, 0x20, 0x0E, 0xF5,
    0x5F, 0xB0, 0x0E, 0xE0, 0x06, 0x60, 0x0B, 0xF6, 0x2B, 0x90, 0x0E, 0xE0, 0x06, 0x60, 0x03, 0xFC, 0x89, 0x90, 0x04,
    0xEE, 0xEE, 0xA0, 0x00, 0x77, 0x3B, 0xB0, 0x00, 0x00, 0x00, 0x00, 0x08, 0x88, 0x88, 0x00, 0x09, 0x90, 0x00, 0x00,
    0x00, 0x11, 0x10, 0x00, 0x09, 0x92, 0x24, 0x40, 0x00, 0x01, 0x10, 0x00, 0x09, 0x90, 0x88, 0x00, 0x26, 0xEF, 0xDE,
    0x20, 0x09, 0x9B, 0xB5, 0x40, 0x2E, 0xC3, 0x3C, 0xE2, 0x0D, 0x9A, 0x25, 0x50, 0x2E, 0xC3, 0x3C, 0xE2, 0x0D, 0xDA,
    0xA5, 0x50, 0x2E, 0xC3, 0x3C, 0xE2, 0x09, 0xD6, 0xED, 0x10, 0x26, 0xCB, 0xBC, 0x62, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x10, 0x00,
    0x05, 0xFB, 0xFF, 0xE0, 0x8E, 0x61, 0x16, 0xE8, 0x0F, 0xF4, 0x03, 0x30, 0x8F, 0x71, 0x17, 0xF8, 0x07, 0xFC, 0x8B,
    0x30, 0x8E, 0x69, 0x96, 0xE8, 0x05, 0x73, 0x3B, 0xA0, 0x8A, 0x6D, 0xD6, 0xA8, 0x0D, 0xD8, 0x8A, 0x20, 0x08, 0xA7,
    0x79, 0xB2, 0x01, 0x10, 0x02, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x8A, 0x01, 0x10, 0x00, 0x00,
    0x00, 0x08, 0x00, 0x80, 0xA1, 0x10, 0x00, 0x07, 0x74, 0x4F, 0x70, 0x80, 0xA9, 0x90, 0x00, 0x02, 0x31, 0xDF, 0x20,
    0x84, 0xE6, 0x00, 0x04, 0x00, 0x27, 0xDA, 0x20, 0xC8, 0xAA, 0x4C, 0x40, 0x00, 0x57, 0x3B, 0x20, 0x00, 0xA1, 0x18,
    0x00, 0x05, 0x54, 0x6F, 0x50, 0x00, 0xA9, 0x98, 0x00, 0x02, 0x22, 0x20, 0x80, 0x02, 0x00, 0x18, 0x88, 0x00, 0x04,
    0x44, 0x40, 0x00, 0x04, 0x00, 0x00, 0x00, 0x04, 0x44, 0x40, 0x0C, 0x44, 0x44, 0x00, 0x00, 0x04, 0x40, 0x00, 0x88,
    0xC0, 0x00, 0x00, 0x00, 0x0C, 0xC0, 0x00, 0x0C, 0x46, 0xA4, 0x40, 0x00, 0x0C, 0xC0, 0x00, 0x08, 0x8E, 0xE0, 0x00,
    0x02, 0x08, 0x80, 0x00, 0x80, 0xD0, 0x88, 0x00, 0x28, 0xA8, 0x80, 0x00, 0x88, 0xCD, 0x4C, 0x40, 0x0A, 0x88, 0x80,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x06, 0xE0, 0x08, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x08, 0x88, 0x00, 0x80, 0x01, 0x06, 0x10, 0x00, 0x56, 0xE7, 0x50, 0x80, 0x02, 0x1F, 0xF1, 0x00, 0x38,
    0x8C, 0xB8, 0x00, 0x0B, 0xF6, 0x0B, 0x00, 0x94, 0xC0, 0x28, 0x00, 0x06, 0x07, 0x6A, 0x00, 0xCB, 0xA6, 0xC8, 0x00,
    0x00, 0x47, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0A, 0x80, 0x00, 0x00, 0x39, 0x14,
    0x20, 0x02, 0x22, 0x24, 0x00, 0x08, 0xAE, 0xA8, 0x60, 0x04, 0x28, 0x99, 0x70, 0x07, 0x75, 0xD1, 0x04, 0x0F, 0xB3,
    0x33, 0xD0, 0x00, 0xAE, 0xBE, 0xA4, 0x25, 0x15, 0x20, 0xA0, 0x02, 0x61, 0x0C, 0x02, 0x20, 0x42, 0x08, 0x20, 0x2C,
    0x30, 0x14, 0x02, 0x02, 0x28, 0x82, 0x00, 0x03, 0xAC, 0xC1, 0x30, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x08, 0x12, 0x00, 0x08, 0x00, 0x28, 0x00, 0x0A, 0xCF, 0xEE, 0x20, 0x0B, 0x62, 0x2E, 0x20, 0x02, 0x10, 0x82,
    0x40, 0x01, 0x44, 0xE4, 0x40, 0x03, 0x00, 0x0E, 0x00, 0x8D, 0xEA, 0xAC, 0x00, 0x02, 0x10, 0x0A, 0x00, 0x01, 0xE0,
    0x24, 0x00, 0x0C, 0x21, 0x02, 0x00, 0x09, 0x42, 0x21, 0x00, 0x00, 0xCC, 0xF4, 0x40, 0x02, 0xBF, 0xD4, 0x40, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x44, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x44, 0x40,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x40, 0x00, 0x0C, 0xCC, 0xC4, 0x40, 0x00, 0x0C, 0xC0, 0x00, 0x00, 0x02, 0xA0,
    0x40, 0x00, 0x0C, 0xC0, 0x00, 0x04, 0xCE, 0x64, 0x40, 0x02, 0x08, 0x80, 0x00, 0x00, 0x90, 0x00, 0x40, 0x28, 0xA8,
    0x80, 0x00, 0x08, 0x01, 0x04, 0x00, 0x0A, 0x88, 0x80, 0x00, 0x04, 0x44, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x29, 0x00, 0x00, 0x00, 0x54, 0x44, 0x00,
    0xEE, 0xFE, 0xE0, 0x00, 0x09, 0x3B, 0x3F, 0x00, 0x21, 0xD8, 0x20, 0x00, 0x00, 0x54, 0x4F, 0x00, 0x18, 0x58, 0x20,
    0x00, 0x00, 0x01, 0x86, 0x00, 0xC6, 0x7E, 0x40, 0x00, 0x00, 0xEF, 0x66, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x80, 0x04, 0x00, 0x00, 0xC0, 0x20, 0x00, 0xAA, 0xAA, 0xEA, 0x20, 0xEF, 0xFF, 0xFF, 0x00, 0x80,
    0x44, 0x19, 0x30, 0x00, 0x49, 0x24, 0x00, 0xC5, 0x35, 0x1B, 0x10, 0x00, 0x4B, 0x24, 0x00, 0x01, 0x35, 0xA0, 0x00,
    0x8C, 0xA9, 0xAC, 0x80, 0x00, 0x2C, 0x00, 0x00, 0x04, 0x21, 0xA4, 0x00, 0x2A, 0x84, 0x00, 0x00, 0x73, 0x11, 0xF1,
    0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0B, 0x11, 0x19, 0x00, 0x00, 0x40, 0x00, 0x00, 0x8F, 0xEE,
    0xEF, 0xE0, 0x0B, 0x76, 0x66, 0xD0, 0x1A, 0x00, 0x0B, 0x40, 0x4C, 0x40, 0x02, 0xD0, 0x28, 0x00, 0x1A, 0x40, 0x01,
    0xD0, 0x2C, 0x10, 0x00, 0x00, 0x38, 0x40, 0x00, 0x40, 0x28, 0x10, 0x00, 0x01, 0xA0, 0x40, 0x00, 0x42, 0x83, 0x00,
    0x05, 0xFE, 0x44, 0x40, 0x03, 0xFD, 0x54, 0x60, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x09, 0x99, 0x9B,
    0x00, 0x00, 0x10, 0x20, 0x00, 0x07, 0x26, 0x21, 0x40, 0x2A, 0xFE, 0xEE, 0xA0, 0x8D, 0x8C, 0xA9, 0xC0, 0x00, 0x10,
    0x20, 0x80, 0x32, 0x33, 0xB3, 0x60, 0x00, 0x19, 0x28, 0x00, 0x00, 0x00, 0xA1, 0x40, 0x00, 0x10, 0xB1, 0x00, 0x00,
    0x08, 0x34, 0x00, 0x00, 0x1A, 0x08, 0x00, 0x05, 0xF7, 0x40, 0x00, 0x8E, 0xF4, 0x44, 0xC0, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x08, 0x14, 0x02, 0x80, 0x00, 0x04, 0x00, 0x00, 0x1D, 0x11, 0xDB, 0x00, 0xDD, 0xFD, 0xDD,
    0xD0, 0x0C, 0x88, 0x07, 0x00, 0x02, 0x06, 0x00, 0x90, 0x48, 0x00, 0x34, 0x00, 0x2C, 0x04, 0x2C, 0x10, 0x48, 0x11,
    0x21, 0x40, 0x04, 0x84, 0x83, 0x40, 0x59, 0x03, 0x00, 0x50, 0x40, 0x0C, 0x10, 0x60, 0x42, 0xA9, 0x88, 0xC0, 0x40,
    0x15, 0x80, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x11, 0x02, 0x00, 0x40, 0x08, 0x98, 0x88, 0x80,
    0x08, 0xF9, 0x98, 0xC0, 0x06, 0x77, 0x75, 0x50, 0x02, 0x0C, 0x05, 0x00, 0x19, 0x98, 0xA8, 0xD0, 0x0B, 0x99, 0xCA,
    0x80, 0x04, 0x54, 0x65, 0xC0, 0x20, 0x08, 0x50, 0x20, 0x00, 0x10, 0x20, 0xC0, 0x31, 0x1C, 0x04, 0x20, 0x00, 0x01,
    0x28, 0x40, 0x26, 0x63, 0xBB, 0xE0, 0x26, 0xEF, 0xE6, 0x60, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01,
    0x02, 0x01, 0x00, 0xC8, 0xC0, 0x00, 0x00, 0x0F, 0x8A, 0x89, 0x80, 0xC3, 0xF3, 0x11, 0x30, 0x0F, 0x02, 0x01, 0x80,
    0xC9, 0xC0, 0x00, 0x30, 0x0F, 0x02, 0x05, 0xA0, 0x00, 0x00, 0x00, 0x30, 0x0E, 0x02, 0x05, 0xA0, 0x00, 0x00, 0x00,
    0x30, 0x0E, 0x02, 0x52, 0x80, 0x00, 0x00, 0x03, 0x00, 0x2C, 0xDF, 0xA8, 0x80, 0x02, 0x33, 0x30, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x88, 0x00, 0x01, 0x02, 0x80, 0x00, 0x03, 0xFF, 0xF7, 0x00, 0x0F,
    0x26, 0xE4, 0x72, 0xCC, 0x38, 0x00, 0x40, 0x0C, 0x38, 0x99, 0x00, 0x03, 0x0A, 0x31, 0x50, 0x0C, 0xB1, 0x82, 0x80,
    0x03, 0x28, 0x06, 0x00, 0x87, 0x88, 0x2A, 0xA0, 0x01, 0x05, 0xC2, 0x00, 0x85, 0x82, 0xC2, 0x80, 0x10, 0x00, 0x39,
    0x10, 0x08, 0x51, 0xBF, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x04, 0x00, 0x48, 0x9D,
    0xCC, 0x40, 0xC9, 0xE6, 0x7F, 0x40, 0x40, 0x00, 0x94, 0x00, 0x5B, 0x21, 0x0C, 0xB0, 0x48, 0xAE, 0xCC, 0x40, 0xE1,
    0x30, 0x0C, 0x30, 0x43, 0x01, 0xA4, 0x00, 0xE1, 0x24, 0x5D, 0x30, 0x78, 0x8C, 0xD6, 0x10, 0xF1, 0x60, 0x94, 0x70,
    0xD0, 0x40, 0x9C, 0x70, 0x0B, 0x8C, 0x53, 0x00, 0x0C, 0x9D, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x01, 0x39, 0x50, 0x00, 0x00, 0x88, 0xF0, 0x00, 0x2E, 0xAF, 0xC6, 0x00, 0x03, 0x01, 0x77, 0x60, 0x04, 0xF0,
    0x41, 0x60, 0x03, 0x92, 0xF8, 0x12, 0x0F, 0xBD, 0x91, 0x40, 0x1B, 0x28, 0x60, 0x92, 0x70, 0xF4, 0x01, 0xF0, 0x0A,
    0xD4, 0x65, 0x82, 0x53, 0xE0, 0x01, 0xE0, 0x04, 0x10, 0x68, 0x60, 0x04, 0x2A, 0xBE, 0x00, 0x00, 0x4F, 0x80, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x3A, 0xEE, 0x00, 0xC8, 0xC0, 0x00, 0x00, 0x0D, 0x84, 0xA5,
    0x00, 0xC1, 0xC2, 0x11, 0x00, 0x45, 0x0E, 0x27, 0x00, 0xD9, 0xC3, 0x00, 0x10, 0x07, 0xF8, 0x8D, 0x20, 0x01, 0x30,
    0x00, 0x10, 0xAC, 0x02, 0x25, 0xA0, 0x01, 0x22, 0x00, 0x10, 0x44, 0x20, 0x16, 0xA0, 0x13, 0x02, 0x00, 0x30, 0x04,
    0x1B, 0xAA, 0x40, 0x21, 0x00, 0x23, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};

// Can be used to set GFXP_FLAG_ENLARGE by default
static u8 sDefaultSpecialFlags;

void GfxPrint_Setup(GfxPrint* this) {
    s32 width = 16;
    s32 height = 256;
    s32 i;

    gDPPipeSync(this->dList++);
    gDPSetOtherMode(this->dList++,
                    G_AD_DISABLE | G_CD_DISABLE | G_CK_NONE | G_TC_FILT | G_TF_BILERP | G_TT_IA16 | G_TL_TILE |
                        G_TD_CLAMP | G_TP_NONE | G_CYC_1CYCLE | G_PM_NPRIMITIVE,
                    G_AC_NONE | G_ZS_PRIM | G_RM_XLU_SURF | G_RM_XLU_SURF2);
    gDPSetCombineMode(this->dList++, G_CC_DECALRGBA, G_CC_DECALRGBA);
    gDPLoadTextureBlock_4b(this->dList++, sGfxPrintFontData, G_IM_FMT_CI, width, height, 0, G_TX_NOMIRROR | G_TX_WRAP,
                           G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
    gDPLoadTLUT(this->dList++, 64, 0x100, sGfxPrintFontTLUT);

    for (i = 1; i < 4; i++) {
        gDPSetTile(this->dList++, G_IM_FMT_CI, G_IM_SIZ_4b, 1, 0, i * 2, i, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK,
                   G_TX_NOLOD, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOLOD);
        gDPSetTileSize(this->dList++, i * 2, 0, 0, 15 << 2, 255 << 2);
    }

    gDPSetColor(this->dList++, G_SETPRIMCOLOR, this->color.rgba);

    gDPLoadMultiTile_4b(this->dList++, sGfxPrintRainbowData, 0, 1, G_IM_FMT_CI, 2, 8, 0, 0, 1, 7, 4,
                        G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, 1, 3, G_TX_NOLOD, G_TX_NOLOD);

    gDPLoadTLUT(this->dList++, 16, 0x140, sGfxPrintRainbowTLUT);

    for (i = 1; i < 4; i++) {
        gDPSetTile(this->dList++, G_IM_FMT_CI, G_IM_SIZ_4b, 1, 0, i * 2 + 1, 4, G_TX_NOMIRROR | G_TX_WRAP, 3,
                   G_TX_NOLOD, G_TX_NOMIRROR | G_TX_WRAP, 1, G_TX_NOLOD);
        gDPSetTileSize(this->dList++, i * 2 + 1, 0, 0, 1 << 2, 7 << 2);
    }
}

void GfxPrint_SetColor(GfxPrint* this, u32 r, u32 g, u32 b, u32 a) {
    this->color.r = r;
    this->color.g = g;
    this->color.b = b;
    this->color.a = a;
    gDPPipeSync(this->dList++);
    gDPSetColor(this->dList++, G_SETPRIMCOLOR, this->color.rgba);
}

void GfxPrint_SetPosPx(GfxPrint* this, s32 x, s32 y) {
    this->posX = this->baseX + (x << 2);
    this->posY = this->baseY + (y << 2);
}

void GfxPrint_SetPos(GfxPrint* this, s32 x, s32 y) {
    GfxPrint_SetPosPx(this, x * GFX_CHAR_X_SPACING, y * GFX_CHAR_Y_SPACING);
}

void GfxPrint_SetBasePosPx(GfxPrint* this, s32 x, s32 y) {
    this->baseX = x << 2;
    this->baseY = y << 2;
}

void GfxPrint_PrintCharImpl(GfxPrint* this, u8 c) {
    u32 tile = (c & 0xFF) * 2;

    if (this->flags & GFXP_FLAG_UPDATE) {
        this->flags &= ~GFXP_FLAG_UPDATE;

        gDPPipeSync(this->dList++);
        if (this->flags & GFXP_FLAG_RAINBOW) {
            gDPSetTextureLUT(this->dList++, G_TT_RGBA16);
            gDPSetCycleType(this->dList++, G_CYC_2CYCLE);
            gDPSetRenderMode(this->dList++, G_RM_PASS, G_RM_XLU_SURF2);
            gDPSetCombineMode(this->dList++, G_CC_INTERFERENCE, G_CC_PASS2);
        } else {
            gDPSetTextureLUT(this->dList++, G_TT_IA16);
            gDPSetCycleType(this->dList++, G_CYC_1CYCLE);
            gDPSetRenderMode(this->dList++, G_RM_XLU_SURF, G_RM_XLU_SURF2);
            gDPSetCombineMode(this->dList++, G_CC_MODULATEIDECALA_PRIM, G_CC_MODULATEIDECALA_PRIM);
        }
    }

    if (this->flags & GFXP_FLAG_SHADOW) {
        gDPSetColor(this->dList++, G_SETPRIMCOLOR, 0);

        if (this->flags & GFXP_FLAG_ENLARGE) {
            gSPTextureRectangle(this->dList++, (this->posX + 4) << 1, (this->posY + 4) << 1, (this->posX + 4 + 32) << 1,
                                (this->posY + 4 + 32) << 1, tile, (u16)(c & 4) * 64, (u16)(c >> 3) * 256, 1 << 9,
                                1 << 9);
        } else {
            gSPTextureRectangle(this->dList++, this->posX + 4, this->posY + 4, this->posX + 4 + 32, this->posY + 4 + 32,
                                tile, (u16)(c & 4) * 64, (u16)(c >> 3) * 256, 1 << 10, 1 << 10);
        }

        gDPSetColor(this->dList++, G_SETPRIMCOLOR, this->color.rgba);
    }

    if (this->flags & GFXP_FLAG_ENLARGE) {
        gSPTextureRectangle(this->dList++, this->posX << 1, this->posY << 1, (this->posX + 32) << 1,
                            (this->posY + 32) << 1, tile, (u16)(c & 4) * 64, (u16)(c >> 3) * 256, 1 << 9, 1 << 9);
    } else {
        gSPTextureRectangle(this->dList++, this->posX, this->posY, this->posX + 32, this->posY + 32, tile,
                            (u16)(c & 4) * 64, (u16)(c >> 3) * 256, 1 << 10, 1 << 10);
    }

    this->posX += GFX_CHAR_X_SPACING << 2;
}

void GfxPrint_PrintChar(GfxPrint* this, u8 c) {
    u8 charParam = c;

    if (c == ' ') {
        this->posX += GFX_CHAR_X_SPACING << 2;
    } else if (c > ' ' && c < 0x7F) {
        GfxPrint_PrintCharImpl(this, charParam);
    } else if (c >= 0xA0 && c < 0xE0) {
        if (this->flags & GFXP_FLAG_HIRAGANA) {
            if (c < 0xC0) {
                charParam = c - 0x20;
            } else {
                charParam = c + 0x20;
            }
        }
        GfxPrint_PrintCharImpl(this, charParam);
    } else {
        switch (c) {
            case '\0':
                break;
            case '\n':
                this->posY += GFX_CHAR_Y_SPACING << 2;
                FALLTHROUGH;
            case '\r':
                this->posX = this->baseX;
                break;
            case '\t':
                do {
                    GfxPrint_PrintCharImpl(this, ' ');
                } while ((this->posX - this->baseX) % 256);
                break;
            case GFXP_HIRAGANA_CHAR:
                this->flags |= GFXP_FLAG_HIRAGANA;
                break;
            case GFXP_KATAKANA_CHAR:
                this->flags &= ~GFXP_FLAG_HIRAGANA;
                break;
            case GFXP_RAINBOW_ON_CHAR:
                this->flags |= GFXP_FLAG_RAINBOW;
                this->flags |= GFXP_FLAG_UPDATE;
                break;
            case GFXP_RAINBOW_OFF_CHAR:
                this->flags &= ~GFXP_FLAG_RAINBOW;
                this->flags |= GFXP_FLAG_UPDATE;
                break;
            case GFXP_UNUSED_CHAR:
            default:
                break;
        }
    }
}

void GfxPrint_PrintStringWithSize(GfxPrint* this, const void* buffer, u32 charSize, u32 charCount) {
    const char* str = (const char*)buffer;
    u32 count = charSize * charCount;

    while (count != 0) {
        GfxPrint_PrintChar(this, *(str++));
        count--;
    }
}

void GfxPrint_PrintString(GfxPrint* this, const char* str) {
    while (*str != '\0') {
        GfxPrint_PrintChar(this, *(str++));
    }
}

void* GfxPrint_Callback(void* arg, const char* str, u32 size) {
    GfxPrint* this = arg;

    GfxPrint_PrintStringWithSize(this, str, sizeof(char), size);

    return this;
}

void GfxPrint_Init(GfxPrint* this) {
    this->flags &= ~GFXP_FLAG_OPEN;

    this->callback = GfxPrint_Callback;
    this->dList = NULL;
    this->posX = 0;
    this->posY = 0;
    this->baseX = 0;
    this->baseY = 0;
    this->color.rgba = 0;

    this->flags &= ~GFXP_FLAG_HIRAGANA;
    this->flags &= ~GFXP_FLAG_RAINBOW;
    this->flags |= GFXP_FLAG_SHADOW;
    this->flags |= GFXP_FLAG_UPDATE;

    if (sDefaultSpecialFlags & GFXP_FLAG_ENLARGE) {
        this->flags |= GFXP_FLAG_ENLARGE;
    } else {
        this->flags &= ~GFXP_FLAG_ENLARGE;
    }
}

void GfxPrint_Destroy(GfxPrint* this) {
}

void GfxPrint_Open(GfxPrint* this, Gfx* dList) {
    if (!(this->flags & GFXP_FLAG_OPEN)) {
        this->flags |= GFXP_FLAG_OPEN;
        this->dList = dList;
        GfxPrint_Setup(this);
    } else {
        osSyncPrintf("gfxprint_open:２重オープンです\n");
    }
}

Gfx* GfxPrint_Close(GfxPrint* this) {
    Gfx* ret;

    this->flags &= ~GFXP_FLAG_OPEN;
    gDPPipeSync(this->dList++);
    ret = this->dList;
    this->dList = NULL;

    return ret;
}

s32 GfxPrint_VPrintf(GfxPrint* this, const char* fmt, va_list args) {
    return PrintUtils_VPrintf(&this->callback, fmt, args);
}

s32 GfxPrint_Printf(GfxPrint* this, const char* fmt, ...) {
    s32 ret;
    va_list args;
    va_start(args, fmt);

    ret = GfxPrint_VPrintf(this, fmt, args);

    va_end(args);

    return ret;
}