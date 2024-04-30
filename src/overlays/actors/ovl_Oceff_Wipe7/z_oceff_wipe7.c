/*
 * File: z_oceff_wipe7.c
 * Overlay: ovl_Oceff_Wipe7
 * Description: Song of Healing Ocarina Effect
 */

#include "z_oceff_wipe7.h"

#define FLAGS (ACTOR_FLAG_4 | ACTOR_FLAG_25)

#define THIS ((OceffWipe7*)thisx)

void OceffWipe7_Init(Actor* thisx, PlayState* play);
void OceffWipe7_Destroy(Actor* thisx, PlayState* play);
void OceffWipe7_Update(Actor* thisx, PlayState* play);
void OceffWipe7_Draw(Actor* thisx, PlayState* play);

ActorInit Oceff_Wipe7_InitVars = {
    /**/ ACTOR_OCEFF_WIPE7,
    /**/ ACTORCAT_ITEMACTION,
    /**/ FLAGS,
    /**/ OBJECT_GAMEPLAY_KEEP,
    /**/ sizeof(OceffWipe7),
    /**/ OceffWipe7_Init,
    /**/ OceffWipe7_Destroy,
    /**/ OceffWipe7_Update,
    /**/ OceffWipe7_Draw,
};

#include "assets/overlays/ovl_Oceff_Wipe7/ovl_Oceff_Wipe7.c"

static s32 sBssPad;

void OceffWipe7_Init(Actor* thisx, PlayState* play) {
    OceffWipe7* this = THIS;

    Actor_SetScale(&this->actor, 1.0f);
    this->counter = 0;
    this->actor.world.pos = GET_ACTIVE_CAM(play)->eye;
}

void OceffWipe7_Destroy(Actor* thisx, PlayState* play) {
    OceffWipe7* this = THIS;
    Player* player = GET_PLAYER(play);

    Magic_Reset(play);
     if (gSaveContext.nayrusLoveTimer != 0) {
        player->stateFlags3 |= PLAYER_STATE3_RESTORE_NAYRUS_LOVE;
    }
}

void OceffWipe7_Update(Actor* thisx, PlayState* play) {
    OceffWipe7* this = THIS;

    this->actor.world.pos = GET_ACTIVE_CAM(play)->eye;
    if (this->counter < 100) {
        this->counter++;
    } else {
        Actor_Kill(&this->actor);
    }
}

AnimatedMatTexScrollParams sSongofHealingEffectTexAnimTexScrollParams[] = {
    { -1, 2, 0x20, 0x20 },
    { -6, 8, 0x20, 0x40 },
};

#define Y -130.0f

void OceffWipe7_Draw(Actor* thisx, PlayState* play) {
    OceffWipe7* this = THIS;
    f32 z;
    u8 alpha;
    s32 i;
    s32 counter;
    Vec3f activeCamEye = GET_ACTIVE_CAM(play)->eye;
    s32 pad;
    Vec3f quakeOffset;
    s32 pad2;

    Camera_GetQuakeOffset(&quakeOffset, GET_ACTIVE_CAM(play));

    if (this->counter < 32) {
        z = Math_SinS(this->counter * 0x200) * 1220.0f;
    } else {
        z = 1220.0f;
    }

    if (this->counter >= 80) {
        alpha = 12 * (100 - this->counter);
    } else {
        alpha = 255;
    }

    for (i = 1; i < ARRAY_COUNT(sSongofHealingEffectFrustrumVtx); i += 2) {
        sSongofHealingEffectFrustrumVtx[i].v.cn[3] = alpha;
    }

    OPEN_DISPS(play->state.gfxCtx, "../z_oceff_wipe7.c", __LINE__);

    Gfx_SetupDL_25Xlu(play->state.gfxCtx);
    Matrix_Translate(activeCamEye.x + quakeOffset.x, activeCamEye.y + quakeOffset.y, activeCamEye.z + quakeOffset.z,
                     MTXMODE_NEW);
    Matrix_Scale(0.1f, 0.1f, 0.1f, MTXMODE_APPLY);
    Matrix_ReplaceRotation(&play->billboardMtxF);
    Matrix_RotateXS(0x708, MTXMODE_APPLY);
    Matrix_Translate(0.0f, Y, -z, MTXMODE_APPLY);

    gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(play->state.gfxCtx, "../z_oceff_wipe7.c", __LINE__),
              G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    AnimatedMat_DrawTwoTexScroll(play, 0x08, &sSongofHealingEffectTexAnimTexScrollParams);
    gSPDisplayList(POLY_XLU_DISP++, sSongOfHealingEffectFrustumDL);

    CLOSE_DISPS(play->state.gfxCtx, "../z_oceff_wipe7.c", __LINE__);
}
