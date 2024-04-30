#include "ultra64.h"
#include "z64.h"
#include "macros.h"
#include "object_mask_deity.h"
#include "assets/misc/link_animetion/link_animetion.h"
#include "assets/objects/gameplay_keep/gameplay_keep.h"

Vtx object_mask_deityVtx_000000[] = {
#include "assets/objects/object_mask_deity/object_mask_deityVtx_000000.vtx.inc"
};

Gfx object_mask_deity_DL_000900[] = {
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPPipeSync(),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPSetTextureLUT(G_TT_RGBA16),
    gsDPLoadTLUT_pal256(object_mask_deity_TLUT_000D50),
    gsDPLoadTextureBlock(object_mask_deity_Tex_000F50, G_IM_FMT_CI, G_IM_SIZ_8b, 32, 32, 0, G_TX_NOMIRROR | G_TX_WRAP,
                         G_TX_NOMIRROR | G_TX_WRAP, 5, 5, G_TX_NOLOD, G_TX_NOLOD),
    gsDPSetPrimColor(0, 0x80, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(object_mask_deityVtx_000000, 32, 0),
    gsSP2Triangles(0, 1, 2, 0, 3, 4, 5, 0),
    gsSP2Triangles(3, 6, 4, 0, 7, 3, 5, 0),
    gsSP2Triangles(7, 8, 3, 0, 9, 10, 11, 0),
    gsSP2Triangles(12, 13, 14, 0, 15, 16, 17, 0),
    gsSP2Triangles(16, 18, 19, 0, 15, 18, 16, 0),
    gsSP2Triangles(15, 8, 20, 0, 21, 8, 15, 0),
    gsSP2Triangles(22, 4, 6, 0, 13, 23, 14, 0),
    gsSP2Triangles(24, 25, 26, 0, 27, 25, 24, 0),
    gsSP2Triangles(27, 28, 25, 0, 20, 8, 7, 0),
    gsSP2Triangles(29, 9, 30, 0, 31, 14, 23, 0),
    gsSPVertex(&object_mask_deityVtx_000000[32], 28, 0),
    gsSP2Triangles(0, 1, 2, 0, 2, 1, 3, 0),
    gsSP2Triangles(3, 4, 5, 0, 6, 7, 8, 0),
    gsSP2Triangles(9, 10, 11, 0, 10, 12, 11, 0),
    gsSP2Triangles(13, 8, 7, 0, 14, 13, 7, 0),
    gsSP2Triangles(15, 3, 16, 0, 4, 17, 18, 0),
    gsSP2Triangles(19, 17, 4, 0, 19, 20, 17, 0),
    gsSP2Triangles(16, 3, 1, 0, 21, 3, 15, 0),
    gsSP2Triangles(11, 22, 9, 0, 23, 24, 16, 0),
    gsSP2Triangles(25, 10, 9, 0, 5, 26, 2, 0),
    gsSP1Triangle(13, 27, 8, 0),
    gsDPPipeSync(),
    gsDPLoadTLUT_pal256(object_mask_deity_TLUT_000D50),
    gsDPLoadTextureBlock(object_mask_deity_Tex_001350, G_IM_FMT_CI, G_IM_SIZ_8b, 64, 32, 0, G_TX_NOMIRROR | G_TX_CLAMP,
                         G_TX_NOMIRROR | G_TX_CLAMP, 6, 5, G_TX_NOLOD, G_TX_NOLOD),
    gsSPVertex(&object_mask_deityVtx_000000[60], 32, 0),
    gsSP2Triangles(0, 1, 2, 0, 0, 3, 1, 0),
    gsSP2Triangles(4, 5, 1, 0, 1, 6, 4, 0),
    gsSP2Triangles(1, 3, 6, 0, 3, 7, 6, 0),
    gsSP2Triangles(1, 8, 9, 0, 10, 8, 1, 0),
    gsSP2Triangles(11, 8, 10, 0, 10, 5, 11, 0),
    gsSP2Triangles(1, 5, 10, 0, 12, 1, 9, 0),
    gsSP2Triangles(2, 1, 12, 0, 13, 2, 12, 0),
    gsSP2Triangles(14, 15, 16, 0, 16, 17, 14, 0),
    gsSP2Triangles(17, 18, 14, 0, 17, 16, 19, 0),
    gsSP2Triangles(14, 20, 15, 0, 15, 21, 16, 0),
    gsSP2Triangles(22, 8, 11, 0, 11, 5, 23, 0),
    gsSP2Triangles(22, 24, 8, 0, 8, 24, 9, 0),
    gsSP2Triangles(9, 24, 25, 0, 25, 12, 9, 0),
    gsSP2Triangles(25, 13, 12, 0, 13, 25, 26, 0),
    gsSP2Triangles(15, 20, 26, 0, 20, 13, 26, 0),
    gsSP2Triangles(15, 26, 27, 0, 15, 27, 21, 0),
    gsSP2Triangles(28, 29, 30, 0, 31, 28, 30, 0),
    gsSPVertex(&object_mask_deityVtx_000000[92], 15, 0),
    gsSP2Triangles(0, 1, 2, 0, 2, 3, 0, 0),
    gsSP2Triangles(4, 3, 2, 0, 4, 5, 3, 0),
    gsSP2Triangles(5, 4, 6, 0, 4, 7, 6, 0),
    gsSP2Triangles(8, 2, 1, 0, 8, 1, 9, 0),
    gsSP2Triangles(10, 11, 12, 0, 13, 10, 12, 0),
    gsSP1Triangle(6, 7, 14, 0),
    gsDPPipeSync(),
    gsDPLoadTLUT_pal256(object_mask_deity_TLUT_000D50),
    gsDPLoadTextureBlock(object_mask_deity_Tex_001B50, G_IM_FMT_CI, G_IM_SIZ_8b, 32, 32, 0, G_TX_NOMIRROR | G_TX_CLAMP,
                         G_TX_NOMIRROR | G_TX_CLAMP, 5, 5, G_TX_NOLOD, G_TX_NOLOD),
    gsSPVertex(&object_mask_deityVtx_000000[107], 8, 0),
    gsSP2Triangles(0, 1, 2, 0, 3, 0, 4, 0),
    gsSP2Triangles(1, 0, 3, 0, 1, 3, 5, 0),
    gsSP2Triangles(6, 5, 3, 0, 3, 4, 6, 0),
    gsSP1Triangle(6, 7, 5, 0),
    gsDPPipeSync(),
    gsDPLoadTLUT_pal256(object_mask_deity_TLUT_000D50),
    gsDPLoadTextureBlock(object_mask_deity_Tex_001F50, G_IM_FMT_CI, G_IM_SIZ_8b, 16, 16, 0, G_TX_NOMIRROR | G_TX_CLAMP,
                         G_TX_NOMIRROR | G_TX_CLAMP, 4, 4, G_TX_NOLOD, G_TX_NOLOD),
    gsSPVertex(&object_mask_deityVtx_000000[115], 14, 0),
    gsSP2Triangles(0, 1, 2, 0, 3, 4, 5, 0),
    gsSP2Triangles(5, 6, 3, 0, 3, 7, 4, 0),
    gsSP2Triangles(8, 9, 10, 0, 10, 11, 12, 0),
    gsSP2Triangles(12, 8, 10, 0, 13, 1, 0, 0),
    gsDPPipeSync(),
    gsDPSetTextureLUT(G_TT_NONE),
    gsDPLoadTextureBlock(object_mask_deity_Tex_002050, G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 8, 0, G_TX_NOMIRROR | G_TX_CLAMP,
                         G_TX_NOMIRROR | G_TX_CLAMP, 3, 3, G_TX_NOLOD, G_TX_NOLOD),
    gsSPVertex(&object_mask_deityVtx_000000[129], 15, 0),
    gsSP2Triangles(0, 1, 2, 0, 0, 3, 1, 0),
    gsSP2Triangles(4, 5, 6, 0, 7, 6, 8, 0),
    gsSP2Triangles(6, 5, 8, 0, 0, 5, 4, 0),
    gsSP2Triangles(0, 4, 9, 0, 5, 0, 2, 0),
    gsSP2Triangles(0, 9, 3, 0, 8, 5, 2, 0),
    gsSP2Triangles(10, 7, 8, 0, 11, 10, 8, 0),
    gsSP2Triangles(2, 11, 8, 0, 12, 3, 9, 0),
    gsSP2Triangles(7, 10, 13, 0, 4, 6, 14, 0),
    gsSPEndDisplayList(),
};

u64 object_mask_deity_TLUT_000D50[] = {
#include "assets/objects/object_mask_deity/tlut_000D50.rgba16.inc.c"
};

u64 object_mask_deity_Tex_000F50[] = {
#include "assets/objects/object_mask_deity/tex_000F50.ci8.inc.c"
};

u64 object_mask_deity_Tex_001350[] = {
#include "assets/objects/object_mask_deity/tex_001350.ci8.inc.c"
};

u64 object_mask_deity_Tex_001B50[] = {
#include "assets/objects/object_mask_deity/tex_001B50.ci8.inc.c"
};

u64 object_mask_deity_Tex_001F50[] = {
#include "assets/objects/object_mask_deity/tex_001F50.ci8.inc.c"
};

u64 object_mask_deity_Tex_002050[] = {
#include "assets/objects/object_mask_deity/tex_002050.rgba16.inc.c"
};

