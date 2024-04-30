#include "ultra64.h"
#include "z64.h"
#include "macros.h"
#include "object_link_deity.h"
#include "assets/misc/link_animetion/link_animetion.h"
#include "assets/objects/gameplay_keep/gameplay_keep.h"

u64 object_link_deity_TLUT_000000[] = {
#include "assets/objects/object_link_deity/tlut_000000.rgba16.inc.c"
};

u64 object_link_deity_TLUT_000200[] = {
#include "assets/objects/object_link_deity/tlut_000200.rgba16.inc.c"
};

u64 gLinkFierceDeityHandHoldingTLUT[] = {
#include "assets/objects/object_link_deity/hand_holding_tlut.rgba16.inc.c"
};

u64 object_link_deity_Tex_000600[] = {
#include "assets/objects/object_link_deity/tex_000600.ci8.inc.c"
};

u64 object_link_deity_Tex_000800[] = {
#include "assets/objects/object_link_deity/tex_000800.ci8.inc.c"
};

u64 gLinkFierceDeityHandHoldingTex[] = {
#include "assets/objects/object_link_deity/hand_holding.ci8.inc.c"
};

u64 object_link_deity_Tex_000B00[] = {
#include "assets/objects/object_link_deity/tex_000B00.i8.inc.c"
};

Vtx object_link_deityVtx_000C00[] = {
#include "assets/objects/object_link_deity/object_link_deityVtx_000C00.vtx.inc"
};

Gfx gLinkFierceDeityWaistDL[] = {
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPPipeSync(),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPSetTextureLUT(G_TT_RGBA16),
    gsDPLoadTLUT_pal16(15, object_link_deity_TLUT_008108),
    gsDPLoadTextureBlock_4b(object_link_deity_Tex_008408, G_IM_FMT_CI, 16, 16, 15, G_TX_MIRROR | G_TX_WRAP, G_TX_MIRROR |
                            G_TX_WRAP, 4, 4, G_TX_NOLOD, G_TX_NOLOD),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 0x02FC, 0x003C),
    gsDPSetPrimColor(0, 0x80, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&object_link_deityVtx_000C00[302], 9, 0),
    gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
    gsSP2Triangles(0, 3, 4, 0, 5, 6, 7, 0),
    gsSP1Triangle(5, 7, 8, 0),
    gsSPVertex(&object_link_deityVtx_000C00[311], 4, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&object_link_deityVtx_000C00[315], 6, 0),
    gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
    gsSP2Triangles(0, 3, 4, 0, 0, 4, 5, 0),
    gsDPPipeSync(),
    gsDPLoadTLUT_pal16(15, object_link_deity_TLUT_008148),
    gsDPLoadTextureBlock_4b(object_link_deity_Tex_008D08, G_IM_FMT_CI, 32, 32, 15, G_TX_NOMIRROR | G_TX_CLAMP,
                            G_TX_NOMIRROR | G_TX_CLAMP, 5, 5, G_TX_NOLOD, G_TX_NOLOD),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&object_link_deityVtx_000C00[321], 4, 0),
    gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
    gsDPPipeSync(),
    gsDPLoadTLUT_pal16(15, object_link_deity_TLUT_008168),
    gsDPLoadTextureBlock_4b(object_link_deity_Tex_008F08, G_IM_FMT_CI, 64, 64, 15, G_TX_NOMIRROR | G_TX_CLAMP,
                            G_TX_NOMIRROR | G_TX_CLAMP, 6, 6, G_TX_NOLOD, G_TX_NOLOD),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&object_link_deityVtx_000C00[325], 16, 0),
    gsSP2Triangles(0, 1, 2, 0, 3, 4, 5, 0),
    gsSP2Triangles(6, 7, 8, 0, 9, 10, 7, 0),
    gsSP2Triangles(6, 9, 7, 0, 2, 1, 6, 0),
    gsSP2Triangles(11, 10, 9, 0, 11, 9, 12, 0),
    gsSP2Triangles(13, 14, 15, 0, 1, 0, 14, 0),
    gsSP1Triangle(1, 14, 13, 0),
    gsSPVertex(&object_link_deityVtx_000C00[341], 12, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
    gsSP2Triangles(4, 0, 3, 0, 4, 3, 5, 0),
    gsSP2Triangles(6, 7, 8, 0, 9, 10, 6, 0),
    gsSP2Triangles(6, 8, 11, 0, 6, 11, 9, 0),
    gsSPEndDisplayList(),
};

