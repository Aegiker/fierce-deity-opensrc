#include "z_kaleido_scope.h"
#include "assets/textures/parameter_static/parameter_static.h"

u8 gAmmoItems[] = {
    ITEM_DEKU_STICK, ITEM_DEKU_NUT, ITEM_BOMB, ITEM_BOW,  ITEM_NONE, ITEM_NONE, ITEM_SLINGSHOT,  ITEM_NONE,
    ITEM_BOMBCHU,    ITEM_NONE,     ITEM_NONE, ITEM_NONE, ITEM_NONE, ITEM_NONE, ITEM_MAGIC_BEAN, ITEM_NONE,
};

#define ROW_LENGTH 6

static s16 sEquipState = 0;
static s16 sEquipAnimTimer = 0;
static s16 sEquipMoveTimer = 10;

static s16 sAmmoVtxOffset[] = {
    0, 2, 4, 6, 99, 99, 8, 99, 99, 10, 99, 99, 99, 99, 99, 99, 12,
};

static u8 sFierceDeityMaskFlag = 0;
#define CHECK_ITEM_SLOT_FD(index) (index == SLOT_TRADE_CHILD ? (sFierceDeityMaskFlag ? ITEM_MASK_DEITY : gSaveContext.inventory.items[index]) : gSaveContext.inventory.items[index])

Vtx* KaleidoScope_SetupAmmoVtx(PlayState* play, PauseContext* pauseCtx, s16 slot) {
    Vtx* ammoVtx = Graph_Alloc(play->state.gfxCtx, 8 * sizeof(Vtx));
    u8 quad;

    for (quad = 0; quad <= 4; quad += 4) {
        ammoVtx[quad + 0].v.ob[0] = ammoVtx[quad + 2].v.ob[0] = (-8 + 0xFFAA + (quad * 1.6)) + (0x20 * (slot % (ROW_LENGTH)));
        ammoVtx[quad + 1].v.ob[0] = ammoVtx[quad + 3].v.ob[0] = (8 + 0xFFAA + (quad * 1.6)) + (0x20 * (slot % (ROW_LENGTH)));
        ammoVtx[quad + 0].v.ob[1] = ammoVtx[quad + 1].v.ob[1] = (8 + 0x001A) - ((0x20 * (s16)(slot / (ROW_LENGTH)))) + pauseCtx->offsetY;
        ammoVtx[quad + 2].v.ob[1] = ammoVtx[quad + 3].v.ob[1] = (-8 + 0x001A)- ((0x20 * (s16)(slot / (ROW_LENGTH)))) + pauseCtx->offsetY;

        ammoVtx[quad + 0].v.ob[2] = ammoVtx[quad + 1].v.ob[2] =
            ammoVtx[quad + 2].v.ob[2] = ammoVtx[quad + 3].v.ob[2] = 0;

        ammoVtx[quad + 0].v.flag = ammoVtx[quad + 1].v.flag =
            ammoVtx[quad + 2].v.flag = ammoVtx[quad + 3].v.flag = 0;

        ammoVtx[quad + 0].v.tc[0] = ammoVtx[quad + 0].v.tc[1] =
            ammoVtx[quad + 1].v.tc[1] = ammoVtx[quad + 2].v.tc[0] = 0;
        ammoVtx[quad + 1].v.tc[0] = ammoVtx[quad + 2].v.tc[1] =
            ammoVtx[quad + 3].v.tc[0] = ammoVtx[quad + 3].v.tc[1] = 512;

        ammoVtx[quad + 0].v.cn[0] = ammoVtx[quad + 1].v.cn[0] =
            ammoVtx[quad + 2].v.cn[0] = ammoVtx[quad + 3].v.cn[0] =
                ammoVtx[quad + 0].v.cn[1] = ammoVtx[quad + 1].v.cn[1] =
                    ammoVtx[quad + 2].v.cn[1] = ammoVtx[quad + 3].v.cn[1] =
                        ammoVtx[quad + 0].v.cn[2] = ammoVtx[quad + 1].v.cn[2] =
                            ammoVtx[quad + 2].v.cn[2] = ammoVtx[quad + 3].v.cn[2] =
                                ammoVtx[quad + 0].v.cn[3] = ammoVtx[quad + 1].v.cn[3] =
                                    ammoVtx[quad + 2].v.cn[3] = ammoVtx[quad + 3].v.cn[3] =
                                        255;
    }

    return ammoVtx;

}

void KaleidoScope_DrawAmmoCount(PlayState* play, PauseContext* pauseCtx, GraphicsContext* gfxCtx, s16 item, s16 slot) {
    s16 ammo;
    Vtx* ammoVtx;
    s16 i;

    OPEN_DISPS(gfxCtx, "../z_kaleido_item.c", 69);

    ammo = AMMO(item);

    gDPPipeSync(POLY_OPA_DISP++);

    if (!Parameter_CanUseItem(item)) {
        gDPSetPrimColor(POLY_OPA_DISP++, 0, 0, 100, 100, 100, pauseCtx->alpha);
    } else {
        gDPSetPrimColor(POLY_OPA_DISP++, 0, 0, 255, 255, 255, pauseCtx->alpha);

        if (ammo == 0) {
            gDPSetPrimColor(POLY_OPA_DISP++, 0, 0, 130, 130, 130, pauseCtx->alpha);
        } else if ((item == ITEM_BOMB && AMMO(item) == CUR_CAPACITY(UPG_BOMB_BAG)) ||
                   (item == ITEM_BOW && AMMO(item) == CUR_CAPACITY(UPG_QUIVER)) ||
                   (item == ITEM_SLINGSHOT && AMMO(item) == CUR_CAPACITY(UPG_BULLET_BAG)) ||
                   (item == ITEM_DEKU_STICK && AMMO(item) == CUR_CAPACITY(UPG_DEKU_STICKS)) ||
                   (item == ITEM_DEKU_NUT && AMMO(item) == CUR_CAPACITY(UPG_DEKU_NUTS)) ||
                   (item == ITEM_BOMBCHU && ammo == 50) || (item == ITEM_MAGIC_BEAN && ammo == 15)) {
            gDPSetPrimColor(POLY_OPA_DISP++, 0, 0, 120, 255, 0, pauseCtx->alpha);
        }
    }

    for (i = 0; ammo >= 10; i++) {
        ammo -= 10;
    }

    gDPPipeSync(POLY_OPA_DISP++);
    ammoVtx = KaleidoScope_SetupAmmoVtx(play, pauseCtx, slot);

    // first digit
    if (i != 0) {
        gSPVertex(POLY_OPA_DISP++, ammoVtx, 4, 0);

        gDPLoadTextureBlock(POLY_OPA_DISP++, ((u8*)gAmmoDigit0Tex + (8 * 8 * i)), G_IM_FMT_IA, G_IM_SIZ_8b, 8, 8, 0,
                            G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD,
                            G_TX_NOLOD);

        gSP1Quadrangle(POLY_OPA_DISP++, 0, 2, 3, 1, 0);
    }

    // second digit
    gSPVertex(POLY_OPA_DISP++, ammoVtx + 4, 4, 0);

    gDPLoadTextureBlock(POLY_OPA_DISP++, ((u8*)gAmmoDigit0Tex + (8 * 8 * ammo)), G_IM_FMT_IA, G_IM_SIZ_8b, 8, 8, 0,
                       G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD,
                        G_TX_NOLOD);

    gSP1Quadrangle(POLY_OPA_DISP++, 0, 2, 3, 1, 0);

    CLOSE_DISPS(gfxCtx, "../z_kaleido_item.c", 116);
}

