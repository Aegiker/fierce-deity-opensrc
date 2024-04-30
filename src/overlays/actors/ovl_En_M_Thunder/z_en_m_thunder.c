#include "z_en_m_thunder.h"
#include "assets/objects/gameplay_keep/gameplay_keep.h"

#define FLAGS (ACTOR_FLAG_4)

void EnMThunder_Init(Actor* thisx, PlayState* play2);
void EnMThunder_Destroy(Actor* thisx, PlayState* play);
void EnMThunder_Update(Actor* thisx, PlayState* play);
void EnMThunder_Draw(Actor* thisx, PlayState* play2);

void func_80A9F314(EnMThunder* this, PlayState* play, f32 arg1);
void EnMThunder_Charge(EnMThunder* this, PlayState* play);
void func_80A9F9B4(EnMThunder* this, PlayState* play);

void EnMThunder_SwordBeam_Attack(EnMThunder* this, PlayState* play);

ActorInit En_M_Thunder_InitVars = {
    ACTOR_EN_M_THUNDER,
    ACTORCAT_ITEMACTION,
    FLAGS,
    OBJECT_GAMEPLAY_KEEP,
    sizeof(EnMThunder),
    (ActorFunc)EnMThunder_Init,
    (ActorFunc)EnMThunder_Destroy,
    (ActorFunc)EnMThunder_Update,
    (ActorFunc)EnMThunder_Draw,
};

static ColliderCylinderInit D_80AA0420 = {
    {
        COLTYPE_NONE,
        AT_ON | AT_TYPE_PLAYER,
        AC_NONE,
        OC1_NONE,
        OC2_TYPE_1,
        COLSHAPE_CYLINDER,
    },
    {
        ELEMTYPE_UNK2,
        { 0x00000001, 0x00, 0x00 },
        { 0xFFCFFFFF, 0x00, 0x00 },
        TOUCH_ON | TOUCH_SFX_NONE,
        BUMP_ON,
        OCELEM_ON,
    },
    { 200, 200, 0, { 0, 0, 0 } },
};

static u32 D_80AA044C[] = { DMG_SPIN_MASTER, DMG_SPIN_KOKIRI, DMG_SPIN_GIANT };
static u32 D_80AA0458[] = { DMG_JUMP_MASTER, DMG_JUMP_KOKIRI, DMG_JUMP_GIANT };
static EnMThunder* topDog = NULL;

static u16 sSfxIds[] = {
    NA_SE_IT_ROLLING_CUT_LV2,
    NA_SE_IT_ROLLING_CUT_LV1,
    NA_SE_IT_ROLLING_CUT_LV2,
    NA_SE_IT_ROLLING_CUT_LV1,
};

// Setup action
void func_80A9EFE0(EnMThunder* this, EnMThunderActionFunc actionFunc) {
    this->actionFunc = actionFunc;
}