Gfx gLinkFierceDeityRightThighDL[] = {
    gsSPMatrix(0x0D000000, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&object_link_deityVtx_000C00[97], 2, 0),
    gsSPVertex(&object_link_deityVtx_000C00[99], 6, 2),
    gsSPMatrix(0x0D000040, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPPipeSync(),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPSetTextureLUT(G_TT_RGBA16),
    gsDPLoadTLUT_pal16(15, object_link_deity_TLUT_008128),
    gsDPLoadTextureBlock_4b(object_link_deity_Tex_008C88, G_IM_FMT_CI, 16, 16, 15, G_TX_MIRROR | G_TX_CLAMP, G_TX_NOMIRROR
                            | G_TX_CLAMP, 4, 4, G_TX_NOLOD, G_TX_NOLOD),
    gsDPSetPrimColor(0, 0x80, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&object_link_deityVtx_000C00[105], 1, 8),
    gsSP1Triangle(4, 8, 1, 0),
    gsSPVertex(&object_link_deityVtx_000C00[106], 3, 8),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSP2Triangles(4, 2, 8, 0, 4, 9, 10, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSP1Triangle(5, 0, 6, 0),
    gsSPVertex(&object_link_deityVtx_000C00[109], 1, 8),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSP1Triangle(5, 6, 8, 0),
    gsSPVertex(&object_link_deityVtx_000C00[110], 2, 8),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSP1Triangle(8, 9, 4, 0),
    gsSPVertex(&object_link_deityVtx_000C00[112], 11, 8),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSP2Triangles(8, 9, 2, 0, 10, 2, 3, 0),
    gsSP2Triangles(11, 12, 3, 0, 13, 3, 5, 0),
    gsSP2Triangles(3, 14, 15, 0, 7, 16, 17, 0),
    gsSP1Triangle(18, 6, 7, 0),
    gsDPPipeSync(),
    gsDPLoadTLUT_pal16(15, object_link_deity_TLUT_008108),
    gsDPLoadTextureBlock_4b(object_link_deity_Tex_008408, G_IM_FMT_CI, 16, 16, 15, G_TX_MIRROR | G_TX_CLAMP, G_TX_NOMIRROR
                            | G_TX_CLAMP, 4, 4, G_TX_NOLOD, G_TX_NOLOD),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 0x007C, 0x003C),
    gsSPVertex(&object_link_deityVtx_000C00[123], 3, 0),
    gsSP1Triangle(0, 1, 2, 0),
    gsSPVertex(&object_link_deityVtx_000C00[126], 3, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSP1Triangle(0, 1, 2, 0),
    gsSPVertex(&object_link_deityVtx_000C00[129], 3, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSP1Triangle(0, 1, 2, 0),
    gsSPVertex(&object_link_deityVtx_000C00[132], 9, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSP2Triangles(0, 1, 2, 0, 3, 4, 5, 0),
    gsSP2Triangles(3, 5, 6, 0, 4, 7, 8, 0),
    gsSP2Triangles(4, 8, 5, 0, 7, 0, 2, 0),
    gsSP1Triangle(7, 2, 8, 0),
    gsDPPipeSync(),
    gsDPLoadTLUT_pal16(15, object_link_deity_TLUT_008128),
    gsDPLoadTextureBlock_4b(object_link_deity_Tex_008C88, G_IM_FMT_CI, 16, 16, 15, G_TX_MIRROR | G_TX_CLAMP, G_TX_NOMIRROR
                            | G_TX_CLAMP, 4, 4, G_TX_NOLOD, G_TX_NOLOD),
    gsSPVertex(&object_link_deityVtx_000C00[141], 4, 0),
    gsSP2Triangles(0, 1, 2, 0, 3, 1, 0, 0),
    gsSPVertex(&object_link_deityVtx_000C00[145], 5, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSP2Triangles(0, 1, 2, 0, 3, 0, 2, 0),
    gsSP1Triangle(2, 4, 3, 0),
    gsSPEndDisplayList(),
};

Gfx gLinkFierceDeityRightShinDL[] = {
    gsSPMatrix(0x0D000040, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&object_link_deityVtx_000C00[41], 1, 0),
    gsSPVertex(&object_link_deityVtx_000C00[42], 1, 1),
    gsSPVertex(&object_link_deityVtx_000C00[43], 3, 2),
    gsSPMatrix(0x0D000080, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPPipeSync(),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPSetTextureLUT(G_TT_RGBA16),
    gsDPLoadTLUT_pal16(15, object_link_deity_TLUT_008108),
    gsDPLoadTextureBlock_4b(object_link_deity_Tex_008408, G_IM_FMT_CI, 16, 16, 15, G_TX_MIRROR | G_TX_CLAMP, G_TX_NOMIRROR
                            | G_TX_CLAMP, 4, 4, G_TX_NOLOD, G_TX_NOLOD),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 0x007C, 0x003C),
    gsDPSetPrimColor(0, 0x80, 255, 255, 255, 255),
    gsSPVertex(&object_link_deityVtx_000C00[46], 15, 5),
    gsSP2Triangles(0, 1, 5, 0, 2, 6, 7, 0),
    gsSP2Triangles(2, 3, 8, 0, 9, 3, 4, 0),
    gsSP2Triangles(10, 4, 11, 0, 12, 13, 0, 0),
    gsSP2Triangles(14, 1, 2, 0, 15, 4, 0, 0),
    gsSP2Triangles(16, 0, 17, 0, 18, 2, 19, 0),
    gsSPVertex(&object_link_deityVtx_000C00[61], 6, 0),
    gsSP2Triangles(0, 1, 2, 0, 2, 1, 3, 0),
    gsSP2Triangles(2, 3, 4, 0, 4, 3, 5, 0),
    gsDPPipeSync(),
    gsDPSetTextureLUT(G_TT_NONE),
    gsDPLoadTextureBlock(object_link_deity_Tex_008488, G_IM_FMT_RGBA, G_IM_SIZ_16b, 16, 32, 0, G_TX_MIRROR | G_TX_WRAP,
                         G_TX_NOMIRROR | G_TX_WRAP, 4, 5, G_TX_NOLOD, G_TX_NOLOD),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 0x007C, 0x007C),
    gsSPVertex(&object_link_deityVtx_000C00[67], 18, 0),
    gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
    gsSP2Triangles(4, 5, 6, 0, 4, 6, 7, 0),
    gsSP2Triangles(3, 2, 6, 0, 3, 6, 8, 0),
    gsSP2Triangles(9, 10, 11, 0, 12, 11, 10, 0),
    gsSP2Triangles(9, 11, 4, 0, 8, 6, 5, 0),
    gsSP2Triangles(10, 13, 14, 0, 14, 12, 10, 0),
    gsSP2Triangles(5, 12, 8, 0, 7, 6, 2, 0),
    gsSP2Triangles(7, 2, 15, 0, 2, 1, 16, 0),
    gsSP2Triangles(2, 16, 15, 0, 5, 11, 12, 0),
    gsSP2Triangles(13, 10, 9, 0, 13, 9, 17, 0),
    gsSP1Triangle(11, 5, 4, 0),
    gsDPPipeSync(),
    gsDPLoadTextureBlock(object_link_deity_Tex_008888, G_IM_FMT_RGBA, G_IM_SIZ_16b, 32, 16, 0, G_TX_NOMIRROR | G_TX_CLAMP,
                         G_TX_NOMIRROR | G_TX_CLAMP, 5, 4, G_TX_NOLOD, G_TX_NOLOD),
    gsSPVertex(&object_link_deityVtx_000C00[85], 12, 0),
    gsSP2Triangles(0, 1, 2, 0, 3, 4, 5, 0),
    gsSP2Triangles(6, 7, 0, 0, 6, 0, 8, 0),
    gsSP2Triangles(3, 5, 9, 0, 6, 8, 9, 0),
    gsSP2Triangles(6, 9, 5, 0, 10, 4, 3, 0),
    gsSP2Triangles(10, 3, 11, 0, 0, 7, 1, 0),
    gsSPEndDisplayList(),
};

Gfx gLinkFierceDeityRightFootDL[] = {
    gsSPMatrix(0x0D000080, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(object_link_deityVtx_000C00, 4, 0),
    gsSPMatrix(0x0D0000C0, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPPipeSync(),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPSetTextureLUT(G_TT_NONE),
    gsDPLoadTextureBlock(object_link_deity_Tex_008208, G_IM_FMT_RGBA, G_IM_SIZ_16b, 16, 16, 0, G_TX_NOMIRROR | G_TX_CLAMP,
                         G_TX_NOMIRROR | G_TX_CLAMP, 4, 4, G_TX_NOLOD, G_TX_NOLOD),
    gsDPSetPrimColor(0, 0x80, 255, 255, 255, 255),
    gsSPVertex(&object_link_deityVtx_000C00[4], 22, 4),
    gsSP2Triangles(0, 4, 5, 0, 6, 7, 1, 0),
    gsSP2Triangles(8, 9, 2, 0, 0, 10, 11, 0),
    gsSP2Triangles(3, 1, 12, 0, 13, 14, 0, 0),
    gsSP2Triangles(1, 2, 15, 0, 3, 16, 0, 0),
    gsSP2Triangles(17, 2, 0, 0, 1, 18, 19, 0),
    gsSP2Triangles(20, 21, 1, 0, 22, 3, 23, 0),
    gsSP1Triangle(24, 25, 3, 0),
    gsSPVertex(&object_link_deityVtx_000C00[26], 15, 0),
    gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
    gsSP2Triangles(4, 5, 6, 0, 7, 0, 3, 0),
    gsSP2Triangles(7, 3, 8, 0, 8, 9, 10, 0),
    gsSP2Triangles(8, 10, 7, 0, 11, 4, 6, 0),
    gsSP2Triangles(11, 12, 4, 0, 12, 11, 13, 0),
    gsSP1Triangle(13, 14, 12, 0),
    gsSPEndDisplayList(),
};

Gfx gLinkFierceDeityLeftThighDL[] = {
    gsSPMatrix(0x0D000000, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&object_link_deityVtx_000C00[248], 1, 0),
    gsSPVertex(&object_link_deityVtx_000C00[249], 1, 1),
    gsSPVertex(&object_link_deityVtx_000C00[250], 2, 2),
    gsSPVertex(&object_link_deityVtx_000C00[252], 1, 4),
    gsSPVertex(&object_link_deityVtx_000C00[253], 3, 5),
    gsSPMatrix(0x0D000100, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPPipeSync(),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPSetTextureLUT(G_TT_RGBA16),
    gsDPLoadTLUT_pal16(15, object_link_deity_TLUT_008128),
    gsDPLoadTextureBlock_4b(object_link_deity_Tex_008C88, G_IM_FMT_CI, 16, 16, 15, G_TX_MIRROR | G_TX_CLAMP, G_TX_NOMIRROR
                            | G_TX_CLAMP, 4, 4, G_TX_NOLOD, G_TX_NOLOD),
    gsDPSetPrimColor(0, 0x80, 250, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&object_link_deityVtx_000C00[256], 1, 8),
    gsSP1Triangle(1, 8, 4, 0),
    gsSPVertex(&object_link_deityVtx_000C00[257], 3, 8),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSP2Triangles(8, 9, 2, 0, 10, 2, 4, 0),
    gsSPVertex(&object_link_deityVtx_000C00[260], 1, 8),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSP1Triangle(8, 6, 0, 0),
    gsSPVertex(&object_link_deityVtx_000C00[261], 1, 8),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSP1Triangle(8, 0, 5, 0),
    gsSPVertex(&object_link_deityVtx_000C00[262], 2, 8),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSP1Triangle(4, 8, 9, 0),
    gsSPVertex(&object_link_deityVtx_000C00[264], 2, 8),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSP1Triangle(2, 8, 9, 0),
    gsSPVertex(&object_link_deityVtx_000C00[266], 9, 8),
    gsSP2Triangles(3, 2, 8, 0, 5, 3, 9, 0),
    gsSP2Triangles(5, 10, 11, 0, 12, 13, 3, 0),
    gsSP2Triangles(14, 15, 7, 0, 7, 6, 16, 0),
    gsDPPipeSync(),
    gsDPLoadTLUT_pal16(15, object_link_deity_TLUT_008108),
    gsDPLoadTextureBlock_4b(object_link_deity_Tex_008408, G_IM_FMT_CI, 16, 16, 15, G_TX_MIRROR | G_TX_CLAMP, G_TX_NOMIRROR
                            | G_TX_CLAMP, 4, 4, G_TX_NOLOD, G_TX_NOLOD),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 0x007C, 0x003C),
    gsDPSetPrimColor(0, 0x80, 255, 255, 255, 255),
    gsSPVertex(&object_link_deityVtx_000C00[275], 3, 0),
    gsSP1Triangle(0, 1, 2, 0),
    gsSPVertex(&object_link_deityVtx_000C00[278], 3, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSP1Triangle(0, 1, 2, 0),
    gsSPVertex(&object_link_deityVtx_000C00[281], 3, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSP1Triangle(0, 1, 2, 0),
    gsSPVertex(&object_link_deityVtx_000C00[284], 9, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSP2Triangles(0, 1, 2, 0, 3, 4, 5, 0),
    gsSP2Triangles(3, 5, 6, 0, 4, 7, 8, 0),
    gsSP2Triangles(4, 8, 5, 0, 7, 0, 2, 0),
    gsSP1Triangle(7, 2, 8, 0),
    gsDPPipeSync(),
    gsDPLoadTLUT_pal16(15, object_link_deity_TLUT_008128),
    gsDPLoadTextureBlock_4b(object_link_deity_Tex_008C88, G_IM_FMT_CI, 16, 16, 15, G_TX_MIRROR | G_TX_CLAMP, G_TX_NOMIRROR
                            | G_TX_CLAMP, 4, 4, G_TX_NOLOD, G_TX_NOLOD),
    gsDPSetPrimColor(0, 0x80, 250, 255, 255, 255),
    gsSPVertex(&object_link_deityVtx_000C00[293], 4, 0),
    gsSP2Triangles(0, 1, 2, 0, 3, 2, 1, 0),
    gsSPVertex(&object_link_deityVtx_000C00[297], 5, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
    gsSP1Triangle(3, 4, 0, 0),
    gsSPEndDisplayList(),
};

Gfx gLinkFierceDeityLeftShinDL[] = {
    gsSPMatrix(0x0D000100, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&object_link_deityVtx_000C00[191], 2, 0),
    gsSPVertex(&object_link_deityVtx_000C00[193], 2, 2),
    gsSPVertex(&object_link_deityVtx_000C00[195], 1, 4),
    gsSPMatrix(0x0D000140, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPPipeSync(),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPSetTextureLUT(G_TT_RGBA16),
    gsDPLoadTLUT_pal16(15, object_link_deity_TLUT_008108),
    gsDPLoadTextureBlock_4b(object_link_deity_Tex_008408, G_IM_FMT_CI, 16, 16, 15, G_TX_MIRROR | G_TX_CLAMP, G_TX_NOMIRROR
                            | G_TX_CLAMP, 4, 4, G_TX_NOLOD, G_TX_NOLOD),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 0x007C, 0x003C),
    gsDPSetPrimColor(0, 0x80, 255, 255, 255, 255),
    gsSPVertex(&object_link_deityVtx_000C00[196], 15, 5),
    gsSP2Triangles(5, 1, 0, 0, 6, 7, 2, 0),
    gsSP2Triangles(8, 3, 2, 0, 9, 4, 3, 0),
    gsSP2Triangles(10, 3, 11, 0, 0, 12, 13, 0),
    gsSP2Triangles(2, 1, 14, 0, 0, 4, 15, 0),
    gsSP2Triangles(16, 0, 17, 0, 18, 2, 19, 0),
    gsSPVertex(&object_link_deityVtx_000C00[211], 6, 0),
    gsSP2Triangles(0, 1, 2, 0, 3, 4, 1, 0),
    gsSP2Triangles(3, 1, 0, 0, 5, 4, 3, 0),
    gsDPPipeSync(),
    gsDPSetTextureLUT(G_TT_NONE),
    gsDPLoadTextureBlock(object_link_deity_Tex_008488, G_IM_FMT_RGBA, G_IM_SIZ_16b, 16, 32, 0, G_TX_NOMIRROR | G_TX_WRAP,
                         G_TX_NOMIRROR | G_TX_WRAP, 4, 5, G_TX_NOLOD, G_TX_NOLOD),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 0x007C, 0x007C),
    gsSPVertex(&object_link_deityVtx_000C00[217], 19, 0),
    gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
    gsSP2Triangles(4, 5, 6, 0, 4, 6, 7, 0),
    gsSP2Triangles(8, 5, 9, 0, 8, 9, 10, 0),
    gsSP2Triangles(11, 12, 13, 0, 12, 11, 14, 0),
    gsSP2Triangles(7, 11, 13, 0, 6, 5, 8, 0),
    gsSP2Triangles(3, 2, 12, 0, 12, 14, 3, 0),
    gsSP2Triangles(8, 14, 6, 0, 15, 1, 16, 0),
    gsSP2Triangles(15, 16, 17, 0, 15, 18, 2, 0),
    gsSP2Triangles(15, 2, 1, 0, 14, 11, 6, 0),
    gsSP2Triangles(18, 13, 12, 0, 18, 12, 2, 0),
    gsSP1Triangle(7, 6, 11, 0),
    gsDPPipeSync(),
    gsDPLoadTextureBlock(object_link_deity_Tex_008888, G_IM_FMT_RGBA, G_IM_SIZ_16b, 32, 16, 0, G_TX_NOMIRROR | G_TX_CLAMP,
                         G_TX_NOMIRROR | G_TX_CLAMP, 5, 4, G_TX_NOLOD, G_TX_NOLOD),
    gsSPVertex(&object_link_deityVtx_000C00[236], 12, 0),
    gsSP2Triangles(0, 1, 2, 0, 3, 4, 5, 0),
    gsSP2Triangles(6, 7, 8, 0, 6, 8, 9, 0),
    gsSP2Triangles(3, 5, 10, 0, 4, 3, 6, 0),
    gsSP2Triangles(4, 6, 9, 0, 0, 10, 5, 0),
    gsSP2Triangles(0, 5, 11, 0, 0, 11, 1, 0),
    gsSPEndDisplayList(),
};

Gfx gLinkFierceDeityLeftFootDL[] = {
    gsSPMatrix(0x0D000140, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&object_link_deityVtx_000C00[150], 4, 0),
    gsSPMatrix(0x0D000180, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPPipeSync(),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPSetTextureLUT(G_TT_NONE),
    gsDPLoadTextureBlock(object_link_deity_Tex_008208, G_IM_FMT_RGBA, G_IM_SIZ_16b, 16, 16, 0, G_TX_NOMIRROR | G_TX_CLAMP,
                         G_TX_NOMIRROR | G_TX_CLAMP, 4, 4, G_TX_NOLOD, G_TX_NOLOD),
    gsDPSetPrimColor(0, 0x80, 255, 255, 255, 255),
    gsSPVertex(&object_link_deityVtx_000C00[154], 22, 4),
    gsSP2Triangles(4, 5, 0, 0, 1, 6, 7, 0),
    gsSP2Triangles(2, 8, 9, 0, 10, 11, 0, 0),
    gsSP2Triangles(12, 1, 3, 0, 0, 13, 14, 0),
    gsSP2Triangles(15, 2, 1, 0, 0, 16, 3, 0),
    gsSP2Triangles(0, 2, 17, 0, 18, 19, 1, 0),
    gsSP2Triangles(1, 20, 21, 0, 22, 3, 23, 0),
    gsSP1Triangle(3, 24, 25, 0),
    gsSPVertex(&object_link_deityVtx_000C00[176], 15, 0),
    gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
    gsSP2Triangles(4, 5, 6, 0, 7, 0, 3, 0),
    gsSP2Triangles(7, 3, 8, 0, 8, 9, 10, 0),
    gsSP2Triangles(8, 10, 7, 0, 4, 6, 11, 0),
    gsSP2Triangles(6, 12, 11, 0, 13, 11, 12, 0),
    gsSP1Triangle(12, 14, 13, 0),
    gsSPEndDisplayList(),
};

Gfx gLinkFierceDeityHatDL[] = {
    gsSPMatrix(0x0D0001C0, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&object_link_deityVtx_000C00[353], 2, 0),
    gsSPVertex(&object_link_deityVtx_000C00[355], 1, 2),
    gsSPVertex(&object_link_deityVtx_000C00[356], 3, 3),
    gsSPMatrix(0x0D000200, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPPipeSync(),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPSetTextureLUT(G_TT_RGBA16),
    gsDPLoadTLUT_pal16(15, object_link_deity_TLUT_008128),
    gsDPLoadTextureBlock_4b(object_link_deity_Tex_008C88, G_IM_FMT_CI, 16, 16, 15, G_TX_NOMIRROR | G_TX_CLAMP,
                            G_TX_NOMIRROR | G_TX_CLAMP, 4, 4, G_TX_NOLOD, G_TX_NOLOD),
    gsDPSetPrimColor(0, 0x80, 255, 255, 255, 255),
    gsSPVertex(&object_link_deityVtx_000C00[359], 18, 6),
    gsSP2Triangles(6, 0, 7, 0, 8, 9, 5, 0),
    gsSP2Triangles(3, 2, 10, 0, 11, 12, 2, 0),
    gsSP2Triangles(13, 4, 0, 0, 1, 5, 14, 0),
    gsSP2Triangles(15, 2, 1, 0, 16, 17, 1, 0),
    gsSP2Triangles(1, 18, 19, 0, 20, 5, 4, 0),
    gsSP2Triangles(21, 0, 3, 0, 22, 0, 23, 0),
    gsSPVertex(&object_link_deityVtx_000C00[377], 11, 0),
    gsSP2Triangles(0, 1, 2, 0, 3, 4, 5, 0),
    gsSP2Triangles(0, 3, 6, 0, 4, 7, 5, 0),
    gsSP2Triangles(8, 2, 1, 0, 0, 6, 1, 0),
    gsSP2Triangles(5, 8, 1, 0, 5, 6, 3, 0),
    gsSP2Triangles(3, 9, 4, 0, 5, 7, 8, 0),
    gsSP2Triangles(1, 6, 5, 0, 9, 3, 0, 0),
    gsSP2Triangles(10, 0, 2, 0, 9, 0, 10, 0),
    gsSPEndDisplayList(),
};

Gfx gLinkFierceDeityHeadDL[] = {
    gsSPMatrix(0x0D000440, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&object_link_deityVtx_000C00[388], 6, 0),
    gsSPMatrix(0x0D0001C0, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPPipeSync(),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPSetTextureLUT(G_TT_RGBA16),
    gsDPLoadTLUT_pal16(15, object_link_deity_TLUT_008108),
    gsDPLoadTextureBlock_4b(object_link_deity_Tex_008408, G_IM_FMT_CI, 16, 16, 15, G_TX_NOMIRROR | G_TX_CLAMP,
                            G_TX_NOMIRROR | G_TX_CLAMP, 4, 4, G_TX_NOLOD, G_TX_NOLOD),
    gsDPSetPrimColor(0, 0x80, 255, 255, 255, 255),
    gsSPVertex(&object_link_deityVtx_000C00[394], 7, 6),
    gsSP2Triangles(4, 6, 7, 0, 8, 2, 3, 0),
    gsSP2Triangles(5, 9, 10, 0, 0, 11, 12, 0),
    gsSPVertex(&object_link_deityVtx_000C00[401], 1, 6),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSP1Triangle(6, 5, 0, 0),
    gsSPVertex(&object_link_deityVtx_000C00[402], 10, 6),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSP2Triangles(6, 1, 4, 0, 7, 3, 5, 0),
    gsSP2Triangles(2, 8, 9, 0, 4, 10, 11, 0),
    gsSP2Triangles(12, 0, 13, 0, 14, 4, 2, 0),
    gsSP1Triangle(15, 0, 1, 0),
    gsDPPipeSync(),
    gsDPSetTextureLUT(G_TT_NONE),
    gsDPLoadTextureBlock(gLinkFierceDeityEyesTex, G_IM_FMT_RGBA, G_IM_SIZ_16b, 64, 32, 0, G_TX_NOMIRROR | G_TX_CLAMP,
                         G_TX_NOMIRROR | G_TX_CLAMP, 6, 5, G_TX_NOLOD, G_TX_NOLOD),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&object_link_deityVtx_000C00[412], 3, 0),
    gsSP1Triangle(0, 1, 2, 0),
    gsSPVertex(&object_link_deityVtx_000C00[415], 32, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSP2Triangles(0, 1, 2, 0, 3, 1, 4, 0),
    gsSP2Triangles(5, 6, 7, 0, 8, 9, 5, 0),
    gsSP2Triangles(10, 11, 12, 0, 0, 13, 4, 0),
    gsSP2Triangles(4, 1, 0, 0, 13, 7, 12, 0),
    gsSP2Triangles(13, 0, 8, 0, 7, 13, 8, 0),
    gsSP2Triangles(8, 5, 7, 0, 11, 4, 13, 0),
    gsSP2Triangles(11, 13, 12, 0, 14, 15, 6, 0),
    gsSP2Triangles(3, 16, 17, 0, 9, 18, 19, 0),
    gsSP2Triangles(9, 19, 20, 0, 21, 19, 22, 0),
    gsSP2Triangles(19, 21, 20, 0, 19, 18, 22, 0),
    gsSP2Triangles(18, 23, 22, 0, 5, 9, 20, 0),
    gsSP2Triangles(22, 23, 24, 0, 21, 22, 24, 0),
    gsSP2Triangles(25, 26, 27, 0, 27, 26, 24, 0),
    gsSP2Triangles(23, 28, 29, 0, 29, 28, 30, 0),
    gsSP2Triangles(24, 26, 21, 0, 25, 27, 30, 0),
    gsSP2Triangles(30, 27, 29, 0, 29, 27, 23, 0),
    gsSP2Triangles(23, 27, 24, 0, 2, 1, 31, 0),
    gsSP2Triangles(3, 31, 1, 0, 23, 2, 31, 0),
    gsSP2Triangles(23, 31, 17, 0, 31, 3, 17, 0),
    gsSP2Triangles(17, 16, 28, 0, 17, 28, 23, 0),
    gsSP1Triangle(5, 20, 14, 0),
    gsSPVertex(&object_link_deityVtx_000C00[447], 15, 0),
    gsSP2Triangles(0, 1, 2, 0, 3, 4, 5, 0),
    gsSP2Triangles(6, 7, 8, 0, 9, 10, 11, 0),
    gsSP1Triangle(12, 13, 14, 0),
    gsDPPipeSync(),
    gsDPSetTextureLUT(G_TT_RGBA16),
    gsDPLoadTLUT_pal16(15, object_link_deity_TLUT_008128),
    gsDPLoadTextureBlock_4b(object_link_deity_Tex_008C88, G_IM_FMT_CI, 16, 16, 15, G_TX_NOMIRROR | G_TX_CLAMP,
                            G_TX_NOMIRROR | G_TX_CLAMP, 4, 4, G_TX_NOLOD, G_TX_NOLOD),
    gsSPVertex(&object_link_deityVtx_000C00[462], 11, 0),
    gsSP2Triangles(0, 1, 2, 0, 3, 4, 5, 0),
    gsSP2Triangles(3, 5, 6, 0, 6, 5, 7, 0),
    gsSP2Triangles(7, 5, 8, 0, 9, 7, 8, 0),
    gsSP1Triangle(9, 8, 10, 0),
    gsSPVertex(&object_link_deityVtx_000C00[473], 3, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSP1Triangle(0, 1, 2, 0),
    gsSPVertex(&object_link_deityVtx_000C00[476], 20, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSP2Triangles(0, 1, 2, 0, 3, 4, 2, 0),
    gsSP2Triangles(2, 4, 0, 0, 5, 6, 7, 0),
    gsSP2Triangles(6, 5, 8, 0, 9, 8, 10, 0),
    gsSP2Triangles(1, 10, 11, 0, 1, 12, 10, 0),
    gsSP2Triangles(2, 1, 11, 0, 12, 9, 10, 0),
    gsSP2Triangles(2, 13, 3, 0, 10, 13, 11, 0),
    gsSP2Triangles(10, 5, 13, 0, 8, 5, 10, 0),
    gsSP2Triangles(14, 15, 16, 0, 6, 8, 9, 0),
    gsSP2Triangles(17, 15, 7, 0, 16, 15, 18, 0),
    gsSP2Triangles(15, 17, 18, 0, 6, 18, 17, 0),
    gsSP2Triangles(6, 19, 18, 0, 6, 9, 19, 0),
    gsSP1Triangle(17, 7, 6, 0),
    gsDPPipeSync(),
    gsDPLoadTLUT_pal16(15, object_link_deity_TLUT_008188),
    gsDPLoadTextureBlock_4b(object_link_deity_Tex_00A708, G_IM_FMT_CI, 32, 32, 15, G_TX_NOMIRROR | G_TX_CLAMP,
                            G_TX_NOMIRROR | G_TX_CLAMP, 5, 5, G_TX_NOLOD, G_TX_NOLOD),
    gsSPVertex(&object_link_deityVtx_000C00[496], 32, 0),
    gsSP2Triangles(0, 1, 2, 0, 3, 4, 0, 0),
    gsSP2Triangles(5, 6, 7, 0, 8, 9, 10, 0),
    gsSP2Triangles(11, 12, 13, 0, 14, 15, 16, 0),
    gsSP2Triangles(17, 18, 19, 0, 17, 19, 20, 0),
    gsSP2Triangles(21, 22, 23, 0, 24, 25, 26, 0),
    gsSP2Triangles(2, 7, 6, 0, 7, 21, 27, 0),
    gsSP1Triangle(28, 29, 30, 0),
    gsSPVertex(&object_link_deityVtx_000C00[527], 32, 0),
    gsSP2Triangles(0, 1, 2, 0, 2, 1, 3, 0),
    gsSP2Triangles(4, 5, 6, 0, 7, 8, 9, 0),
    gsSP2Triangles(10, 11, 12, 0, 13, 14, 15, 0),
    gsSP2Triangles(4, 6, 16, 0, 17, 18, 19, 0),
    gsSP2Triangles(20, 21, 14, 0, 22, 23, 24, 0),
    gsSP2Triangles(25, 26, 27, 0, 25, 27, 28, 0),
    gsSP2Triangles(28, 27, 29, 0, 29, 22, 30, 0),
    gsSP2Triangles(29, 30, 28, 0, 30, 22, 24, 0),
    gsSPVertex(&object_link_deityVtx_000C00[558], 28, 0),
    gsSP2Triangles(0, 1, 2, 0, 2, 1, 3, 0),
    gsSP2Triangles(4, 5, 6, 0, 4, 6, 7, 0),
    gsSP2Triangles(8, 9, 10, 0, 8, 10, 11, 0),
    gsSP2Triangles(12, 13, 14, 0, 15, 16, 17, 0),
    gsSP2Triangles(18, 19, 7, 0, 20, 21, 22, 0),
    gsSP2Triangles(7, 19, 4, 0, 10, 23, 11, 0),
    gsSP2Triangles(24, 25, 26, 0, 27, 25, 24, 0),
    gsDPPipeSync(),
    gsDPSetTextureLUT(G_TT_NONE),
    gsDPLoadTextureBlock(gLinkFierceDeityMouthTex, G_IM_FMT_RGBA, G_IM_SIZ_16b, 32, 16, 0, G_TX_NOMIRROR | G_TX_CLAMP,
                         G_TX_NOMIRROR | G_TX_CLAMP, 5, 4, G_TX_NOLOD, G_TX_NOLOD),
    gsSPVertex(&object_link_deityVtx_000C00[586], 13, 0),
    gsSP2Triangles(0, 1, 2, 0, 2, 3, 0, 0),
    gsSP2Triangles(4, 5, 2, 0, 4, 2, 1, 0),
    gsSP2Triangles(6, 7, 8, 0, 8, 7, 9, 0),
    gsSP2Triangles(10, 1, 11, 0, 12, 11, 4, 0),
    gsSP1Triangle(2, 5, 3, 0),
    gsDPPipeSync(),
    gsDPSetCombineLERP(0, 0, 0, TEXEL0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPSetTextureLUT(G_TT_RGBA16),
    gsDPLoadTLUT_pal16(15, object_link_deity_TLUT_008188),
    gsDPLoadTextureBlock_4b(object_link_deity_Tex_00A708, G_IM_FMT_CI, 32, 32, 15, G_TX_NOMIRROR | G_TX_CLAMP,
                            G_TX_NOMIRROR | G_TX_CLAMP, 5, 5, G_TX_NOLOD, G_TX_NOLOD),
    gsDPSetPrimColor(0, 0x80, 255, 253, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_SHADING_SMOOTH),
    gsSPVertex(&object_link_deityVtx_000C00[599], 3, 0),
    gsSP1Triangle(0, 1, 2, 0),
    gsDPPipeSync(),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPSetTextureLUT(G_TT_NONE),
    gsDPLoadTextureBlock(gLinkFierceDeityEarTex, G_IM_FMT_RGBA, G_IM_SIZ_16b, 16, 16, 0, G_TX_NOMIRROR | G_TX_CLAMP,
                         G_TX_NOMIRROR | G_TX_CLAMP, 4, 4, G_TX_NOLOD, G_TX_NOLOD),
    gsDPSetPrimColor(0, 0x80, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&object_link_deityVtx_000C00[602], 3, 0),
    gsSP1Triangle(0, 1, 2, 0),
    gsSPVertex(&object_link_deityVtx_000C00[605], 10, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSP2Triangles(0, 1, 2, 0, 3, 4, 5, 0),
    gsSP2Triangles(5, 6, 3, 0, 5, 7, 6, 0),
    gsSP1Triangle(8, 9, 1, 0),
    gsSPEndDisplayList(),
};

Gfx object_link_deity_DL_0060E8[] = {
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(PRIMITIVE, 0, SHADE, 0, 0, 0, 0, 1, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
    gsDPSetPrimColor(0, 0x80, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&object_link_deityVtx_000C00[765], 24, 0),
    gsSP2Triangles(0, 1, 2, 0, 3, 4, 5, 0),
    gsSP2Triangles(6, 7, 8, 0, 9, 10, 11, 0),
    gsSP2Triangles(12, 13, 14, 0, 15, 16, 17, 0),
    gsSP2Triangles(18, 19, 20, 0, 21, 22, 23, 0),
    gsSPEndDisplayList(),
};

Gfx gLinkFierceDeityTorsoDL[] = {
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPPipeSync(),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPSetTextureLUT(G_TT_RGBA16),
    gsDPLoadTLUT_pal16(15, object_link_deity_TLUT_0081E8),
    gsDPLoadTextureBlock_4b(object_link_deity_Tex_00B188, G_IM_FMT_CI, 64, 64, 15, G_TX_NOMIRROR | G_TX_CLAMP,
                            G_TX_NOMIRROR | G_TX_CLAMP, 6, 6, G_TX_NOLOD, G_TX_NOLOD),
    gsDPSetPrimColor(0, 0x80, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&object_link_deityVtx_000C00[935], 32, 0),
    gsSP2Triangles(0, 1, 2, 0, 3, 4, 0, 0),
    gsSP2Triangles(4, 3, 5, 0, 6, 3, 0, 0),
    gsSP2Triangles(7, 8, 9, 0, 10, 11, 7, 0),
    gsSP2Triangles(12, 13, 14, 0, 11, 15, 12, 0),
    gsSP2Triangles(7, 11, 16, 0, 17, 18, 10, 0),
    gsSP2Triangles(19, 20, 2, 0, 21, 4, 22, 0),
    gsSP2Triangles(23, 1, 8, 0, 8, 7, 23, 0),
    gsSP2Triangles(13, 12, 15, 0, 24, 15, 25, 0),
    gsSP2Triangles(26, 25, 18, 0, 18, 17, 27, 0),
    gsSP2Triangles(16, 11, 12, 0, 15, 18, 25, 0),
    gsSP2Triangles(18, 15, 11, 0, 18, 11, 10, 0),
    gsSP2Triangles(1, 0, 28, 0, 27, 17, 29, 0),
    gsSP2Triangles(30, 20, 19, 0, 0, 2, 6, 0),
    gsSP2Triangles(5, 30, 4, 0, 30, 22, 4, 0),
    gsSP2Triangles(1, 23, 19, 0, 19, 23, 22, 0),
    gsSP2Triangles(2, 1, 19, 0, 19, 22, 30, 0),
    gsSP2Triangles(14, 16, 12, 0, 31, 22, 23, 0),
    gsSP2Triangles(7, 16, 31, 0, 23, 7, 31, 0),
    gsSP2Triangles(17, 10, 9, 0, 9, 10, 7, 0),
    gsSP2Triangles(9, 29, 17, 0, 28, 8, 1, 0),
    gsSP2Triangles(22, 31, 21, 0, 27, 26, 18, 0),
    gsSP1Triangle(15, 24, 13, 0),
    gsDPPipeSync(),
    gsDPLoadTLUT_pal16(15, object_link_deity_TLUT_008168),
    gsDPLoadTextureBlock_4b(object_link_deity_Tex_008F08, G_IM_FMT_CI, 64, 64, 15, G_TX_NOMIRROR | G_TX_CLAMP,
                            G_TX_NOMIRROR | G_TX_CLAMP, 6, 6, G_TX_NOLOD, G_TX_NOLOD),
    gsSPVertex(&object_link_deityVtx_000C00[967], 17, 0),
    gsSP2Triangles(0, 1, 2, 0, 3, 4, 5, 0),
    gsSP2Triangles(6, 7, 8, 0, 9, 10, 3, 0),
    gsSP2Triangles(2, 1, 11, 0, 9, 2, 10, 0),
    gsSP2Triangles(3, 10, 12, 0, 0, 8, 1, 0),
    gsSP2Triangles(13, 5, 4, 0, 14, 15, 16, 0),
    gsSP2Triangles(5, 13, 15, 0, 9, 5, 14, 0),
    gsSP2Triangles(0, 14, 6, 0, 6, 8, 0, 0),
    gsSP2Triangles(3, 5, 9, 0, 14, 0, 9, 0),
    gsSP2Triangles(2, 9, 0, 0, 16, 6, 14, 0),
    gsSP1Triangle(15, 14, 5, 0),
    gsSPEndDisplayList(),
};

Gfx object_link_deity_DL_006370[] = {
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPPipeSync(),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPSetTextureLUT(G_TT_NONE),
    gsDPLoadTextureBlock(object_link_deity_Tex_008208, G_IM_FMT_RGBA, G_IM_SIZ_16b, 16, 16, 0, G_TX_NOMIRROR | G_TX_CLAMP,
                         G_TX_NOMIRROR | G_TX_CLAMP, 4, 4, G_TX_NOLOD, G_TX_NOLOD),
    gsDPSetPrimColor(0, 0x80, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&object_link_deityVtx_000C00[984], 6, 0),
    gsSP2Triangles(0, 1, 2, 0, 1, 0, 3, 0),
    gsSP2Triangles(4, 0, 2, 0, 0, 4, 3, 0),
    gsSP2Triangles(1, 5, 2, 0, 5, 1, 3, 0),
    gsSP2Triangles(5, 4, 2, 0, 4, 5, 3, 0),
    gsSPEndDisplayList(),
};

Gfx gLinkFierceDeityRightShoulderDL[] = {
    gsSPMatrix(0x0D000440, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&object_link_deityVtx_000C00[893], 3, 0),
    gsSPVertex(&object_link_deityVtx_000C00[896], 2, 3),
    gsSPMatrix(0x0D000340, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPPipeSync(),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPSetTextureLUT(G_TT_RGBA16),
    gsDPLoadTLUT_pal16(15, object_link_deity_TLUT_008128),
    gsDPLoadTextureBlock_4b(object_link_deity_Tex_008C88, G_IM_FMT_CI, 16, 16, 15, G_TX_NOMIRROR | G_TX_CLAMP,
                            G_TX_NOMIRROR | G_TX_CLAMP, 4, 4, G_TX_NOLOD, G_TX_NOLOD),
    gsDPSetPrimColor(0, 0x80, 255, 255, 255, 255),
    gsSPVertex(&object_link_deityVtx_000C00[898], 15, 5),
    gsSP2Triangles(2, 5, 6, 0, 7, 8, 1, 0),
    gsSP2Triangles(3, 9, 10, 0, 11, 0, 2, 0),
    gsSP2Triangles(1, 12, 2, 0, 13, 14, 3, 0),
    gsSP2Triangles(15, 16, 2, 0, 17, 1, 4, 0),
    gsSP2Triangles(18, 4, 3, 0, 3, 0, 19, 0),
    gsSPVertex(&object_link_deityVtx_000C00[913], 12, 0),
    gsSP2Triangles(0, 1, 2, 0, 3, 4, 5, 0),
    gsSP2Triangles(6, 7, 8, 0, 0, 2, 9, 0),
    gsSP2Triangles(8, 7, 10, 0, 10, 9, 8, 0),
    gsSP2Triangles(9, 11, 0, 0, 10, 11, 9, 0),
    gsDPPipeSync(),
    gsDPLoadTLUT_pal16(15, object_link_deity_TLUT_008108),
    gsDPLoadTextureBlock_4b(object_link_deity_Tex_008408, G_IM_FMT_CI, 16, 16, 15, G_TX_NOMIRROR | G_TX_CLAMP,
                            G_TX_NOMIRROR | G_TX_CLAMP, 4, 4, G_TX_NOLOD, G_TX_NOLOD),
    gsDPSetPrimColor(0, 0x80, 190, 178, 178, 255),
    gsSPVertex(&object_link_deityVtx_000C00[925], 10, 0),
    gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
    gsSP2Triangles(4, 5, 6, 0, 4, 6, 7, 0),
    gsSP2Triangles(3, 2, 5, 0, 3, 5, 4, 0),
    gsSP2Triangles(8, 9, 7, 0, 1, 0, 9, 0),
    gsSP2Triangles(9, 8, 1, 0, 7, 6, 8, 0),
    gsSPEndDisplayList(),
};

Gfx gLinkFierceDeityRightForearmDL[] = {
    gsSPMatrix(0x0D000340, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&object_link_deityVtx_000C00[846], 7, 0),
    gsSPMatrix(0x0D000380, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPPipeSync(),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPSetTextureLUT(G_TT_RGBA16),
    gsDPLoadTLUT_pal16(15, object_link_deity_TLUT_008108),
    gsDPLoadTextureBlock_4b(object_link_deity_Tex_008408, G_IM_FMT_CI, 16, 16, 15, G_TX_MIRROR | G_TX_CLAMP, G_TX_NOMIRROR
                            | G_TX_CLAMP, 4, 4, G_TX_NOLOD, G_TX_NOLOD),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 0x007C, 0x003C),
    gsDPSetPrimColor(0, 0x80, 255, 255, 255, 255),
    gsSPVertex(&object_link_deityVtx_000C00[853], 11, 7),
    gsSP2Triangles(7, 4, 5, 0, 8, 5, 9, 0),
    gsSP2Triangles(0, 10, 11, 0, 0, 12, 13, 0),
    gsSP2Triangles(14, 15, 3, 0, 3, 4, 16, 0),
    gsSP1Triangle(17, 5, 0, 0),
    gsSPVertex(&object_link_deityVtx_000C00[864], 6, 7),
    gsSP2Triangles(1, 6, 7, 0, 8, 6, 2, 0),
    gsSP2Triangles(2, 9, 10, 0, 11, 12, 1, 0),
    gsSPVertex(&object_link_deityVtx_000C00[870], 5, 0),
    gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
    gsSP1Triangle(3, 2, 4, 0),
    gsDPPipeSync(),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPLoadTLUT_pal16(15, object_link_deity_TLUT_0081A8),
    gsDPLoadTextureBlock_4b(object_link_deity_Tex_00AF08, G_IM_FMT_CI, 32, 32, 15, G_TX_MIRROR | G_TX_WRAP, G_TX_NOMIRROR
                            | G_TX_WRAP, 5, 5, G_TX_NOLOD, G_TX_NOLOD),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 0x01FC, 0x007C),
    gsSPVertex(&object_link_deityVtx_000C00[875], 18, 0),
    gsSP2Triangles(0, 1, 2, 0, 3, 4, 5, 0),
    gsSP2Triangles(3, 5, 6, 0, 3, 6, 7, 0),
    gsSP2Triangles(8, 9, 10, 0, 8, 10, 11, 0),
    gsSP2Triangles(12, 13, 9, 0, 12, 9, 8, 0),
    gsSP2Triangles(14, 15, 13, 0, 14, 13, 12, 0),
    gsSP2Triangles(16, 10, 9, 0, 16, 13, 15, 0),
    gsSP2Triangles(1, 17, 16, 0, 16, 15, 1, 0),
    gsSP2Triangles(9, 13, 16, 0, 0, 17, 1, 0),
    gsSP2Triangles(2, 1, 15, 0, 2, 15, 14, 0),
    gsSPEndDisplayList(),
};

Gfx gLinkFierceDeityRightHandDL[] = {
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPPipeSync(),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPSetTextureLUT(G_TT_RGBA16),
    gsDPLoadTLUT_pal16(15, object_link_deity_TLUT_0081A8),
    gsDPLoadTextureBlock_4b(object_link_deity_Tex_00AF08, G_IM_FMT_CI, 32, 32, 15, G_TX_NOMIRROR | G_TX_CLAMP,
                            G_TX_NOMIRROR | G_TX_CLAMP, 5, 5, G_TX_NOLOD, G_TX_NOLOD),
    gsDPSetPrimColor(0, 0x80, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&object_link_deityVtx_000C00[789], 6, 0),
    gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
    gsSP2Triangles(4, 0, 3, 0, 4, 3, 5, 0),
    gsSPVertex(&object_link_deityVtx_000C00[795], 7, 0),
    gsSP2Triangles(0, 1, 2, 0, 3, 4, 5, 0),
    gsSP2Triangles(5, 6, 3, 0, 2, 6, 0, 0),
    gsSP1Triangle(2, 3, 6, 0),
    gsSPVertex(&object_link_deityVtx_000C00[802], 6, 0),
    gsSP2Triangles(0, 1, 2, 0, 3, 0, 2, 0),
    gsSP2Triangles(4, 0, 3, 0, 4, 3, 5, 0),
    gsSPVertex(&object_link_deityVtx_000C00[808], 11, 0),
    gsSP2Triangles(0, 1, 2, 0, 3, 4, 5, 0),
    gsSP2Triangles(3, 6, 1, 0, 7, 6, 5, 0),
    gsSP2Triangles(1, 6, 2, 0, 0, 8, 1, 0),
    gsSP2Triangles(3, 5, 6, 0, 9, 5, 10, 0),
    gsSP1Triangle(5, 9, 7, 0),
    gsDPPipeSync(),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPLoadTLUT_pal16(15, gLinkFierceDeityHandTLUT),
    gsDPLoadTextureBlock_4b(gLinkFierceDeityHandTex, G_IM_FMT_CI, 16, 16, 15, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR
                            | G_TX_CLAMP, 4, 4, G_TX_NOLOD, G_TX_NOLOD),
    gsSPVertex(&object_link_deityVtx_000C00[819], 12, 0),
    gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
    gsSP2Triangles(1, 0, 4, 0, 2, 1, 5, 0),
    gsSP2Triangles(2, 5, 6, 0, 4, 7, 6, 0),
    gsSP2Triangles(4, 6, 5, 0, 8, 9, 10, 0),
    gsSP2Triangles(8, 10, 11, 0, 1, 4, 5, 0),
    gsSPVertex(&object_link_deityVtx_000C00[831], 11, 0),
    gsSP2Triangles(0, 1, 2, 0, 3, 4, 5, 0),
    gsSP2Triangles(6, 7, 8, 0, 1, 0, 9, 0),
    gsSP2Triangles(9, 8, 1, 0, 8, 10, 6, 0),
    gsSP2Triangles(3, 5, 0, 0, 5, 9, 0, 0),
    gsDPPipeSync(),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPLoadTLUT_pal16(15, object_link_deity_TLUT_0081A8),
    gsDPLoadTextureBlock_4b(object_link_deity_Tex_00AF08, G_IM_FMT_CI, 32, 32, 15, G_TX_NOMIRROR | G_TX_CLAMP,
                            G_TX_NOMIRROR | G_TX_CLAMP, 5, 5, G_TX_NOLOD, G_TX_NOLOD),
    gsSPVertex(&object_link_deityVtx_000C00[842], 4, 0),
    gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
    gsSPEndDisplayList(),
};

Gfx gLinkFierceDeityLeftShoulderDL[] = {
    gsSPMatrix(0x0D000440, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&object_link_deityVtx_000C00[719], 4, 0),
    gsSPVertex(&object_link_deityVtx_000C00[723], 1, 4),
    gsSPMatrix(0x0D000280, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPPipeSync(),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPSetTextureLUT(G_TT_RGBA16),
    gsDPLoadTLUT_pal16(15, object_link_deity_TLUT_008128),
    gsDPLoadTextureBlock_4b(object_link_deity_Tex_008C88, G_IM_FMT_CI, 16, 16, 15, G_TX_NOMIRROR | G_TX_CLAMP,
                            G_TX_NOMIRROR | G_TX_CLAMP, 4, 4, G_TX_NOLOD, G_TX_NOLOD),
    gsDPSetPrimColor(0, 0x80, 255, 255, 255, 255),
    gsSPVertex(&object_link_deityVtx_000C00[724], 15, 5),
    gsSP2Triangles(5, 6, 3, 0, 2, 7, 8, 0),
    gsSP2Triangles(9, 10, 4, 0, 3, 1, 11, 0),
    gsSP2Triangles(3, 12, 2, 0, 4, 13, 14, 0),
    gsSP2Triangles(3, 15, 16, 0, 0, 2, 17, 0),
    gsSP2Triangles(4, 0, 18, 0, 19, 1, 4, 0),
    gsSPVertex(&object_link_deityVtx_000C00[739], 12, 0),
    gsSP2Triangles(0, 1, 2, 0, 3, 4, 5, 0),
    gsSP2Triangles(6, 7, 8, 0, 9, 0, 2, 0),
    gsSP2Triangles(10, 7, 6, 0, 6, 9, 10, 0),
    gsSP2Triangles(2, 11, 9, 0, 9, 11, 10, 0),
    gsDPPipeSync(),
    gsDPLoadTLUT_pal16(15, object_link_deity_TLUT_008108),
    gsDPLoadTextureBlock_4b(object_link_deity_Tex_008408, G_IM_FMT_CI, 16, 16, 15, G_TX_MIRROR | G_TX_CLAMP, G_TX_NOMIRROR
                            | G_TX_CLAMP, 4, 4, G_TX_NOLOD, G_TX_NOLOD),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 0x007C, 0x003C),
    gsSPVertex(&object_link_deityVtx_000C00[751], 7, 0),
    gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
    gsSP2Triangles(4, 5, 6, 0, 3, 2, 6, 0),
    gsSP1Triangle(3, 6, 5, 0),
    gsSPVertex(&object_link_deityVtx_000C00[758], 7, 0),
    gsSP2Triangles(0, 1, 2, 0, 0, 3, 4, 0),
    gsSP2Triangles(5, 4, 3, 0, 4, 6, 0, 0),
    gsSP1Triangle(0, 6, 1, 0),
    gsSPEndDisplayList(),
};

Gfx gLinkFierceDeityLeftForearmDL[] = {
    gsSPMatrix(0x0D000280, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&object_link_deityVtx_000C00[672], 1, 0),
    gsSPVertex(&object_link_deityVtx_000C00[673], 6, 1),
    gsSPMatrix(0x0D0002C0, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPPipeSync(),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPSetTextureLUT(G_TT_RGBA16),
    gsDPLoadTLUT_pal16(15, object_link_deity_TLUT_008108),
    gsDPLoadTextureBlock_4b(object_link_deity_Tex_008408, G_IM_FMT_CI, 16, 16, 15, G_TX_MIRROR | G_TX_CLAMP, G_TX_NOMIRROR
                            | G_TX_CLAMP, 4, 4, G_TX_NOLOD, G_TX_NOLOD),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 0x007C, 0x003C),
    gsDPSetPrimColor(0, 0x80, 255, 255, 255, 255),
    gsSPVertex(&object_link_deityVtx_000C00[679], 6, 7),
    gsSP2Triangles(3, 0, 7, 0, 8, 0, 2, 0),
    gsSP2Triangles(9, 10, 3, 0, 2, 11, 12, 0),
    gsSPVertex(&object_link_deityVtx_000C00[685], 11, 7),
    gsSP2Triangles(7, 8, 1, 0, 4, 9, 10, 0),
    gsSP2Triangles(4, 11, 12, 0, 1, 6, 13, 0),
    gsSP2Triangles(14, 5, 4, 0, 15, 6, 5, 0),
    gsSP1Triangle(16, 5, 17, 0),
    gsDPPipeSync(),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPLoadTLUT_pal16(15, object_link_deity_TLUT_0081A8),
    gsDPLoadTextureBlock_4b(object_link_deity_Tex_00AF08, G_IM_FMT_CI, 32, 32, 15, G_TX_MIRROR | G_TX_WRAP, G_TX_NOMIRROR
                            | G_TX_WRAP, 5, 5, G_TX_NOLOD, G_TX_NOLOD),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 0x01FC, 0x007C),
    gsSPVertex(&object_link_deityVtx_000C00[696], 18, 0),
    gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
    gsSP2Triangles(4, 5, 6, 0, 4, 6, 7, 0),
    gsSP2Triangles(8, 9, 10, 0, 8, 10, 11, 0),
    gsSP2Triangles(7, 6, 12, 0, 7, 12, 13, 0),
    gsSP2Triangles(5, 14, 15, 0, 12, 6, 15, 0),
    gsSP2Triangles(15, 10, 9, 0, 9, 12, 15, 0),
    gsSP2Triangles(15, 6, 5, 0, 16, 14, 5, 0),
    gsSP2Triangles(13, 12, 9, 0, 13, 9, 8, 0),
    gsSP2Triangles(16, 5, 4, 0, 0, 17, 1, 0),
    gsDPPipeSync(),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPLoadTLUT_pal16(15, object_link_deity_TLUT_008108),
    gsDPLoadTextureBlock_4b(object_link_deity_Tex_008408, G_IM_FMT_CI, 16, 16, 15, G_TX_MIRROR | G_TX_CLAMP, G_TX_NOMIRROR
                            | G_TX_CLAMP, 4, 4, G_TX_NOLOD, G_TX_NOLOD),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 0x007C, 0x003C),
    gsSPVertex(&object_link_deityVtx_000C00[714], 5, 0),
    gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
    gsSP1Triangle(3, 2, 4, 0),
    gsSPEndDisplayList(),
};

Gfx gLinkFierceDeityLeftHandDL[] = {
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPPipeSync(),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPSetTextureLUT(G_TT_RGBA16),
    gsDPLoadTLUT_pal16(15, object_link_deity_TLUT_0081A8),
    gsDPLoadTextureBlock_4b(object_link_deity_Tex_00AF08, G_IM_FMT_CI, 32, 32, 15, G_TX_NOMIRROR | G_TX_CLAMP,
                            G_TX_NOMIRROR | G_TX_CLAMP, 5, 5, G_TX_NOLOD, G_TX_NOLOD),
    gsDPSetPrimColor(0, 0x80, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&object_link_deityVtx_000C00[615], 6, 0),
    gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
    gsSP2Triangles(4, 0, 3, 0, 4, 3, 5, 0),
    gsSPVertex(&object_link_deityVtx_000C00[621], 7, 0),
    gsSP2Triangles(0, 1, 2, 0, 3, 4, 5, 0),
    gsSP2Triangles(5, 6, 3, 0, 2, 6, 0, 0),
    gsSP1Triangle(6, 5, 0, 0),
    gsSPVertex(&object_link_deityVtx_000C00[628], 6, 0),
    gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
    gsSP2Triangles(3, 2, 4, 0, 5, 3, 4, 0),
    gsSPVertex(&object_link_deityVtx_000C00[634], 11, 0),
    gsSP2Triangles(0, 1, 2, 0, 3, 4, 5, 0),
    gsSP2Triangles(1, 6, 5, 0, 3, 6, 7, 0),
    gsSP2Triangles(0, 6, 1, 0, 1, 8, 2, 0),
    gsSP2Triangles(6, 3, 5, 0, 9, 3, 10, 0),
    gsSP1Triangle(7, 10, 3, 0),
    gsDPPipeSync(),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPLoadTLUT_pal16(15, gLinkFierceDeityHandTLUT),
    gsDPLoadTextureBlock_4b(gLinkFierceDeityHandTex, G_IM_FMT_CI, 16, 16, 15, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR
                            | G_TX_CLAMP, 4, 4, G_TX_NOLOD, G_TX_NOLOD),
    gsSPVertex(&object_link_deityVtx_000C00[645], 12, 0),
    gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
    gsSP2Triangles(4, 5, 3, 0, 6, 4, 2, 0),
    gsSP2Triangles(6, 2, 1, 0, 4, 6, 7, 0),
    gsSP2Triangles(4, 7, 5, 0, 8, 9, 10, 0),
    gsSP2Triangles(8, 10, 11, 0, 4, 3, 2, 0),
    gsSPVertex(&object_link_deityVtx_000C00[657], 11, 0),
    gsSP2Triangles(0, 1, 2, 0, 3, 4, 5, 0),
    gsSP2Triangles(6, 7, 8, 0, 9, 2, 1, 0),
    gsSP2Triangles(1, 6, 9, 0, 8, 10, 6, 0),
    gsSP2Triangles(2, 3, 5, 0, 2, 9, 3, 0),
    gsDPPipeSync(),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetTextureLUT(G_TT_NONE),
    gsDPLoadTextureBlock(object_link_deity_Tex_00B988, G_IM_FMT_RGBA, G_IM_SIZ_16b, 50, 75, 0, G_TX_NOMIRROR | G_TX_CLAMP,
                         G_TX_NOMIRROR | G_TX_CLAMP, 6, 7, G_TX_NOLOD, G_TX_NOLOD),
    gsSPVertex(&object_link_deityVtx_000C00[668], 4, 0),
    gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
    gsSPEndDisplayList(),
};

Vtx object_link_deityVtx_007110[] = {
#include "assets/objects/object_link_deity/object_link_deityVtx_007110.vtx.inc"
};

Gfx gLinkFierceDeityLeftHandHoldBottleDL[] = {
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPPipeSync(),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPPipeSync(),
    gsDPSetTextureLUT(G_TT_RGBA16),
    gsDPLoadTLUT_pal256(gLinkFierceDeityHandHoldingTLUT),
    gsDPLoadTextureBlock(gLinkFierceDeityHandHoldingTex, G_IM_FMT_CI, G_IM_SIZ_8b, 16, 16, 0, G_TX_MIRROR | G_TX_CLAMP,
                         G_TX_MIRROR | G_TX_CLAMP, 4, 4, G_TX_NOLOD, G_TX_NOLOD),
    gsDPSetPrimColor(0, 0x80, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(object_link_deityVtx_007110, 22, 0),
    gsSP2Triangles(0, 1, 2, 0, 1, 3, 4, 0),
    gsSP2Triangles(0, 3, 1, 0, 5, 6, 7, 0),
    gsSP2Triangles(8, 9, 10, 0, 7, 11, 5, 0),
    gsSP2Triangles(11, 10, 5, 0, 11, 8, 10, 0),
    gsSP2Triangles(11, 7, 8, 0, 12, 13, 2, 0),
    gsSP2Triangles(14, 15, 16, 0, 17, 18, 4, 0),
    gsSP2Triangles(17, 12, 18, 0, 2, 18, 12, 0),
    gsSP2Triangles(19, 4, 3, 0, 4, 19, 17, 0),
    gsSP2Triangles(1, 18, 2, 0, 1, 4, 18, 0),
    gsSP2Triangles(20, 19, 21, 0, 17, 20, 12, 0),
    gsSP1Triangle(17, 19, 20, 0),
    gsDPPipeSync(),
    gsDPLoadTLUT_pal256(object_link_deity_TLUT_000200),
    gsDPLoadTextureBlock(object_link_deity_Tex_000800, G_IM_FMT_CI, G_IM_SIZ_8b, 16, 32, 0, G_TX_MIRROR | G_TX_WRAP,
                         G_TX_MIRROR | G_TX_WRAP, 4, 5, G_TX_NOLOD, G_TX_NOLOD),
    gsSPVertex(&object_link_deityVtx_007110[22], 4, 0),
    gsSP2Triangles(0, 1, 2, 0, 2, 1, 3, 0),
    gsDPPipeSync(),
    gsDPLoadTLUT_pal256(object_link_deity_TLUT_000000),
    gsDPLoadTextureBlock(object_link_deity_Tex_000600, G_IM_FMT_CI, G_IM_SIZ_8b, 16, 32, 0, G_TX_MIRROR | G_TX_WRAP,
                         G_TX_MIRROR | G_TX_WRAP, 4, 5, G_TX_NOLOD, G_TX_NOLOD),
    gsSPVertex(&object_link_deityVtx_007110[26], 15, 0),
    gsSP2Triangles(0, 1, 2, 0, 3, 4, 5, 0),
    gsSP2Triangles(6, 7, 8, 0, 0, 9, 1, 0),
    gsSP2Triangles(10, 11, 12, 0, 11, 5, 13, 0),
    gsSP2Triangles(10, 5, 11, 0, 14, 7, 6, 0),
    gsSP2Triangles(5, 4, 13, 0, 3, 5, 10, 0),
    gsSPEndDisplayList(),
};

Gfx object_link_deity_DL_007A50[] = {
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPPipeSync(),
    gsDPSetCombineLERP(0, 0, 0, ENVIRONMENT, 0, 0, 0, PRIMITIVE, COMBINED, 0, SHADE, 0, 0, 0, 0, COMBINED),
    gsDPSetPrimColor(0, 0xFF, 255, 255, 255, 255),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&object_link_deityVtx_007110[41], 10, 0),
    gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
    gsSP2Triangles(0, 3, 4, 0, 0, 5, 6, 0),
    gsSP2Triangles(0, 6, 1, 0, 6, 7, 2, 0),
    gsSP2Triangles(6, 2, 1, 0, 8, 4, 3, 0),
    gsSP2Triangles(9, 4, 8, 0, 4, 9, 0, 0),
    gsSP2Triangles(0, 9, 5, 0, 7, 8, 3, 0),
    gsSP2Triangles(7, 3, 2, 0, 7, 6, 5, 0),
    gsSP2Triangles(7, 5, 9, 0, 7, 9, 8, 0),
    gsSPEndDisplayList(),
};

Vtx object_link_deityVtx_00EFB8[] = {
#include "assets/objects/object_link_deity/object_link_deityVtx_00EFB8.vtx.inc"
};

Gfx gLinkFierceDeityBottleDL[] = {
    gsDPPipeSync(),
    gsDPSetTextureLUT(G_TT_NONE),
    gsSPTexture(0x05DC, 0x05DC, 0, G_TX_RENDERTILE, G_ON),
    gsDPLoadTextureBlock(gBottleGlassTex, G_IM_FMT_RGBA, G_IM_SIZ_16b, 16, 16, 0, G_TX_MIRROR | G_TX_WRAP, G_TX_MIRROR |
                         G_TX_WRAP, 4, 4, G_TX_NOLOD, G_TX_NOLOD),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, PRIMITIVE, COMBINED, 0, ENVIRONMENT, 0, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_XLU_SURF2),
    gsSPSetGeometryMode(G_FOG | G_LIGHTING | G_TEXTURE_GEN | G_TEXTURE_GEN_LINEAR),
    gsSPDisplayList(0x0C000000),
    gsDPSetPrimColor(0, 0, 255, 255, 255, 178),
    gsSPVertex(&object_link_deityVtx_00EFB8[4466], 3, 0),
    gsSP1Triangle(0, 1, 2, 0),
    gsSPVertex(&object_link_deityVtx_00EFB8[4469], 13, 0),
    gsSP2Triangles(0, 1, 2, 0, 3, 4, 5, 0),
    gsSP2Triangles(3, 6, 7, 0, 5, 8, 3, 0),
    gsSP2Triangles(5, 9, 8, 0, 1, 9, 5, 0),
    gsSP2Triangles(1, 10, 9, 0, 8, 6, 3, 0),
    gsSP2Triangles(11, 6, 8, 0, 12, 1, 0, 0),
    gsSP1Triangle(12, 10, 1, 0),
    gsDPPipeSync(),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, PRIMITIVE, COMBINED, 0, PRIMITIVE, 0, 0, 0, 0, COMBINED),
    gsDPSetPrimColor(0, 0, 255, 255, 255, 204),
    gsSPVertex(&object_link_deityVtx_00EFB8[4482], 12, 0),
    gsSP2Triangles(0, 1, 2, 0, 3, 1, 0, 0),
    gsSP2Triangles(1, 3, 4, 0, 4, 3, 5, 0),
    gsSP2Triangles(4, 5, 6, 0, 4, 6, 7, 0),
    gsSP2Triangles(6, 8, 9, 0, 6, 9, 7, 0),
    gsSP2Triangles(6, 5, 3, 0, 6, 3, 0, 0),
    gsSP2Triangles(10, 1, 11, 0, 10, 11, 7, 0),
    gsSPEndDisplayList(),
};

Vtx object_link_deityVtx_007BE8[] = {
#include "assets/objects/object_link_deity/object_link_deityVtx_007BE8.vtx.inc"
};

Gfx gLinkFierceDeitySwordDL[] = {
    gsSPTexture(0x03E8, 0x01F4, 0, G_TX_RENDERTILE, G_ON),
    gsDPPipeSync(),
    gsDPSetCombineLERP(TEXEL0, ENVIRONMENT, SHADE, PRIMITIVE, TEXEL0, 0, PRIMITIVE, 0, COMBINED, 0, SHADE, 0, 0, 0, 0,
                       COMBINED),
    gsDPSetPrimColor(0, 0xFF, 128, 128, 128, 255),
    gsDPSetEnvColor(0, 20, 80, 255),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetTextureLUT(G_TT_NONE),
    gsDPLoadTextureBlock(object_link_deity_Tex_000B00, G_IM_FMT_I, G_IM_SIZ_8b, 16, 16, 0, G_TX_MIRROR | G_TX_WRAP,
                         G_TX_MIRROR | G_TX_WRAP, 4, 4, 1, G_TX_NOLOD),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_TEXTURE_GEN | G_TEXTURE_GEN_LINEAR |
                         G_SHADING_SMOOTH),
    gsSPVertex(&object_link_deityVtx_007BE8[20], 32, 0),
    gsSP2Triangles(0, 1, 2, 0, 2, 1, 3, 0),
    gsSP2Triangles(2, 4, 5, 0, 3, 4, 2, 0),
    gsSP2Triangles(6, 7, 8, 0, 7, 9, 8, 0),
    gsSP2Triangles(7, 10, 9, 0, 7, 11, 10, 0),
    gsSP2Triangles(7, 12, 13, 0, 14, 7, 13, 0),
    gsSP2Triangles(7, 15, 12, 0, 7, 6, 15, 0),
    gsSP2Triangles(15, 16, 12, 0, 15, 17, 16, 0),
    gsSP2Triangles(17, 18, 16, 0, 17, 19, 18, 0),
    gsSP2Triangles(19, 20, 18, 0, 20, 21, 18, 0),
    gsSP2Triangles(22, 23, 19, 0, 22, 24, 23, 0),
    gsSP2Triangles(21, 25, 18, 0, 26, 10, 27, 0),
    gsSP2Triangles(10, 11, 27, 0, 8, 27, 6, 0),
    gsSP2Triangles(8, 26, 27, 0, 22, 25, 24, 0),
    gsSP2Triangles(28, 22, 17, 0, 22, 19, 17, 0),
    gsSP2Triangles(29, 28, 15, 0, 28, 17, 15, 0),
    gsSP2Triangles(30, 29, 27, 0, 30, 27, 31, 0),
    gsSP2Triangles(29, 15, 27, 0, 15, 6, 27, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_TEXTURE_GEN | G_TEXTURE_GEN_LINEAR |
                         G_SHADING_SMOOTH),
    gsSP2Triangles(8, 9, 10, 0, 8, 10, 26, 0),
    gsDPPipeSync(),
    gsDPSetEnvColor(138, 20, 90, 255),
    gsDPLoadTextureBlock(object_link_deity_Tex_000B00, G_IM_FMT_I, G_IM_SIZ_8b, 16, 16, 0, G_TX_MIRROR | G_TX_WRAP,
                         G_TX_MIRROR | G_TX_WRAP, 4, 4, G_TX_NOLOD, G_TX_NOLOD),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_TEXTURE_GEN | G_TEXTURE_GEN_LINEAR |
                         G_SHADING_SMOOTH),
    gsSPVertex(object_link_deityVtx_007BE8, 20, 0),
    gsSP2Triangles(0, 1, 2, 0, 0, 3, 1, 0),
    gsSP2Triangles(4, 3, 0, 0, 5, 4, 0, 0),
    gsSP2Triangles(6, 7, 8, 0, 7, 9, 8, 0),
    gsSP2Triangles(7, 10, 9, 0, 10, 11, 9, 0),
    gsSP2Triangles(10, 12, 11, 0, 12, 13, 11, 0),
    gsSP2Triangles(9, 14, 15, 0, 9, 11, 14, 0),
    gsSP2Triangles(11, 16, 14, 0, 11, 13, 16, 0),
    gsSP2Triangles(8, 9, 15, 0, 8, 15, 6, 0),
    gsSP2Triangles(12, 17, 13, 0, 12, 18, 17, 0),
    gsSP2Triangles(13, 19, 16, 0, 19, 18, 16, 0),
    gsSPEndDisplayList(),
};

Gfx gLinkFierceDeityLeftHandHoldingSwordDL[] = {
    gsSPDisplayList(gLinkFierceDeityLeftHandDL),
    gsSPBranchList(gLinkFierceDeitySwordDL),
};

Gfx gLinkFierceDeityEmptyDL[] = {
    gsSPEndDisplayList(),
};

u64 object_link_deity_TLUT_008108[] = {
#include "assets/objects/object_link_deity/tlut_008108.rgba16.inc.c"
};

u64 object_link_deity_TLUT_008128[] = {
#include "assets/objects/object_link_deity/tlut_008128.rgba16.inc.c"
};

u64 object_link_deity_TLUT_008148[] = {
#include "assets/objects/object_link_deity/tlut_008148.rgba16.inc.c"
};

u64 object_link_deity_TLUT_008168[] = {
#include "assets/objects/object_link_deity/tlut_008168.rgba16.inc.c"
};

u64 object_link_deity_TLUT_008188[] = {
#include "assets/objects/object_link_deity/tlut_008188.rgba16.inc.c"
};

u64 object_link_deity_TLUT_0081A8[] = {
#include "assets/objects/object_link_deity/tlut_0081A8.rgba16.inc.c"
};

u64 gLinkFierceDeityHandTLUT[] = {
#include "assets/objects/object_link_deity/hand_tlut.rgba16.inc.c"
};

u64 object_link_deity_TLUT_0081E8[] = {
#include "assets/objects/object_link_deity/tlut_0081E8.rgba16.inc.c"
};

u64 object_link_deity_Tex_008208[] = {
#include "assets/objects/object_link_deity/tex_008208.rgba16.inc.c"
};

u64 object_link_deity_Tex_008408[] = {
#include "assets/objects/object_link_deity/tex_008408.ci4.inc.c"
};

u64 object_link_deity_Tex_008488[] = {
#include "assets/objects/object_link_deity/tex_008488.rgba16.inc.c"
};

u64 object_link_deity_Tex_008888[] = {
#include "assets/objects/object_link_deity/tex_008888.rgba16.inc.c"
};

u64 object_link_deity_Tex_008C88[] = {
#include "assets/objects/object_link_deity/tex_008C88.ci4.inc.c"
};

u64 object_link_deity_Tex_008D08[] = {
#include "assets/objects/object_link_deity/tex_008D08.ci4.inc.c"
};

u64 object_link_deity_Tex_008F08[] = {
#include "assets/objects/object_link_deity/tex_008F08.ci4.inc.c"
};

u64 gLinkFierceDeityEyesTex[] = {
#include "assets/objects/object_link_deity/eyes.rgba16.inc.c"
};

u64 object_link_deity_Tex_00A708[] = {
#include "assets/objects/object_link_deity/tex_00A708.ci4.inc.c"
};

u64 gLinkFierceDeityMouthTex[] = {
#include "assets/objects/object_link_deity/mouth.rgba16.inc.c"
};

u64 gLinkFierceDeityEarTex[] = {
#include "assets/objects/object_link_deity/ear.rgba16.inc.c"
};

u64 object_link_deity_Tex_00AF08[] = {
#include "assets/objects/object_link_deity/tex_00AF08.ci4.inc.c"
};

u64 gLinkFierceDeityHandTex[] = {
#include "assets/objects/object_link_deity/hand.ci4.inc.c"
};

u64 object_link_deity_Tex_00B188[] = {
#include "assets/objects/object_link_deity/tex_00B188.ci4.inc.c"
};

u64 object_link_deity_Tex_00B988[] = {
#include "assets/objects/object_link_deity/tex_00B988.rgba16.inc.c"
};

u8 object_link_deity_unaccounted_00D670[] = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
};

LodLimb gLinkFierceDeityRootLimb = { 
    { -57, 3377, 0 }, LINK_FIERCE_DEITY_LIMB_WAIST - 1, LIMB_DONE,
    { NULL, NULL }
};

LodLimb gLinkFierceDeityWaistLimb = { 
    { 0, 0, 0 }, LINK_FIERCE_DEITY_LIMB_LOWER_ROOT - 1, LINK_FIERCE_DEITY_LIMB_UPPER_ROOT - 1,
    { gLinkFierceDeityWaistDL, gLinkFierceDeityWaistDL }
};

LodLimb gLinkFierceDeityLowerRootLimb = { 
    { 945, 0, 0 }, LINK_FIERCE_DEITY_LIMB_RIGHT_THIGH - 1, LIMB_DONE,
    { NULL, NULL }
};

LodLimb gLinkFierceDeityRightThighLimb = { 
    { -399, 69, -249 }, LINK_FIERCE_DEITY_LIMB_RIGHT_SHIN - 1, LINK_FIERCE_DEITY_LIMB_LEFT_THIGH - 1,
    { gLinkFierceDeityRightThighDL, gLinkFierceDeityRightThighDL }
};

LodLimb gLinkFierceDeityRightShinLimb = { 
    { 1306, 0, 0 }, LINK_FIERCE_DEITY_LIMB_RIGHT_FOOT - 1, LIMB_DONE,
    { gLinkFierceDeityRightShinDL, gLinkFierceDeityRightShinDL }
};

LodLimb gLinkFierceDeityRightFootLimb = { 
    { 1256, 5, 11 }, LIMB_DONE, LIMB_DONE,
    { gLinkFierceDeityRightFootDL, gLinkFierceDeityRightFootDL }
};

LodLimb gLinkFierceDeityLeftThighLimb = { 
    { -396, 76, 264 }, LINK_FIERCE_DEITY_LIMB_LEFT_SHIN - 1, LIMB_DONE,
    { gLinkFierceDeityLeftThighDL, gLinkFierceDeityLeftThighDL }
};

LodLimb gLinkFierceDeityLeftShinLimb = { 
    { 1304, 0, 0 }, LINK_FIERCE_DEITY_LIMB_LEFT_FOOT - 1, LIMB_DONE,
    { gLinkFierceDeityLeftShinDL, gLinkFierceDeityLeftShinDL }
};

LodLimb gLinkFierceDeityLeftFootLimb = { 
    { 1257, 6, 3 }, LIMB_DONE, LIMB_DONE,
    { gLinkFierceDeityLeftFootDL, gLinkFierceDeityLeftFootDL }
};

LodLimb gLinkFierceDeityUpperRootLimb = { 
    { 0, 21, -7 }, LINK_FIERCE_DEITY_LIMB_HEAD - 1, LIMB_DONE,
    { NULL, NULL }
};

LodLimb gLinkFierceDeityHeadLimb = { 
    { 1392, -259, 0 }, LINK_FIERCE_DEITY_LIMB_HAT - 1, LINK_FIERCE_DEITY_LIMB_COLLAR - 1,
    { gLinkFierceDeityHeadDL, gLinkFierceDeityHeadDL }
};

LodLimb gLinkFierceDeityHatLimb = { 
    { -298, -700, 0 }, LIMB_DONE, LIMB_DONE,
    { gLinkFierceDeityHatDL, gLinkFierceDeityHatDL }
};

LodLimb gLinkFierceDeityCollarLimb = { 
    { 0, 0, 0 }, LIMB_DONE, LINK_FIERCE_DEITY_LIMB_LEFT_SHOULDER - 1,
    { gLinkFierceDeityEmptyDL, gLinkFierceDeityEmptyDL }
};

LodLimb gLinkFierceDeityLeftShoulderLimb = { 
    { 1039, -172, 680 }, LINK_FIERCE_DEITY_LIMB_LEFT_FOREARM - 1, LINK_FIERCE_DEITY_LIMB_RIGHT_SHOULDER - 1,
    { gLinkFierceDeityLeftShoulderDL, gLinkFierceDeityLeftShoulderDL }
};

LodLimb gLinkFierceDeityLeftForearmLimb = { 
    { 919, 0, 0 }, LINK_FIERCE_DEITY_LIMB_LEFT_HAND - 1, LIMB_DONE,
    { gLinkFierceDeityLeftForearmDL, gLinkFierceDeityLeftForearmDL }
};

LodLimb gLinkFierceDeityLeftHandLimb = { 
    { 754, 0, 0 }, LIMB_DONE, LIMB_DONE,
    { gLinkFierceDeityLeftHandDL, gLinkFierceDeityLeftHandDL }
};

LodLimb gLinkFierceDeityRightShoulderLimb = { 
    { 1039, -173, -680 }, LINK_FIERCE_DEITY_LIMB_RIGHT_FOREARM - 1, LINK_FIERCE_DEITY_LIMB_SHEATH - 1,
    { gLinkFierceDeityRightShoulderDL, gLinkFierceDeityRightShoulderDL }
};

LodLimb gLinkFierceDeityRightForearmLimb = { 
    { 919, 0, 0 }, LINK_FIERCE_DEITY_LIMB_RIGHT_HAND - 1, LIMB_DONE,
    { gLinkFierceDeityRightForearmDL, gLinkFierceDeityRightForearmDL }
};

LodLimb gLinkFierceDeityRightHandLimb = { 
    { 754, 0, 0 }, LIMB_DONE, LIMB_DONE,
    { gLinkFierceDeityRightHandDL, gLinkFierceDeityRightHandDL }
};

LodLimb gLinkFierceDeitySheathLimb = { 
    { 978, -692, 342 }, LIMB_DONE, LINK_FIERCE_DEITY_LIMB_TORSO - 1,
    { gLinkFierceDeityEmptyDL, gLinkFierceDeityEmptyDL }
};

LodLimb gLinkFierceDeityTorsoLimb = { 
    { 0, 0, 0 }, LIMB_DONE, LIMB_DONE,
    { gLinkFierceDeityTorsoDL, gLinkFierceDeityTorsoDL }
};

void* gLinkFierceDeitySkelLimbs[] = {
    &gLinkFierceDeityRootLimb, /* LINK_FIERCE_DEITY_LIMB_ROOT */
    &gLinkFierceDeityWaistLimb, /* LINK_FIERCE_DEITY_LIMB_WAIST */
    &gLinkFierceDeityLowerRootLimb, /* LINK_FIERCE_DEITY_LIMB_LOWER_ROOT */
    &gLinkFierceDeityRightThighLimb, /* LINK_FIERCE_DEITY_LIMB_RIGHT_THIGH */
    &gLinkFierceDeityRightShinLimb, /* LINK_FIERCE_DEITY_LIMB_RIGHT_SHIN */
    &gLinkFierceDeityRightFootLimb, /* LINK_FIERCE_DEITY_LIMB_RIGHT_FOOT */
    &gLinkFierceDeityLeftThighLimb, /* LINK_FIERCE_DEITY_LIMB_LEFT_THIGH */
    &gLinkFierceDeityLeftShinLimb, /* LINK_FIERCE_DEITY_LIMB_LEFT_SHIN */
    &gLinkFierceDeityLeftFootLimb, /* LINK_FIERCE_DEITY_LIMB_LEFT_FOOT */
    &gLinkFierceDeityUpperRootLimb, /* LINK_FIERCE_DEITY_LIMB_UPPER_ROOT */
    &gLinkFierceDeityHeadLimb, /* LINK_FIERCE_DEITY_LIMB_HEAD */
    &gLinkFierceDeityHatLimb, /* LINK_FIERCE_DEITY_LIMB_HAT */
    &gLinkFierceDeityCollarLimb, /* LINK_FIERCE_DEITY_LIMB_COLLAR */
    &gLinkFierceDeityLeftShoulderLimb, /* LINK_FIERCE_DEITY_LIMB_LEFT_SHOULDER */
    &gLinkFierceDeityLeftForearmLimb, /* LINK_FIERCE_DEITY_LIMB_LEFT_FOREARM */
    &gLinkFierceDeityLeftHandLimb, /* LINK_FIERCE_DEITY_LIMB_LEFT_HAND */
    &gLinkFierceDeityRightShoulderLimb, /* LINK_FIERCE_DEITY_LIMB_RIGHT_SHOULDER */
    &gLinkFierceDeityRightForearmLimb, /* LINK_FIERCE_DEITY_LIMB_RIGHT_FOREARM */
    &gLinkFierceDeityRightHandLimb, /* LINK_FIERCE_DEITY_LIMB_RIGHT_HAND */
    &gLinkFierceDeitySheathLimb, /* LINK_FIERCE_DEITY_LIMB_SHEATH */
    &gLinkFierceDeityTorsoLimb, /* LINK_FIERCE_DEITY_LIMB_TORSO */
};

FlexSkeletonHeader gLinkFierceDeitySkel = { 
    { gLinkFierceDeitySkelLimbs, ARRAY_COUNT(gLinkFierceDeitySkelLimbs) }, 18
};