void KaleidoScope_SetCursorVtx(PauseContext* pauseCtx, u16 index, Vtx* vtx) {
    pauseCtx->cursorVtx[0].v.ob[0] = vtx[index].v.ob[0];
    pauseCtx->cursorVtx[0].v.ob[1] = vtx[index].v.ob[1];
}

void KaleidoScope_SetItemCursorVtx(PauseContext* pauseCtx) {
    KaleidoScope_SetCursorVtx(pauseCtx, pauseCtx->cursorSlot[PAUSE_ITEM] * 4, pauseCtx->itemVtx);
}

void KaleidoScope_MaskTooltip(PlayState* this) {
    GraphicsContext* gfxCtx = this->state.gfxCtx;
    Gfx* gfx;
    Gfx* opaStart;
    GfxPrint printer;
    u16 i;
    u16 line;
    s32 pad;

    OPEN_DISPS(gfxCtx, "../z_kaleido_item.c", 628);

    GfxPrint_Init(&printer);
    opaStart = POLY_OPA_DISP;
    gfx = Graph_GfxPlusOne(POLY_OPA_DISP);

    gSPDisplayList(OVERLAY_DISP++, gfx);

    // draw background box
    gDPSetCombineMode(gfx++, G_CC_PRIMITIVE, G_CC_PRIMITIVE);
    gDPSetPrimColor(gfx++, 0, 0, 0, 0, 0, 220);
    gDPFillRectangle(gfx++, 1, 1, SCREEN_WIDTH, 30);
    gDPPipeSync(gfx++);
    gDPSetCombineLERP(gfx++, 0, 0, 0, PRIMITIVE, TEXEL0, 0, PRIMITIVE, 0, 0, 0, 0, PRIMITIVE, TEXEL0, 0,
                      PRIMITIVE, 0);

    GfxPrint_Open(&printer, gfx);
    
    line = 0;

    // print build version
    GfxPrint_SetColor(&printer, 255, 155, 255, 255);
    GfxPrint_SetPos(&printer, 9, 1);
    GfxPrint_Printf(&printer, "hold L to access mask");

    gfx = GfxPrint_Close(&printer);
    gSPEndDisplayList(gfx++);
    Graph_BranchDlist(opaStart, gfx);
    POLY_OPA_DISP = gfx;

    CLOSE_DISPS(gfxCtx, "../z_kaleido_item.c", 664);

    GfxPrint_Destroy(&printer);
}

