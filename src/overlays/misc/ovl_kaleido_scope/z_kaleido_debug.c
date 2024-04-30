#include "z_kaleido_scope.h"
#include "assets/textures/parameter_static/parameter_static.h"

// Positions of each input section in the editor
static u16 sSectionPositions[][2] = {
    { 64, 15 },   { 144, 15 },  { 170, 15 },  { 78, 35 },   { 104, 35 },  { 130, 35 },  { 156, 35 },  { 182, 35 },
    { 208, 35 },  { 78, 50 },   { 104, 50 },  { 130, 50 },  { 156, 50 },  { 182, 50 },  { 208, 50 },  { 78, 65 },
    { 104, 65 },  { 130, 65 },  { 156, 65 },  { 182, 65 },  { 208, 65 },  { 78, 80 },   { 104, 80 },  { 130, 80 },
    { 156, 80 },  { 182, 80 },  { 208, 80 },  { 78, 98 },   { 88, 98 },   { 98, 98 },   { 108, 98 },  { 118, 98 },
    { 128, 98 },  { 138, 98 },  { 148, 98 },  { 158, 98 },  { 168, 98 },  { 178, 98 },  { 188, 98 },  { 198, 98 },
    { 208, 98 },  { 218, 98 },  { 228, 98 },  { 238, 98 },  { 78, 115 },  { 90, 115 },  { 102, 115 }, { 114, 115 },
    { 126, 115 }, { 138, 115 }, { 150, 115 }, { 162, 115 }, { 202, 115 }, { 214, 115 }, { 226, 115 }, { 238, 115 },
    { 78, 132 },  { 90, 132 },  { 102, 132 }, { 114, 132 }, { 126, 132 }, { 138, 132 }, { 150, 132 }, { 162, 132 },
    { 174, 132 }, { 186, 132 }, { 198, 132 }, { 210, 132 }, { 78, 149 },  { 90, 149 },  { 102, 149 }, { 114, 149 },
    { 126, 149 }, { 138, 149 }, { 78, 166 },  { 90, 166 },  { 102, 166 }, { 114, 166 }, { 126, 166 }, { 138, 166 },
    { 150, 166 }, { 162, 166 }, { 174, 166 }, { 186, 166 }, { 198, 166 }, { 210, 166 }, { 210, 149 }, { 222, 149 },
    { 234, 149 }, { 78, 185 },  { 90, 185 },  { 145, 185 }, { 210, 185 },
};

// First section of each row in the editor (starting from the top)
static u16 sRowFirstSections[] = {
    0x00, 0x03, 0x1B, 0x2C, 0x34, 0x38, 0x44, 0x4A, 0x56, 0x59, 0x5C,
};

// Maximum value of each upgrade type
static u8 sMaxUpgradeValues[] = {
    3, 3, 3, 2, 2, 3, 3, 3,
};

// Item ID corresponding to each slot, aside from bottles and trade items
static s16 sSlotItems[] = {
    ITEM_DEKU_STICK, ITEM_DEKU_NUT,      ITEM_BOMB,       ITEM_BOW,      ITEM_ARROW_FIRE,  ITEM_DINS_FIRE,
    ITEM_SLINGSHOT,  ITEM_OCARINA_FAIRY, ITEM_BOMBCHU,    ITEM_HOOKSHOT, ITEM_ARROW_ICE,   ITEM_FARORES_WIND,
    ITEM_BOOMERANG,  ITEM_LENS_OF_TRUTH, ITEM_MAGIC_BEAN, ITEM_HAMMER,   ITEM_ARROW_LIGHT, ITEM_NAYRUS_LOVE,
};