void EnMThunder_Init(Actor* thisx, PlayState* play2) {
    PlayState* play = play2;
    EnMThunder* this = (EnMThunder*)thisx;
    Player* player = GET_PLAYER(play);

    Collider_InitCylinder(play, &this->collider);
    Collider_SetCylinder(play, &this->collider, &this->actor, &D_80AA0420);
    this->type = (this->actor.params & 0xFF) - 1;
    Lights_PointNoGlowSetInfo(&this->lightInfo, this->actor.world.pos.x, this->actor.world.pos.y,
                              this->actor.world.pos.z, 255, 255, 255, 0);
    this->lightNode = LightContext_InsertLight(play, &play->lightCtx, &this->lightInfo);
    this->collider.dim.radius = 0;
    this->collider.dim.height = 40;
    this->collider.dim.yShift = -20;
    this->timer = 8;
    this->scroll = 0.0f;
    this->actor.world.pos = player->bodyPartsPos[PLAYER_BODYPART_WAIST];
    this->lightColorFrac = 0.0f;
    this->adjustLightsArg1 = 0.0f;
    this->actor.shape.rot.y = player->actor.shape.rot.y + 0x8000;
    this->actor.room = -1;
    Actor_SetScale(&this->actor, 0.1f);
    this->isCharging = 0;

    if (player->stateFlags2 & PLAYER_STATE2_17) {
        if (!LINK_IS_DEITY) {
            if (!gSaveContext.isMagicAcquired || (gSaveContext.magicState != MAGIC_STATE_IDLE) ||
                (((this->actor.params & 0xFF00) >> 8) &&
                !(Magic_RequestChange(play, (this->actor.params & 0xFF00) >> 8, MAGIC_CONSUME_NOW)))) {
                Audio_PlaySfxGeneral(NA_SE_IT_ROLLING_CUT, &player->actor.projectedPos, 4, &gSfxDefaultFreqAndVolScale,
                                    &gSfxDefaultFreqAndVolScale, &gSfxDefaultReverb);
                Audio_PlaySfxGeneral(NA_SE_IT_SWORD_SWING_HARD, &player->actor.projectedPos, 4, &gSfxDefaultFreqAndVolScale,
                                    &gSfxDefaultFreqAndVolScale, &gSfxDefaultReverb);
                Actor_Kill(&this->actor);
                return;
            }
        }

        player->stateFlags2 &= ~PLAYER_STATE2_17;
        this->isCharging = 1;

        if (!(player->meleeWeaponAnimation < PLAYER_MWA_SPIN_ATTACK_1H)) { // not a sord beem
            this->collider.info.toucher.dmgFlags = D_80AA044C[this->type];
            this->subtype = 1;
            this->scaleTarget = ((this->type == 1) ? 2 : 4);
            func_80A9EFE0(this, func_80A9F9B4);
            this->timer = 8;
        } else { // sord beem
            this->subtype += ENMTHUNDER_SUBTYPE_SWORDBEAM_GREAT;
            func_80A9EFE0(this, EnMThunder_SwordBeam_Attack);
            this->timer = 1;
            this->scaleTarget = 12;
            this->collider.info.toucher.dmgFlags = DMG_SWORDBEAM; 
            this->collider.info.toucher.damage = 3;
            this->isCharging = 1;
            //*((u32*)0x80740004) = 0x77777777;
        }

        Audio_PlaySfxGeneral(NA_SE_IT_ROLLING_CUT_LV1, &player->actor.projectedPos, 4, &gSfxDefaultFreqAndVolScale,
                             &gSfxDefaultFreqAndVolScale, &gSfxDefaultReverb);
        this->lightColorFrac = 1.0f;
    } else {
        func_80A9EFE0(this, EnMThunder_Charge);
    }
    this->actor.child = NULL;
    topDog = this;
}

void EnMThunder_Destroy(Actor* thisx, PlayState* play) {
    EnMThunder* this = (EnMThunder*)thisx;

    if (this->isCharging != 0) {
        //*((u32*)0x80740008) = 0x88888888;
        Magic_Reset(play);
    }

    Collider_DestroyCylinder(play, &this->collider);
    func_80A9F314(this, play, 0.0f);
    LightContext_RemoveLight(play, &play->lightCtx, this->lightNode);
}

// topDog ensures that the newest EnMThunder is the only one controlling the lights
void func_80A9F314(EnMThunder* this, PlayState* play, f32 arg1) {
    if (this == topDog || topDog == NULL || (topDog != NULL && (topDog->actor.id != ACTOR_EN_M_THUNDER || topDog->actor.update == NULL))) { // emergency cases: topDog is null or topDog is somehow not an EnMThunder, or topDog was destroyed
        Environment_AdjustLights(play, arg1, 850.0f, 0.2f, 0.0f);
    }
}

void func_80A9F350(EnMThunder* this, PlayState* play) {
    Player* player = GET_PLAYER(play);

    if (player->stateFlags2 & PLAYER_STATE2_17) {
        if (player->meleeWeaponAnimation >= PLAYER_MWA_SPIN_ATTACK_1H) {
            Audio_PlaySfxGeneral(NA_SE_IT_ROLLING_CUT, &player->actor.projectedPos, 4, &gSfxDefaultFreqAndVolScale,
                                 &gSfxDefaultFreqAndVolScale, &gSfxDefaultReverb);
            Audio_PlaySfxGeneral(NA_SE_IT_SWORD_SWING_HARD, &player->actor.projectedPos, 4, &gSfxDefaultFreqAndVolScale,
                                 &gSfxDefaultFreqAndVolScale, &gSfxDefaultReverb);
        }

        Actor_Kill(&this->actor);
        return;
    }

    if (!(player->stateFlags1 & PLAYER_STATE1_12)) {
        Actor_Kill(&this->actor);
    }
}