void KaleidoScope_DrawItemSelect(PlayState* play) {
    static s16 magicArrowEffectsR[] = { 255, 100, 255 };
    static s16 magicArrowEffectsG[] = { 0, 100, 255 };
    static s16 magicArrowEffectsB[] = { 0, 255, 100 };
    Input* input = &play->state.input[0];
    PauseContext* pauseCtx = &play->pauseCtx;
    u16 i;
    u16 j;
    u16 cursorItem;
    u16 cursorSlot;
    u16 index;
    s16 cursorPoint;
    s16 cursorX;
    s16 cursorY;
    s16 oldCursorPoint;
    s16 moveCursorResult;

    OPEN_DISPS(play->state.gfxCtx, "../z_kaleido_item.c", 234);

    Gfx_SetupDL_42Opa(play->state.gfxCtx);

    gDPSetCombineMode(POLY_OPA_DISP++, G_CC_MODULATEIA_PRIM, G_CC_MODULATEIA_PRIM);

    pauseCtx->cursorColorSet = 0;
    pauseCtx->nameColorSet = 0;
    
    if ((pauseCtx->pageIndex == PAUSE_ITEM && CHECK_BTN_ALL(input->cur.button, BTN_L)) || gSaveContext.inventory.items[SLOT_TRADE_CHILD] == ITEM_NONE) {
        sFierceDeityMaskFlag = 1;
    } else {
        sFierceDeityMaskFlag = 0;
    }

    if ((pauseCtx->state == 6) && (pauseCtx->unk_1E4 == 0) && (pauseCtx->pageIndex == PAUSE_ITEM)) {
        if (gSaveContext.inventory.items[SLOT_TRADE_CHILD] != ITEM_NONE) {
            KaleidoScope_MaskTooltip(play);
        }

        moveCursorResult = 0;
        oldCursorPoint = pauseCtx->cursorPoint[PAUSE_ITEM];

        cursorItem = pauseCtx->cursorItem[PAUSE_ITEM];
        cursorSlot = pauseCtx->cursorSlot[PAUSE_ITEM];

        if (pauseCtx->cursorSpecialPos == 0) {
            pauseCtx->cursorColorSet = 4;

            /*
            if (cursorItem == PAUSE_ITEM_NONE) {
                pauseCtx->stickAdjX = 40;
            }*/

            if (ABS(pauseCtx->stickAdjX) > 30) {
                cursorPoint = pauseCtx->cursorPoint[PAUSE_ITEM];
                cursorX = pauseCtx->cursorX[PAUSE_ITEM];
                cursorY = pauseCtx->cursorY[PAUSE_ITEM];

                osSyncPrintf("now=%d  ccc=%d\n", cursorPoint, cursorItem);

                // Seems necessary to match
                if (pauseCtx->cursorX[PAUSE_ITEM]) {}
                if (CHECK_ITEM_SLOT_FD(pauseCtx->cursorPoint[PAUSE_ITEM])) {}

                while (moveCursorResult == 0) {
                    if (pauseCtx->stickAdjX < -30) {
                        if (pauseCtx->cursorX[PAUSE_ITEM] != 0) {
                            pauseCtx->cursorX[PAUSE_ITEM]--;
                            pauseCtx->cursorPoint[PAUSE_ITEM] -= 1;

                            if (1/*CHECK_ITEM_SLOT_FD(pauseCtx->cursorPoint[PAUSE_ITEM]) != ITEM_NONE*/) {
                                moveCursorResult = 1;
                            }
                        } else {
                            pauseCtx->cursorX[PAUSE_ITEM] = cursorX;
                            pauseCtx->cursorY[PAUSE_ITEM]++;

                            if (pauseCtx->cursorY[PAUSE_ITEM] >= 4) {
                                pauseCtx->cursorY[PAUSE_ITEM] = 0;
                            }

                            pauseCtx->cursorPoint[PAUSE_ITEM] =
                                pauseCtx->cursorX[PAUSE_ITEM] + (pauseCtx->cursorY[PAUSE_ITEM] * 6);

                            if (pauseCtx->cursorPoint[PAUSE_ITEM] >= 24) {
                                pauseCtx->cursorPoint[PAUSE_ITEM] = pauseCtx->cursorX[PAUSE_ITEM];
                            }

                            if (cursorY == pauseCtx->cursorY[PAUSE_ITEM]) {
                                pauseCtx->cursorX[PAUSE_ITEM] = cursorX;
                                pauseCtx->cursorPoint[PAUSE_ITEM] = cursorPoint;

                                KaleidoScope_MoveCursorToSpecialPos(play, PAUSE_CURSOR_PAGE_LEFT);

                                moveCursorResult = 2;
                            }
                        }
                    } else if (pauseCtx->stickAdjX > 30) {
                        if (pauseCtx->cursorX[PAUSE_ITEM] < 5) {
                            pauseCtx->cursorX[PAUSE_ITEM]++;
                            pauseCtx->cursorPoint[PAUSE_ITEM] += 1;

                            if (1/*CHECK_ITEM_SLOT_FD(pauseCtx->cursorPoint[PAUSE_ITEM]) != ITEM_NONE*/) {
                                moveCursorResult = 1;
                            }
                        } else {
                            pauseCtx->cursorX[PAUSE_ITEM] = cursorX;
                            pauseCtx->cursorY[PAUSE_ITEM]++;

                            if (pauseCtx->cursorY[PAUSE_ITEM] >= 4) {
                                pauseCtx->cursorY[PAUSE_ITEM] = 0;
                            }

                            pauseCtx->cursorPoint[PAUSE_ITEM] =
                                pauseCtx->cursorX[PAUSE_ITEM] + (pauseCtx->cursorY[PAUSE_ITEM] * 6);

                            if (pauseCtx->cursorPoint[PAUSE_ITEM] >= 24) {
                                pauseCtx->cursorPoint[PAUSE_ITEM] = pauseCtx->cursorX[PAUSE_ITEM];
                            }

                            if (cursorY == pauseCtx->cursorY[PAUSE_ITEM]) {
                                pauseCtx->cursorX[PAUSE_ITEM] = cursorX;
                                pauseCtx->cursorPoint[PAUSE_ITEM] = cursorPoint;

                                KaleidoScope_MoveCursorToSpecialPos(play, PAUSE_CURSOR_PAGE_RIGHT);

                                moveCursorResult = 2;
                            }
                        }
                    }
                }

                if (moveCursorResult == 1) {
                    cursorItem = CHECK_ITEM_SLOT_FD(pauseCtx->cursorPoint[PAUSE_ITEM]);
                }

                osSyncPrintf("【Ｘ cursor=%d(%) (cur_xpt=%d)(ok_fg=%d)(ccc=%d)(key_angle=%d)】  ",
                             pauseCtx->cursorPoint[PAUSE_ITEM], pauseCtx->cursorX[PAUSE_ITEM], moveCursorResult,
                             cursorItem, pauseCtx->cursorSpecialPos);
            }
        } else if (pauseCtx->cursorSpecialPos == PAUSE_CURSOR_PAGE_LEFT) {
            if (pauseCtx->stickAdjX > 30) {
                pauseCtx->nameDisplayTimer = 0;
                pauseCtx->cursorSpecialPos = 0;

                Audio_PlaySfxGeneral(NA_SE_SY_CURSOR, &gSfxDefaultPos, 4, &gSfxDefaultFreqAndVolScale,
                                     &gSfxDefaultFreqAndVolScale, &gSfxDefaultReverb);

                cursorPoint = cursorX = cursorY = 0;
                while (true) {
                    if (1/*CHECK_ITEM_SLOT_FD(cursorPoint) != ITEM_NONE*/) {
                        pauseCtx->cursorPoint[PAUSE_ITEM] = cursorPoint;
                        pauseCtx->cursorX[PAUSE_ITEM] = cursorX;
                        pauseCtx->cursorY[PAUSE_ITEM] = cursorY;
                        moveCursorResult = 1;
                        break;
                    }

                    cursorY = cursorY + 1;
                    cursorPoint = cursorPoint + 6;
                    if (cursorY < 4) {
                        continue;
                    }

                    cursorY = 0;
                    cursorPoint = cursorX + 1;
                    cursorX = cursorPoint;
                    if (cursorX < 6) {
                        continue;
                    }

                    KaleidoScope_MoveCursorToSpecialPos(play, PAUSE_CURSOR_PAGE_RIGHT);
                    break;
                }
            }
        } else {
            if (pauseCtx->stickAdjX < -30) {
                pauseCtx->nameDisplayTimer = 0;
                pauseCtx->cursorSpecialPos = 0;

                Audio_PlaySfxGeneral(NA_SE_SY_CURSOR, &gSfxDefaultPos, 4, &gSfxDefaultFreqAndVolScale,
                                     &gSfxDefaultFreqAndVolScale, &gSfxDefaultReverb);

                cursorPoint = cursorX = 5;
                cursorY = 0;
                while (true) {
                    if (1/*CHECK_ITEM_SLOT_FD(cursorPoint) != ITEM_NONE*/) {
                        pauseCtx->cursorPoint[PAUSE_ITEM] = cursorPoint;
                        pauseCtx->cursorX[PAUSE_ITEM] = cursorX;
                        pauseCtx->cursorY[PAUSE_ITEM] = cursorY;
                        moveCursorResult = 1;
                        break;
                    }

                    cursorY = cursorY + 1;
                    cursorPoint = cursorPoint + 6;
                    if (cursorY < 4) {
                        continue;
                    }

                    cursorY = 0;
                    cursorPoint = cursorX - 1;
                    cursorX = cursorPoint;
                    if (cursorX >= 0) {
                        continue;
                    }

                    KaleidoScope_MoveCursorToSpecialPos(play, PAUSE_CURSOR_PAGE_LEFT);
                    break;
                }
            }
        }

        if (pauseCtx->cursorSpecialPos == 0) {
            if (cursorItem != PAUSE_ITEM_NONE) {
                if (ABS(pauseCtx->stickAdjY) > 30) {
                    moveCursorResult = 0;

                    cursorPoint = pauseCtx->cursorPoint[PAUSE_ITEM];
                    cursorY = pauseCtx->cursorY[PAUSE_ITEM];
                    while (moveCursorResult == 0) {
                        if (pauseCtx->stickAdjY > 30) {
                            if (pauseCtx->cursorY[PAUSE_ITEM] != 0) {
                                pauseCtx->cursorY[PAUSE_ITEM]--;
                                pauseCtx->cursorPoint[PAUSE_ITEM] -= 6;

                                if (1/*CHECK_ITEM_SLOT_FD(pauseCtx->cursorPoint[PAUSE_ITEM]) != ITEM_NONE*/) {
                                    moveCursorResult = 1;
                                }
                            } else {
                                pauseCtx->cursorY[PAUSE_ITEM] = cursorY;
                                pauseCtx->cursorPoint[PAUSE_ITEM] = cursorPoint;

                                moveCursorResult = 2;
                            }
                        } else if (pauseCtx->stickAdjY < -30) {
                            if (pauseCtx->cursorY[PAUSE_ITEM] < 3) {
                                pauseCtx->cursorY[PAUSE_ITEM]++;
                                pauseCtx->cursorPoint[PAUSE_ITEM] += 6;

                                if (1/*CHECK_ITEM_SLOT_FD(pauseCtx->cursorPoint[PAUSE_ITEM]) != ITEM_NONE*/) {
                                    moveCursorResult = 1;
                                }
                            } else {
                                pauseCtx->cursorY[PAUSE_ITEM] = cursorY;
                                pauseCtx->cursorPoint[PAUSE_ITEM] = cursorPoint;

                                moveCursorResult = 2;
                            }
                        }
                    }

                    cursorPoint = PAUSE_ITEM;
                    osSyncPrintf("【Ｙ cursor=%d(%) (cur_ypt=%d)(ok_fg=%d)(ccc=%d)】  ",
                                 pauseCtx->cursorPoint[cursorPoint], pauseCtx->cursorY[PAUSE_ITEM], moveCursorResult,
                                 cursorItem);
                }
            }

            cursorSlot = pauseCtx->cursorPoint[PAUSE_ITEM];

            pauseCtx->cursorColorSet = 4;

            if (moveCursorResult == 1) {
                cursorItem = CHECK_ITEM_SLOT_FD(pauseCtx->cursorPoint[PAUSE_ITEM]);
            } else if (moveCursorResult != 2) {
                cursorItem = CHECK_ITEM_SLOT_FD(pauseCtx->cursorPoint[PAUSE_ITEM]);
            }

            pauseCtx->cursorItem[PAUSE_ITEM] = cursorItem;
            pauseCtx->cursorSlot[PAUSE_ITEM] = cursorSlot;

            if (!Parameter_CanUseItem(cursorItem)) {
                pauseCtx->nameColorSet = 1;
            }

            if (cursorItem != PAUSE_ITEM_NONE) {
                index = cursorSlot * 4; // required to match?
                KaleidoScope_SetCursorVtx(pauseCtx, index, pauseCtx->itemVtx);

                if ((pauseCtx->debugState == 0) && (pauseCtx->state == 6) && (pauseCtx->unk_1E4 == 0)) {
                    if (cursorItem != ITEM_NONE && CHECK_BTN_ANY(input->press.button, BTN_CLEFT | BTN_CDOWN | BTN_CRIGHT)) {
                        if ((Parameter_CanUseItem(cursorItem)) &&
                            (cursorItem != ITEM_SOLD_OUT)) {
                            if (CHECK_BTN_ALL(input->press.button, BTN_CLEFT)) {
                                pauseCtx->equipTargetCBtn = 0;
                            } else if (CHECK_BTN_ALL(input->press.button, BTN_CDOWN)) {
                                pauseCtx->equipTargetCBtn = 1;
                            } else if (CHECK_BTN_ALL(input->press.button, BTN_CRIGHT)) {
                                pauseCtx->equipTargetCBtn = 2;
                            }

                            pauseCtx->equipTargetItem = cursorItem;
                            pauseCtx->equipTargetSlot = cursorSlot;
                            pauseCtx->unk_1E4 = 3;
                            pauseCtx->equipAnimX = pauseCtx->itemVtx[index].v.ob[0] * 10;
                            pauseCtx->equipAnimY = pauseCtx->itemVtx[index].v.ob[1] * 10;
                            pauseCtx->equipAnimAlpha = 255;
                            sEquipAnimTimer = 0;
                            sEquipState = 3;
                            sEquipMoveTimer = 10;
                            if ((pauseCtx->equipTargetItem == ITEM_ARROW_FIRE) ||
                                (pauseCtx->equipTargetItem == ITEM_ARROW_ICE) ||
                                (pauseCtx->equipTargetItem == ITEM_ARROW_LIGHT)) {
                                index = 0;
                                if (pauseCtx->equipTargetItem == ITEM_ARROW_ICE) {
                                    index = 1;
                                }
                                if (pauseCtx->equipTargetItem == ITEM_ARROW_LIGHT) {
                                    index = 2;
                                }
                                Audio_PlaySfxGeneral(NA_SE_SY_SET_FIRE_ARROW + index, &gSfxDefaultPos, 4,
                                                     &gSfxDefaultFreqAndVolScale, &gSfxDefaultFreqAndVolScale,
                                                     &gSfxDefaultReverb);
                                pauseCtx->equipTargetItem = 0xBF + index;
                                sEquipState = 0;
                                pauseCtx->equipAnimAlpha = 0;
                                sEquipMoveTimer = 6;
                            } else {
                                Audio_PlaySfxGeneral(NA_SE_SY_DECIDE, &gSfxDefaultPos, 4, &gSfxDefaultFreqAndVolScale,
                                                     &gSfxDefaultFreqAndVolScale, &gSfxDefaultReverb);
                            }
                        } else {
                            Audio_PlaySfxGeneral(NA_SE_SY_ERROR, &gSfxDefaultPos, 4, &gSfxDefaultFreqAndVolScale,
                                                 &gSfxDefaultFreqAndVolScale, &gSfxDefaultReverb);
                        }
                    }
                }
            } else {
                pauseCtx->cursorVtx[0].v.ob[0] = pauseCtx->cursorVtx[2].v.ob[0] = pauseCtx->cursorVtx[1].v.ob[0] =
                    pauseCtx->cursorVtx[3].v.ob[0] = 0;

                pauseCtx->cursorVtx[0].v.ob[1] = pauseCtx->cursorVtx[1].v.ob[1] = pauseCtx->cursorVtx[2].v.ob[1] =
                    pauseCtx->cursorVtx[3].v.ob[1] = -200;
            }
        } else {
            pauseCtx->cursorItem[PAUSE_ITEM] = PAUSE_ITEM_NONE;
        }

        if (oldCursorPoint != pauseCtx->cursorPoint[PAUSE_ITEM]) {
            Audio_PlaySfxGeneral(NA_SE_SY_CURSOR, &gSfxDefaultPos, 4, &gSfxDefaultFreqAndVolScale,
                                 &gSfxDefaultFreqAndVolScale, &gSfxDefaultReverb);
        }
    } else if ((pauseCtx->unk_1E4 == 3) && (pauseCtx->pageIndex == PAUSE_ITEM)) {
        KaleidoScope_SetCursorVtx(pauseCtx, cursorSlot * 4, pauseCtx->itemVtx);
        pauseCtx->cursorColorSet = 4;
    }

    gDPSetCombineLERP(OVERLAY_DISP++, PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, TEXEL0, 0, PRIMITIVE, 0, PRIMITIVE,
                      ENVIRONMENT, TEXEL0, ENVIRONMENT, TEXEL0, 0, PRIMITIVE, 0);
    gDPSetPrimColor(POLY_OPA_DISP++, 0, 0, 255, 255, 255, pauseCtx->alpha);
    gDPSetEnvColor(POLY_OPA_DISP++, 0, 0, 0, 0);

    for (i = 0, j = 24 * 4; i < 3; i++, j += 4) {
        if (gSaveContext.equips.buttonItems[i + 1] != ITEM_NONE) {
            gSPVertex(POLY_OPA_DISP++, &pauseCtx->itemVtx[j], 4, 0);
            POLY_OPA_DISP = KaleidoScope_QuadTextureIA8(POLY_OPA_DISP, gEquippedItemOutlineTex, 32, 32, 0);
        }
    }

    gDPPipeSync(POLY_OPA_DISP++);
    gDPSetCombineMode(POLY_OPA_DISP++, G_CC_MODULATEIA_PRIM, G_CC_MODULATEIA_PRIM);

    for (i = j = 0; i < 24; i++, j += 4) {
        gDPSetPrimColor(POLY_OPA_DISP++, 0, 0, 255, 255, 255, pauseCtx->alpha);

        if (CHECK_ITEM_SLOT_FD(i) != ITEM_NONE) {
            if ((pauseCtx->unk_1E4 == 0) && (pauseCtx->pageIndex == PAUSE_ITEM) && (pauseCtx->cursorSpecialPos == 0)) {
                if (Parameter_CanUseItem(cursorItem)) {
                    if ((sEquipState == 2) && (i == 3)) {
                        gDPSetPrimColor(POLY_OPA_DISP++, 0, 0, magicArrowEffectsR[pauseCtx->equipTargetItem - 0xBF],
                                        magicArrowEffectsG[pauseCtx->equipTargetItem - 0xBF],
                                        magicArrowEffectsB[pauseCtx->equipTargetItem - 0xBF], pauseCtx->alpha);

                        pauseCtx->itemVtx[j + 0].v.ob[0] = pauseCtx->itemVtx[j + 2].v.ob[0] =
                            pauseCtx->itemVtx[j + 0].v.ob[0] - 2;

                        pauseCtx->itemVtx[j + 1].v.ob[0] = pauseCtx->itemVtx[j + 3].v.ob[0] =
                            pauseCtx->itemVtx[j + 0].v.ob[0] + 32;

                        pauseCtx->itemVtx[j + 0].v.ob[1] = pauseCtx->itemVtx[j + 1].v.ob[1] =
                            pauseCtx->itemVtx[j + 0].v.ob[1] + 2;

                        pauseCtx->itemVtx[j + 2].v.ob[1] = pauseCtx->itemVtx[j + 3].v.ob[1] =
                            pauseCtx->itemVtx[j + 0].v.ob[1] - 32;
                    } else if (i == cursorSlot) {
                        pauseCtx->itemVtx[j + 0].v.ob[0] = pauseCtx->itemVtx[j + 2].v.ob[0] =
                            pauseCtx->itemVtx[j + 0].v.ob[0] - 2;

                        pauseCtx->itemVtx[j + 1].v.ob[0] = pauseCtx->itemVtx[j + 3].v.ob[0] =
                            pauseCtx->itemVtx[j + 0].v.ob[0] + 32;

                        pauseCtx->itemVtx[j + 0].v.ob[1] = pauseCtx->itemVtx[j + 1].v.ob[1] =
                            pauseCtx->itemVtx[j + 0].v.ob[1] + 2;

                        pauseCtx->itemVtx[j + 2].v.ob[1] = pauseCtx->itemVtx[j + 3].v.ob[1] =
                            pauseCtx->itemVtx[j + 0].v.ob[1] - 32;
                    }
                }
            }

            gSPVertex(POLY_OPA_DISP++, &pauseCtx->itemVtx[j + 0], 4, 0);
            KaleidoScope_DrawQuadTextureRGBA32(play->state.gfxCtx, gItemIcons[CHECK_ITEM_SLOT_FD(i)],
                                               ITEM_ICON_WIDTH, ITEM_ICON_HEIGHT, 0);
        }
    }

    if (pauseCtx->cursorSpecialPos == 0) {
        KaleidoScope_DrawCursor(play, PAUSE_ITEM);
    }

    gDPPipeSync(POLY_OPA_DISP++);
    gDPSetCombineLERP(POLY_OPA_DISP++, PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, TEXEL0, 0, PRIMITIVE, 0, PRIMITIVE,
                      ENVIRONMENT, TEXEL0, ENVIRONMENT, TEXEL0, 0, PRIMITIVE, 0);

    for (i = 0; i < 24; i++) { // ammo counter items
        u8 item = CHECK_ITEM_SLOT_FD(i);
        if (item == ITEM_DEKU_STICK || item == ITEM_BOW || item == ITEM_SLINGSHOT || item == ITEM_BOMB || item == ITEM_BOMBCHU || item == ITEM_MAGIC_BEAN || item == ITEM_DEKU_NUT) {
            KaleidoScope_DrawAmmoCount(play, pauseCtx, play->state.gfxCtx, item, i);
        } else if (item == ITEM_BOW_FIRE || item == ITEM_BOW_ICE || item == ITEM_BOW_LIGHT) {
            KaleidoScope_DrawAmmoCount(play, pauseCtx, play->state.gfxCtx, ITEM_BOW, i);
        }
    }

    CLOSE_DISPS(play->state.gfxCtx, "../z_kaleido_item.c", 516);
}