void KaleidoScope_DrawDebugEditorText(Gfx** gfxp) {
    GfxPrint printer;
    s32 pad[2];

    GfxPrint_Init(&printer);
    GfxPrint_Open(&printer, *gfxp);

    GfxPrint_SetPos(&printer, 4, 2);
    GfxPrint_SetColor(&printer, 255, 60, 0, 255);
    GfxPrint_Printf(&printer, "%s", GFXP_KATAKANA "ﾙﾋﾟｰ"); // "Rupee"
    GfxPrint_SetPos(&printer, 15, 2);
    GfxPrint_Printf(&printer, "%s", GFXP_KATAKANA "ﾊｰﾄ"); // "Heart"
    GfxPrint_SetPos(&printer, 26, 3);
    GfxPrint_Printf(&printer, "%s", "/4");
    GfxPrint_SetPos(&printer, 4, 5);
    GfxPrint_Printf(&printer, "%s", GFXP_KATAKANA "ｱｲﾃﾑ"); // "Item"
    GfxPrint_SetPos(&printer, 4, 13);
    GfxPrint_Printf(&printer, "%s", "KEY");
    GfxPrint_SetPos(&printer, 4, 15);
    GfxPrint_Printf(&printer, "%s", GFXP_HIRAGANA "ｿｳﾋﾞ"); // "Equipment"
    GfxPrint_SetPos(&printer, 23, 14);
    GfxPrint_Printf(&printer, "%s", GFXP_KATAKANA "ｹﾝ"); // "Sword"
    GfxPrint_SetPos(&printer, 23, 15);
    GfxPrint_Printf(&printer, "%s", GFXP_KATAKANA "ﾀﾃ"); // "Shield"
    GfxPrint_SetPos(&printer, 4, 17);
    GfxPrint_Printf(&printer, "%s", "MAP");
    GfxPrint_SetPos(&printer, 4, 19);
    GfxPrint_Printf(&printer, "%s", GFXP_HIRAGANA "ﾌｳｲﾝ"); // "Seal"
    GfxPrint_SetPos(&printer, 20, 19);
    GfxPrint_Printf(&printer, "%s", GFXP_HIRAGANA "ｾｲﾚｲｾｷ"); // "Spiritual Stone"
    GfxPrint_SetPos(&printer, 4, 21);
    GfxPrint_Printf(&printer, "%s", GFXP_KATAKANA "ｵｶﾘﾅ"); // "Ocarina"
    GfxPrint_SetPos(&printer, 4, 24);
    GfxPrint_Printf(&printer, "%s", GFXP_KATAKANA "ｺﾚｸﾄ"); // "Collect"
    GfxPrint_SetPos(&printer, 14, 24);
    GfxPrint_Printf(&printer, "%s", GFXP_KATAKANA "ｷﾝｽﾀ"); // "Skulltula"
    GfxPrint_SetPos(&printer, 23, 24);
    GfxPrint_Printf(&printer, "%s", GFXP_KATAKANA "ｶｹﾗ"); // "Gold Token"
    GfxPrint_SetPos(&printer, 28, 24);
    GfxPrint_Printf(&printer, "%s", "/4");

    *gfxp = GfxPrint_Close(&printer);
    GfxPrint_Destroy(&printer);
}

void KaleidoScope_DrawDigit(PlayState* play, s32 digit, s32 rectLeft, s32 rectTop) {
    OPEN_DISPS(play->state.gfxCtx, "../z_kaleido_debug.c", 208);

    gDPLoadTextureBlock(POLY_OPA_DISP++, ((u8*)gCounterDigit0Tex + (8 * 16 * digit)), G_IM_FMT_I, G_IM_SIZ_8b, 8, 16, 0,
                        G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD,
                        G_TX_NOLOD);
    gSPTextureRectangle(POLY_OPA_DISP++, rectLeft << 2, rectTop << 2, (rectLeft + 8) << 2, (rectTop + 16) << 2,
                        G_TX_RENDERTILE, 0, 0, 1 << 10, 1 << 10);

    CLOSE_DISPS(play->state.gfxCtx, "../z_kaleido_debug.c", 220);
}

void KaleidoScope_DrawDebugEditor(PlayState* play) { // stub

}