void EnMThunder_Charge(EnMThunder* this, PlayState* play) {
    Player* player = GET_PLAYER(play);
    Actor* child = this->actor.child;

    this->unk_1B8 = player->unk_858;
    this->actor.world.pos = player->bodyPartsPos[PLAYER_BODYPART_WAIST];
    this->actor.shape.rot.y = player->actor.shape.rot.y + 0x8000;

    if (this->isCharging == 0) {
        if (player->unk_858 >= 0.1f) {
            if ((gSaveContext.magicState != MAGIC_STATE_IDLE) ||
                (((this->actor.params & 0xFF00) >> 8) &&
                 !(Magic_RequestChange(play, (this->actor.params & 0xFF00) >> 8, MAGIC_CONSUME_WAIT_PREVIEW)))) {
                func_80A9F350(this, play);
                func_80A9EFE0(this, func_80A9F350);
                this->chargingAlpha = 0;
                this->adjustLightsArg1 = 0.0;
                this->lightColorFrac = 0.0f;
                return;
            }

            this->isCharging = 1;
        }
    }

    if (player->unk_858 >= 0.1f) {
        Rumble_Request(0.0f, (s32)(player->unk_858 * 150.0f), 2, (s32)(player->unk_858 * 150.0f));
    }

    if (player->stateFlags2 & PLAYER_STATE2_17) {
        if ((child != NULL) && (child->update != NULL)) {
            child->parent = NULL;
        }

        if (player->unk_858 <= 0.15f) {
            if ((player->unk_858 >= 0.1f) && (player->meleeWeaponAnimation >= PLAYER_MWA_SPIN_ATTACK_1H)) {
                Audio_PlaySfxGeneral(NA_SE_IT_ROLLING_CUT, &player->actor.projectedPos, 4, &gSfxDefaultFreqAndVolScale,
                                     &gSfxDefaultFreqAndVolScale, &gSfxDefaultReverb);
                Audio_PlaySfxGeneral(NA_SE_IT_SWORD_SWING_HARD, &player->actor.projectedPos, 4,
                                     &gSfxDefaultFreqAndVolScale, &gSfxDefaultFreqAndVolScale, &gSfxDefaultReverb);
            }
            Actor_Kill(&this->actor);
            return;
        } else {
            player->stateFlags2 &= ~PLAYER_STATE2_17;
            if ((this->actor.params & 0xFF00) >> 8) {
                gSaveContext.magicState = MAGIC_STATE_CONSUME_SETUP;
            }
            if (player->unk_858 < 0.85f) {
                this->collider.info.toucher.dmgFlags = D_80AA044C[this->type];
                this->subtype = 1;
                this->scaleTarget = ((this->type == 1) ? 2 : 4);
            } else {
                this->collider.info.toucher.dmgFlags = D_80AA0458[this->type];
                this->subtype = 0;
                this->scaleTarget = ((this->type == 1) ? 4 : 8);
            }

            if (player->meleeWeaponAnimation < PLAYER_MWA_SPIN_ATTACK_1H) { // sword beem 2, definitely not matching lol
                this->subtype += ENMTHUNDER_SUBTYPE_SWORDBEAM_GREAT;
                func_80A9EFE0(this, EnMThunder_SwordBeam_Attack);
                this->timer = 1;
                this->scaleTarget = 12;
                this->collider.info.toucher.dmgFlags = DMG_SWORDBEAM; 
                this->collider.info.toucher.damage = 3;
            } else {
                func_80A9EFE0(this, func_80A9F9B4);
                this->timer = 8;
            }
            Audio_PlaySfxGeneral(sSfxIds[this->subtype], &player->actor.projectedPos, 4, &gSfxDefaultFreqAndVolScale,
                                 &gSfxDefaultFreqAndVolScale, &gSfxDefaultReverb);
            this->lightColorFrac = 1.0f;
            return;
        }
    }

    if (!(player->stateFlags1 & PLAYER_STATE1_12)) {
        if (this->actor.child != NULL) {
            this->actor.child->parent = NULL;
        }
        Actor_Kill(&this->actor);
        return;
    }

    if (player->unk_858 > 0.15f) {
        this->chargingAlpha = 255;
        if (this->actor.child == NULL) {
            Actor_SpawnAsChild(&play->actorCtx, &this->actor, play, ACTOR_EFF_DUST, this->actor.world.pos.x,
                               this->actor.world.pos.y, this->actor.world.pos.z, 0, this->actor.shape.rot.y, 0,
                               this->type + 2);
        }
        this->adjustLightsArg1 += ((((player->unk_858 - 0.15f) * 1.5f) - this->adjustLightsArg1) * 0.5f);

    } else if (player->unk_858 > .1f) {
        this->chargingAlpha = (s32)((player->unk_858 - .1f) * 255.0f * 20.0f);
        this->lightColorFrac = (player->unk_858 - .1f) * 10.0f;
    } else {
        this->chargingAlpha = 0;
    }

    if (player->unk_858 > 0.85f) {
        func_800F4254(&player->actor.projectedPos, 2);
    } else if (player->unk_858 > 0.15f) {
        func_800F4254(&player->actor.projectedPos, 1);
    } else if (player->unk_858 > 0.1f) {
        func_800F4254(&player->actor.projectedPos, 0);
    }

    if (Play_InCsMode(play)) {
        Actor_Kill(&this->actor);
    }
}