static s16 sCButtonPosX[] = { 660, 900, 1140 };
static s16 sCButtonPosY[] = { 1100, 920, 1100 };

void KaleidoScope_UpdateItemEquip(PlayState* play) {
    static s16 D_8082A488 = 0;
    PauseContext* pauseCtx = &play->pauseCtx;
    Vtx* bowItemVtx;
    u16 offsetX;
    u16 offsetY;

    if (sEquipState == 0) {
        pauseCtx->equipAnimAlpha += 14;
        if (pauseCtx->equipAnimAlpha > 255) {
            pauseCtx->equipAnimAlpha = 254;
            sEquipState++;
        }
        sEquipAnimTimer = 5;
        return;
    }

    if (sEquipState == 2) {
        D_8082A488--;

        if (D_8082A488 == 0) {
            pauseCtx->equipTargetItem -= 0xBF - ITEM_BOW_FIRE;
            pauseCtx->equipTargetSlot = SLOT_BOW;
            sEquipMoveTimer = 6;
            WREG(90) = 320;
            WREG(87) = WREG(91);
            sEquipState++;
            Audio_PlaySfxGeneral(NA_SE_SY_SYNTH_MAGIC_ARROW, &gSfxDefaultPos, 4, &gSfxDefaultFreqAndVolScale,
                                 &gSfxDefaultFreqAndVolScale, &gSfxDefaultReverb);
        }
        return;
    }

    if (sEquipState == 1) {
        bowItemVtx = &pauseCtx->itemVtx[12];
        offsetX = ABS(pauseCtx->equipAnimX - bowItemVtx->v.ob[0] * 10) / sEquipMoveTimer;
        offsetY = ABS(pauseCtx->equipAnimY - bowItemVtx->v.ob[1] * 10) / sEquipMoveTimer;
    } else {
        offsetX = ABS(pauseCtx->equipAnimX - sCButtonPosX[pauseCtx->equipTargetCBtn]) / sEquipMoveTimer;
        offsetY = ABS(pauseCtx->equipAnimY - sCButtonPosY[pauseCtx->equipTargetCBtn]) / sEquipMoveTimer;
    }

    if ((pauseCtx->equipTargetItem >= 0xBF) && (pauseCtx->equipAnimAlpha < 254)) {
        pauseCtx->equipAnimAlpha += 14;
        if (pauseCtx->equipAnimAlpha > 255) {
            pauseCtx->equipAnimAlpha = 254;
        }
        sEquipAnimTimer = 5;
        return;
    }

    if (sEquipAnimTimer == 0) {
        WREG(90) -= WREG(87) / sEquipMoveTimer;
        WREG(87) -= WREG(87) / sEquipMoveTimer;

        if (sEquipState == 1) {
            if (pauseCtx->equipAnimX >= (pauseCtx->itemVtx[12].v.ob[0] * 10)) {
                pauseCtx->equipAnimX -= offsetX;
            } else {
                pauseCtx->equipAnimX += offsetX;
            }

            if (pauseCtx->equipAnimY >= (pauseCtx->itemVtx[12].v.ob[1] * 10)) {
                pauseCtx->equipAnimY -= offsetY;
            } else {
                pauseCtx->equipAnimY += offsetY;
            }
        } else {
            if (pauseCtx->equipAnimX >= sCButtonPosX[pauseCtx->equipTargetCBtn]) {
                pauseCtx->equipAnimX -= offsetX;
            } else {
                pauseCtx->equipAnimX += offsetX;
            }

            if (pauseCtx->equipAnimY >= sCButtonPosY[pauseCtx->equipTargetCBtn]) {
                pauseCtx->equipAnimY -= offsetY;
            } else {
                pauseCtx->equipAnimY += offsetY;
            }
        }

        sEquipMoveTimer--;

        if (sEquipMoveTimer == 0) {
            if (sEquipState == 1) {
                sEquipState++;
                D_8082A488 = 4;
                return;
            }

            osSyncPrintf("\n＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝\n");

            if (pauseCtx->equipTargetCBtn == 0) {

                if (pauseCtx->equipTargetSlot == gSaveContext.equips.cButtonSlots[1]) {
                    if (gSaveContext.equips.buttonItems[1] != ITEM_NONE) {
                        if ((pauseCtx->equipTargetItem >= 0xBF) && (pauseCtx->equipTargetItem <= 0xC1) &&
                            ((gSaveContext.equips.buttonItems[1] == ITEM_BOW) ||
                             ((gSaveContext.equips.buttonItems[1] >= ITEM_BOW_FIRE) &&
                              (gSaveContext.equips.buttonItems[1] <= ITEM_BOW_LIGHT)))) {
                            pauseCtx->equipTargetItem -= 0xBF - ITEM_BOW_FIRE;
                            pauseCtx->equipTargetSlot = SLOT_BOW;
                        } else {
                            gSaveContext.equips.buttonItems[2] = gSaveContext.equips.buttonItems[1];
                            gSaveContext.equips.cButtonSlots[1] = gSaveContext.equips.cButtonSlots[0];
                            Interface_LoadItemIcon2(play, 2);
                        }
                    } else {
                        gSaveContext.equips.buttonItems[2] = ITEM_NONE;
                        gSaveContext.equips.cButtonSlots[1] = SLOT_NONE;
                    }
                } else if (pauseCtx->equipTargetSlot == gSaveContext.equips.cButtonSlots[2]) {
                    if (gSaveContext.equips.buttonItems[1] != ITEM_NONE) {
                        if ((pauseCtx->equipTargetItem >= 0xBF) && (pauseCtx->equipTargetItem <= 0xC1) &&
                            ((gSaveContext.equips.buttonItems[1] == ITEM_BOW) ||
                             ((gSaveContext.equips.buttonItems[1] >= ITEM_BOW_FIRE) &&
                              (gSaveContext.equips.buttonItems[1] <= ITEM_BOW_LIGHT)))) {
                            pauseCtx->equipTargetItem -= 0xBF - ITEM_BOW_FIRE;
                            pauseCtx->equipTargetSlot = SLOT_BOW;
                        } else {
                            gSaveContext.equips.buttonItems[3] = gSaveContext.equips.buttonItems[1];
                            gSaveContext.equips.cButtonSlots[2] = gSaveContext.equips.cButtonSlots[0];
                            Interface_LoadItemIcon2(play, 3);
                        }
                    } else {
                        gSaveContext.equips.buttonItems[3] = ITEM_NONE;
                        gSaveContext.equips.cButtonSlots[2] = SLOT_NONE;
                    }
                }

                if ((pauseCtx->equipTargetItem >= 0xBF) && (pauseCtx->equipTargetItem <= 0xC1)) {
                    if ((gSaveContext.equips.buttonItems[1] == ITEM_BOW) ||
                        ((gSaveContext.equips.buttonItems[1] >= ITEM_BOW_FIRE) &&
                         (gSaveContext.equips.buttonItems[1] <= ITEM_BOW_LIGHT))) {
                        pauseCtx->equipTargetItem -= 0xBF - ITEM_BOW_FIRE;
                        pauseCtx->equipTargetSlot = SLOT_BOW;
                    }
                } else if (pauseCtx->equipTargetItem == ITEM_BOW) {
                    if ((gSaveContext.equips.buttonItems[2] >= ITEM_BOW_FIRE) &&
                        (gSaveContext.equips.buttonItems[2] <= ITEM_BOW_LIGHT)) {
                        gSaveContext.equips.buttonItems[2] = gSaveContext.equips.buttonItems[1];
                        gSaveContext.equips.cButtonSlots[1] = gSaveContext.equips.cButtonSlots[0];
                        Interface_LoadItemIcon2(play, 2);
                    } else if ((gSaveContext.equips.buttonItems[3] >= ITEM_BOW_FIRE) &&
                               (gSaveContext.equips.buttonItems[3] <= ITEM_BOW_LIGHT)) {
                        gSaveContext.equips.buttonItems[3] = gSaveContext.equips.buttonItems[1];
                        gSaveContext.equips.cButtonSlots[2] = gSaveContext.equips.cButtonSlots[0];
                        Interface_LoadItemIcon2(play, 3);
                    }
                }

                gSaveContext.equips.buttonItems[1] = pauseCtx->equipTargetItem;
                gSaveContext.equips.cButtonSlots[0] = pauseCtx->equipTargetSlot;
                Interface_LoadItemIcon1(play, 1);

                osSyncPrintf("Ｃ左sl_item_no=%d (1)=%d (2)=%d (3)=%d\n", pauseCtx->equipTargetItem,
                             gSaveContext.equips.buttonItems[1], gSaveContext.equips.buttonItems[2],
                             gSaveContext.equips.buttonItems[3]);
                osSyncPrintf("Ｃ左sl_number=%d (1)=%d (2)=%d (3)=%d\n", pauseCtx->equipTargetSlot,
                             gSaveContext.equips.cButtonSlots[0], gSaveContext.equips.cButtonSlots[1],
                             gSaveContext.equips.cButtonSlots[2]);
            } else if (pauseCtx->equipTargetCBtn == 1) {
                osSyncPrintf("Ｃ下sl_item_no=%d (1)=%d (2)=%d (3)=%d\n", pauseCtx->equipTargetItem,
                             gSaveContext.equips.buttonItems[1], gSaveContext.equips.buttonItems[2],
                             gSaveContext.equips.buttonItems[3]);
                osSyncPrintf("Ｃ下sl_number=%d (1)=%d (2)=%d (3)=%d\n", pauseCtx->equipTargetSlot,
                             gSaveContext.equips.cButtonSlots[0], gSaveContext.equips.cButtonSlots[1],
                             gSaveContext.equips.cButtonSlots[2]);

                if (pauseCtx->equipTargetSlot == gSaveContext.equips.cButtonSlots[0]) {
                    if (gSaveContext.equips.buttonItems[2] != ITEM_NONE) {
                        if ((pauseCtx->equipTargetItem >= 0xBF) && (pauseCtx->equipTargetItem <= 0xC1) &&
                            ((gSaveContext.equips.buttonItems[2] == ITEM_BOW) ||
                             ((gSaveContext.equips.buttonItems[2] >= ITEM_BOW_FIRE) &&
                              (gSaveContext.equips.buttonItems[2] <= ITEM_BOW_LIGHT)))) {
                            pauseCtx->equipTargetItem -= 0xBF - ITEM_BOW_FIRE;
                            pauseCtx->equipTargetSlot = SLOT_BOW;
                        } else {
                            gSaveContext.equips.buttonItems[1] = gSaveContext.equips.buttonItems[2];
                            gSaveContext.equips.cButtonSlots[0] = gSaveContext.equips.cButtonSlots[1];
                            Interface_LoadItemIcon2(play, 1);
                        }
                    } else {
                        gSaveContext.equips.buttonItems[1] = ITEM_NONE;
                        gSaveContext.equips.cButtonSlots[0] = SLOT_NONE;
                    }
                } else if (pauseCtx->equipTargetSlot == gSaveContext.equips.cButtonSlots[2]) {
                    if (gSaveContext.equips.buttonItems[2] != ITEM_NONE) {
                        if ((pauseCtx->equipTargetItem >= 0xBF) && (pauseCtx->equipTargetItem <= 0xC1) &&
                            ((gSaveContext.equips.buttonItems[2] == ITEM_BOW) ||
                             ((gSaveContext.equips.buttonItems[2] >= ITEM_BOW_FIRE) &&
                              (gSaveContext.equips.buttonItems[2] <= ITEM_BOW_LIGHT)))) {
                            pauseCtx->equipTargetItem -= 0xBF - ITEM_BOW_FIRE;
                            pauseCtx->equipTargetSlot = SLOT_BOW;
                        } else {
                            gSaveContext.equips.buttonItems[3] = gSaveContext.equips.buttonItems[2];
                            gSaveContext.equips.cButtonSlots[2] = gSaveContext.equips.cButtonSlots[1];
                            Interface_LoadItemIcon2(play, 3);
                        }
                    } else {
                        gSaveContext.equips.buttonItems[3] = ITEM_NONE;
                        gSaveContext.equips.cButtonSlots[2] = SLOT_NONE;
                    }
                }

                if ((pauseCtx->equipTargetItem >= 0xBF) && (pauseCtx->equipTargetItem <= 0xC1)) {
                    if ((gSaveContext.equips.buttonItems[2] == ITEM_BOW) ||
                        ((gSaveContext.equips.buttonItems[2] >= ITEM_BOW_FIRE) &&
                         (gSaveContext.equips.buttonItems[2] <= ITEM_BOW_LIGHT))) {
                        pauseCtx->equipTargetItem -= 0xBF - ITEM_BOW_FIRE;
                        pauseCtx->equipTargetSlot = SLOT_BOW;
                    }
                } else if (pauseCtx->equipTargetItem == ITEM_BOW) {
                    if ((gSaveContext.equips.buttonItems[1] >= ITEM_BOW_FIRE) &&
                        (gSaveContext.equips.buttonItems[1] <= ITEM_BOW_LIGHT)) {
                        gSaveContext.equips.buttonItems[1] = gSaveContext.equips.buttonItems[2];
                        Interface_LoadItemIcon2(play, 1);
                    } else if ((gSaveContext.equips.buttonItems[3] >= ITEM_BOW_FIRE) &&
                               (gSaveContext.equips.buttonItems[3] <= ITEM_BOW_LIGHT)) {
                        gSaveContext.equips.buttonItems[3] = gSaveContext.equips.buttonItems[2];
                        Interface_LoadItemIcon2(play, 3);
                    }
                }

                gSaveContext.equips.buttonItems[2] = pauseCtx->equipTargetItem;
                gSaveContext.equips.cButtonSlots[1] = pauseCtx->equipTargetSlot;
                Interface_LoadItemIcon1(play, 2);

                osSyncPrintf("Ｃ下sl_item_no=%d (1)=%d (2)=%d (3)=%d\n", pauseCtx->equipTargetItem,
                             gSaveContext.equips.buttonItems[1], gSaveContext.equips.buttonItems[2],
                             gSaveContext.equips.buttonItems[3]);
                osSyncPrintf("Ｃ下sl_number=%d (1)=%d (2)=%d (3)=%d\n", pauseCtx->equipTargetSlot,
                             gSaveContext.equips.cButtonSlots[0], gSaveContext.equips.cButtonSlots[1],
                             gSaveContext.equips.cButtonSlots[2]);
            } else {
                osSyncPrintf("Ｃ右sl_item_no=%d (1)=%d (2)=%d (3)=%d\n", pauseCtx->equipTargetItem,
                             gSaveContext.equips.buttonItems[1], gSaveContext.equips.buttonItems[2],
                             gSaveContext.equips.buttonItems[3]);
                osSyncPrintf("Ｃ右sl_number=%d (1)=%d (2)=%d (3)=%d\n", pauseCtx->equipTargetSlot,
                             gSaveContext.equips.cButtonSlots[0], gSaveContext.equips.cButtonSlots[1],
                             gSaveContext.equips.cButtonSlots[2]);

                if (pauseCtx->equipTargetSlot == gSaveContext.equips.cButtonSlots[0]) {
                    if (gSaveContext.equips.buttonItems[3] != ITEM_NONE) {
                        if ((pauseCtx->equipTargetItem >= 0xBF) && (pauseCtx->equipTargetItem <= 0xC1) &&
                            ((gSaveContext.equips.buttonItems[3] == ITEM_BOW) ||
                             ((gSaveContext.equips.buttonItems[3] >= ITEM_BOW_FIRE) &&
                              (gSaveContext.equips.buttonItems[3] <= ITEM_BOW_LIGHT)))) {
                            pauseCtx->equipTargetItem -= 0xBF - ITEM_BOW_FIRE;
                            pauseCtx->equipTargetSlot = SLOT_BOW;
                        } else {
                            gSaveContext.equips.buttonItems[1] = gSaveContext.equips.buttonItems[3];
                            gSaveContext.equips.cButtonSlots[0] = gSaveContext.equips.cButtonSlots[2];
                            Interface_LoadItemIcon2(play, 1);
                        }
                    } else {
                        gSaveContext.equips.buttonItems[1] = ITEM_NONE;
                        gSaveContext.equips.cButtonSlots[0] = SLOT_NONE;
                    }
                } else if (pauseCtx->equipTargetSlot == gSaveContext.equips.cButtonSlots[1]) {
                    if (gSaveContext.equips.buttonItems[3] != ITEM_NONE) {
                        if ((pauseCtx->equipTargetItem >= 0xBF) && (pauseCtx->equipTargetItem <= 0xC1) &&
                            ((gSaveContext.equips.buttonItems[3] == ITEM_BOW) ||
                             ((gSaveContext.equips.buttonItems[3] >= ITEM_BOW_FIRE) &&
                              (gSaveContext.equips.buttonItems[3] <= ITEM_BOW_LIGHT)))) {
                            pauseCtx->equipTargetItem -= 0xBF - ITEM_BOW_FIRE;
                            pauseCtx->equipTargetSlot = SLOT_BOW;
                        } else {
                            gSaveContext.equips.buttonItems[2] = gSaveContext.equips.buttonItems[3];
                            gSaveContext.equips.cButtonSlots[1] = gSaveContext.equips.cButtonSlots[2];
                            Interface_LoadItemIcon2(play, 2);
                        }
                    } else {
                        gSaveContext.equips.buttonItems[2] = ITEM_NONE;
                        gSaveContext.equips.cButtonSlots[1] = SLOT_NONE;
                    }
                }

                if ((pauseCtx->equipTargetItem >= 0xBF) && (pauseCtx->equipTargetItem <= 0xC1)) {
                    if ((gSaveContext.equips.buttonItems[3] == ITEM_BOW) ||
                        ((gSaveContext.equips.buttonItems[3] >= ITEM_BOW_FIRE) &&
                         (gSaveContext.equips.buttonItems[3] <= ITEM_BOW_LIGHT))) {
                        pauseCtx->equipTargetItem -= 0xBF - ITEM_BOW_FIRE;
                        pauseCtx->equipTargetSlot = SLOT_BOW;
                    }
                } else if (pauseCtx->equipTargetItem == ITEM_BOW) {
                    if ((gSaveContext.equips.buttonItems[1] >= ITEM_BOW_FIRE) &&
                        (gSaveContext.equips.buttonItems[1] <= ITEM_BOW_LIGHT)) {
                        gSaveContext.equips.buttonItems[1] = gSaveContext.equips.buttonItems[3];
                        Interface_LoadItemIcon2(play, 1);
                    } else if ((gSaveContext.equips.buttonItems[2] >= ITEM_BOW_FIRE) &&
                               (gSaveContext.equips.buttonItems[2] <= ITEM_BOW_LIGHT)) {
                        gSaveContext.equips.buttonItems[2] = gSaveContext.equips.buttonItems[3];
                        Interface_LoadItemIcon2(play, 2);
                    }
                }

                gSaveContext.equips.buttonItems[3] = pauseCtx->equipTargetItem;
                gSaveContext.equips.cButtonSlots[2] = pauseCtx->equipTargetSlot;
                Interface_LoadItemIcon1(play, 3);

                osSyncPrintf("Ｃ右sl_item_no=%d (1)=%d (2)=%d (3)=%d\n", pauseCtx->equipTargetItem,
                             gSaveContext.equips.buttonItems[1], gSaveContext.equips.buttonItems[2],
                             gSaveContext.equips.buttonItems[3]);
                osSyncPrintf("Ｃ右sl_number=%d (1)=%d (2)=%d (3)=%d\n", pauseCtx->equipTargetSlot,
                             gSaveContext.equips.cButtonSlots[0], gSaveContext.equips.cButtonSlots[1],
                             gSaveContext.equips.cButtonSlots[2]);
            }

            pauseCtx->unk_1E4 = 0;
            sEquipMoveTimer = 10;
            WREG(90) = 320;
            WREG(87) = WREG(91);
        }
    } else {
        sEquipAnimTimer--;
        if (sEquipAnimTimer == 0) {
            pauseCtx->equipAnimAlpha = 255;
        }
    }
}