void func_80A9F938(EnMThunder* this, PlayState* play) {
    if (this->timer < 2) {
        if (this->chargingAlpha < 40) {
            this->chargingAlpha = 0;
        } else {
            this->chargingAlpha -= 40;
        }
    }

    this->scroll += 2.0f * this->alphaFrac;

    if (this->adjustLightsArg1 < this->lightColorFrac) {
        this->adjustLightsArg1 += ((this->lightColorFrac - this->adjustLightsArg1) * 0.1f);
    } else {
        this->adjustLightsArg1 = this->lightColorFrac;
    }
}

void func_80A9F9B4(EnMThunder* this, PlayState* play) {
    Player* player = GET_PLAYER(play);

    if (Math_StepToF(&this->lightColorFrac, 0.0f, 1 / 16.0f)) {
        Actor_Kill(&this->actor);
    } else {
        Math_SmoothStepToF(&this->actor.scale.x, (s32)this->scaleTarget, 0.6f, 0.8f, 0.0f);
        Actor_SetScale(&this->actor, this->actor.scale.x);
        this->collider.dim.radius = (this->actor.scale.x * 25.0f);
        Collider_UpdateCylinder(&this->actor, &this->collider);
        CollisionCheck_SetAT(play, &play->colChkCtx, &this->collider.base);
    }

    if (this->timer > 0) {
        this->actor.world.pos.x = player->bodyPartsPos[PLAYER_BODYPART_WAIST].x;
        this->actor.world.pos.z = player->bodyPartsPos[PLAYER_BODYPART_WAIST].z;
        this->timer--;
    }

    if (this->lightColorFrac > 0.6f) {
        this->alphaFrac = 1.0f;
    } else {
        this->alphaFrac = this->lightColorFrac * (5.0f / 3.0f);
    }

    func_80A9F938(this, play);

    if (Play_InCsMode(play)) {
        Actor_Kill(&this->actor);
    }
}

void EnMThunder_SwordBeam_Attack(EnMThunder* this, PlayState* play) {
    s32 pad[2];
    f32 sp2C;

    this->actor.shape.rot.x = -this->actor.world.rot.x;

    if (this->lightColorFrac > (9.0f / 10.0f)) {
        this->alphaFrac = 1.0f;
    } else {
        this->alphaFrac = this->lightColorFrac * (10.0f / 9.0f);
    }

    if (Math_StepToF(&this->lightColorFrac, 0.0f, 0.05f)) {
        Actor_Kill(&this->actor);
    } else {
        sp2C = -80.0f * Math_CosS(this->actor.world.rot.x);

        this->actor.world.pos.x += sp2C * Math_SinS(this->actor.shape.rot.y);
        this->actor.world.pos.z += sp2C * Math_CosS(this->actor.shape.rot.y);
        this->actor.world.pos.y += -80.0f * Math_SinS(this->actor.world.rot.x);

        Math_SmoothStepToF(&this->actor.scale.x, this->scaleTarget, 0.6f, 2.0f, 0.0f);
        Actor_SetScale(&this->actor, this->actor.scale.x);

        this->collider.dim.radius = this->actor.scale.x * 5.0f;

        this->collider.dim.pos.x = this->actor.world.pos.x;
        this->collider.dim.pos.y = this->actor.world.pos.y;
        this->collider.dim.pos.z = this->actor.world.pos.z;

        this->collider.dim.pos.x =
            (Math_SinS(this->actor.shape.rot.y) * -5.0f * this->actor.scale.x) + this->actor.world.pos.x;
        this->collider.dim.pos.y = this->actor.world.pos.y;
        this->collider.dim.pos.z =
            (Math_CosS(this->actor.shape.rot.y) * -5.0f * this->actor.scale.z) + this->actor.world.pos.z;

        CollisionCheck_SetAT(play, &play->colChkCtx, &this->collider.base);
    }

    if (this->timer > 0) {
        this->timer--;
    }

    func_80A9F938(this, play);
}

void EnMThunder_Update(Actor* thisx, PlayState* play) {
    EnMThunder* this = (EnMThunder*)thisx;
    f32 blueRadius;
    s32 redGreen;

    this->actionFunc(this, play);
    func_80A9F314(this, play, this->adjustLightsArg1);

    blueRadius = this->lightColorFrac;
    redGreen = (u32)(blueRadius * 255.0f) & 0xFF;
    Lights_PointNoGlowSetInfo(&this->lightInfo, this->actor.world.pos.x, this->actor.world.pos.y,
                              this->actor.world.pos.z, redGreen, redGreen, (u32)(blueRadius * 100.0f),
                              (s32)(blueRadius * 800.0f));
}

void EnMThunder_Draw(Actor* thisx, PlayState* play2) {
    static f32 D_80AA046C[] = { 0.1f, 0.15f, 0.2f, 0.25f, 0.3f, 0.25f, 0.2f, 0.15f };
    PlayState* play = play2;
    EnMThunder* this = (EnMThunder*)thisx;
    Player* player = GET_PLAYER(play);
    f32 phi_f14;
    s32 phi_t1;

    OPEN_DISPS(play->state.gfxCtx, "../z_en_m_thunder.c", 844);

    if (this->subtype >= ENMTHUNDER_SUBTYPE_SWORDBEAM_GREAT) {
        //Matrix_RotateX(-BINANG_TO_DEG(this->actor.shape.rot.x), MTXMODE_APPLY);
    }

    Gfx_SetupDL_25Xlu(play->state.gfxCtx);
    Matrix_Scale(0.02f, 0.02f, 0.02f, MTXMODE_APPLY);
    gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(play->state.gfxCtx, "../z_en_m_thunder.c", 853),
              G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);

    switch (this->subtype) {
        case ENMTHUNDER_SUBTYPE_SPIN_GREAT:
        case ENMTHUNDER_SUBTYPE_SPIN_REGULAR:
            gSPSegment(POLY_XLU_DISP++, 0x08,
                       Gfx_TwoTexScroll(play->state.gfxCtx, G_TX_RENDERTILE,
                                        0xFF - ((u8)(s32)(this->scroll * 30) & 0xFF), 0, 0x40, 0x20, 1,
                                        0xFF - ((u8)(s32)(this->scroll * 20) & 0xFF), 0, 8, 8));
            break;
        case ENMTHUNDER_SUBTYPE_SWORDBEAM_GREAT:
        case ENMTHUNDER_SUBTYPE_SWORDBEAM_REGULAR:
            gSPSegment(POLY_XLU_DISP++, 0x08,
                       Gfx_TwoTexScroll(play->state.gfxCtx, 0, 0, 0, 16, 64, 1, 0,
                                        0x1FF - ((u16)(s32)(this->scroll * 10.0f) & 0x1FF), 32, 128));
            break;
    }

    switch (this->subtype) {
        case ENMTHUNDER_SUBTYPE_SPIN_GREAT:
            gDPSetPrimColor(POLY_XLU_DISP++, 0, 0x80, 255, 255, 170, (u8)(this->alphaFrac * 255));
            gSPDisplayList(POLY_XLU_DISP++, gSpinAttack3DL);
            gSPDisplayList(POLY_XLU_DISP++, gSpinAttack4DL);
            break;

        case ENMTHUNDER_SUBTYPE_SPIN_REGULAR:
            gDPSetPrimColor(POLY_XLU_DISP++, 0, 0x80, 170, 255, 255, (u8)(this->alphaFrac * 255));
            gSPDisplayList(POLY_XLU_DISP++, gSpinAttack1DL);
            gSPDisplayList(POLY_XLU_DISP++, gSpinAttack2DL);
            break;

        case ENMTHUNDER_SUBTYPE_SWORDBEAM_REGULAR:
            gDPSetPrimColor(POLY_XLU_DISP++, 0, 0x80, 170, 255, 255, (u16)(this->alphaFrac * 255.0f));
            gDPSetEnvColor(POLY_XLU_DISP++, 0, 100, 255, 128);
            gSPDisplayList(POLY_XLU_DISP++, gUnusedBeamBladeDL);
            break;

        case ENMTHUNDER_SUBTYPE_SWORDBEAM_GREAT:
            gDPSetPrimColor(POLY_XLU_DISP++, 0, 0x80, 0, 255, 255, (u16)(this->alphaFrac * 255.0f));
            gDPSetEnvColor(POLY_XLU_DISP++, 200, 200, 200, 128);
            gSPDisplayList(POLY_XLU_DISP++, gUnusedBeamBladeDL);
            break;
    }

    Matrix_Mult(&player->mf_9E0, MTXMODE_NEW);

    switch (this->type) {
        case 1:
            Matrix_Translate(0.0f, 220.0f, 0.0f, MTXMODE_APPLY);
            Matrix_Scale(-0.7f, -0.6f, -0.4f, MTXMODE_APPLY);
            Matrix_RotateX(16384.0f, MTXMODE_APPLY);
            break;
        case 0:
            Matrix_Translate(0.0f, 300.0f, -100.0f, MTXMODE_APPLY);
            Matrix_Scale(-1.2f, -1.0f, -0.7f, MTXMODE_APPLY);
            Matrix_RotateX(16384.0f, MTXMODE_APPLY);
            break;
        case 2:
            Matrix_Translate(200.0f, 350.0f, 0.0f, MTXMODE_APPLY);
            Matrix_Scale(-1.8f, -1.4f, -0.7f, MTXMODE_APPLY);
            Matrix_RotateX(16384.0f, MTXMODE_APPLY);
            break;
    }

    if (this->subtype == ENMTHUNDER_SUBTYPE_SWORDBEAM_REGULAR || this->subtype == ENMTHUNDER_SUBTYPE_SWORDBEAM_GREAT) {
        if (this->type == ENMTHUNDER_SUBTYPE_SWORDBEAM_REGULAR || this->type == ENMTHUNDER_SUBTYPE_SWORDBEAM_GREAT) { 
                Matrix_Translate(0.0f, 220.0f, 0.0f, MTXMODE_APPLY);
                Matrix_Scale(-0.7f, -0.6f, -0.4f, MTXMODE_APPLY);
                Matrix_RotateX(-BINANG_TO_DEG(0x4000), MTXMODE_APPLY);
        }
    }

    if (this->unk_1B8 >= 0.85f) {
        phi_f14 = (D_80AA046C[(play->gameplayFrames & 7)] * 6.0f) + 1.0f;
        gDPSetPrimColor(POLY_XLU_DISP++, 0, 0x80, 255, 255, 170, this->chargingAlpha);
        gDPSetEnvColor(POLY_XLU_DISP++, 255, 100, 0, 128);
        phi_t1 = 0x28;
    } else {
        phi_f14 = (D_80AA046C[play->gameplayFrames & 7] * 2.0f) + 1.0f;
        gDPSetPrimColor(POLY_XLU_DISP++, 0, 0x80, 170, 255, 255, this->chargingAlpha);
        gDPSetEnvColor(POLY_XLU_DISP++, 0, 100, 255, 128);
        phi_t1 = 0x14;
    }

    Matrix_Scale(1.0f, phi_f14, phi_f14, MTXMODE_APPLY);

    gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(play->state.gfxCtx, "../z_en_m_thunder.c", 960),
              G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPSegment(POLY_XLU_DISP++, 0x09,
               Gfx_TwoTexScroll(play->state.gfxCtx, G_TX_RENDERTILE, (play->gameplayFrames * 5) & 0xFF, 0, 0x20, 0x20,
                                1, (play->gameplayFrames * 20) & 0xFF, (play->gameplayFrames * phi_t1) & 0xFF, 8, 8));

    gSPDisplayList(POLY_XLU_DISP++, gSpinAttackChargingDL);

    CLOSE_DISPS(play->state.gfxCtx, "../z_en_m_thunder.c", 1031);
}

/* 

void EnMThunder_Draw(Actor* thisx, PlayState* play2) {
    static f32 D_80AA046C[] = { 0.1f, 0.15f, 0.2f, 0.25f, 0.3f, 0.25f, 0.2f, 0.15f };
    PlayState* play = play2;
    EnMThunder* this = (EnMThunder*)thisx;
    Player* player = GET_PLAYER(play);
    f32 phi_f14;
    s32 phi_t1;

    OPEN_DISPS(play->state.gfxCtx, "../z_en_m_thunder.c", 844);
    Gfx_SetupDL_25Xlu(play->state.gfxCtx);
    Matrix_Scale(0.02f, 0.02f, 0.02f, MTXMODE_APPLY);
    gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(play->state.gfxCtx, "../z_en_m_thunder.c", 853),
              G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);

    switch (this->subtype) {
        case 0:
        case 1:
            gSPSegment(POLY_XLU_DISP++, 0x08,
                       Gfx_TwoTexScroll(play->state.gfxCtx, G_TX_RENDERTILE,
                                        0xFF - ((u8)(s32)(this->scroll * 30) & 0xFF), 0, 0x40, 0x20, 1,
                                        0xFF - ((u8)(s32)(this->scroll * 20) & 0xFF), 0, 8, 8));
            break;
    }

    switch (this->subtype) {
        case 0:
            gDPSetPrimColor(POLY_XLU_DISP++, 0, 0x80, 255, 255, 170, (u8)(this->alphaFrac * 255));
            gSPDisplayList(POLY_XLU_DISP++, gSpinAttack3DL);
            gSPDisplayList(POLY_XLU_DISP++, gSpinAttack4DL);
            break;
        case 1:
            gDPSetPrimColor(POLY_XLU_DISP++, 0, 0x80, 170, 255, 255, (u8)(this->alphaFrac * 255));
            gSPDisplayList(POLY_XLU_DISP++, gSpinAttack1DL);
            gSPDisplayList(POLY_XLU_DISP++, gSpinAttack2DL);
            break;
    }

    Matrix_Mult(&player->mf_9E0, MTXMODE_NEW);

    switch (this->type) {
        case 1:
            Matrix_Translate(0.0f, 220.0f, 0.0f, MTXMODE_APPLY);
            Matrix_Scale(-0.7f, -0.6f, -0.4f, MTXMODE_APPLY);
            Matrix_RotateX(16384.0f, MTXMODE_APPLY);
            break;
        case 0:
            Matrix_Translate(0.0f, 300.0f, -100.0f, MTXMODE_APPLY);
            Matrix_Scale(-1.2f, -1.0f, -0.7f, MTXMODE_APPLY);
            Matrix_RotateX(16384.0f, MTXMODE_APPLY);
            break;
        case 2:
            Matrix_Translate(200.0f, 350.0f, 0.0f, MTXMODE_APPLY);
            Matrix_Scale(-1.8f, -1.4f, -0.7f, MTXMODE_APPLY);
            Matrix_RotateX(16384.0f, MTXMODE_APPLY);
            break;
    }

    if (this->unk_1B8 >= 0.85f) {
        phi_f14 = (D_80AA046C[(play->gameplayFrames & 7)] * 6.0f) + 1.0f;
        gDPSetPrimColor(POLY_XLU_DISP++, 0, 0x80, 255, 255, 170, this->chargingAlpha);
        gDPSetEnvColor(POLY_XLU_DISP++, 255, 100, 0, 128);
        phi_t1 = 0x28;
    } else {
        phi_f14 = (D_80AA046C[play->gameplayFrames & 7] * 2.0f) + 1.0f;
        gDPSetPrimColor(POLY_XLU_DISP++, 0, 0x80, 170, 255, 255, this->chargingAlpha);
        gDPSetEnvColor(POLY_XLU_DISP++, 0, 100, 255, 128);
        phi_t1 = 0x14;
    }
    Matrix_Scale(1.0f, phi_f14, phi_f14, MTXMODE_APPLY);
    gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(play->state.gfxCtx, "../z_en_m_thunder.c", 960),
              G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);

    gSPSegment(POLY_XLU_DISP++, 0x09,
               Gfx_TwoTexScroll(play->state.gfxCtx, G_TX_RENDERTILE, (play->gameplayFrames * 5) & 0xFF, 0, 0x20, 0x20,
                                1, (play->gameplayFrames * 20) & 0xFF, (play->gameplayFrames * phi_t1) & 0xFF, 8, 8));

    gSPDisplayList(POLY_XLU_DISP++, gSpinAttackChargingDL);

    CLOSE_DISPS(play->state.gfxCtx, "../z_en_m_thunder.c", 1031);
}

*/