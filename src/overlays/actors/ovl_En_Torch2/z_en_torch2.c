/*
 * File: z_en_torch2.c
 * Overlay: ovl_En_Torch2
 * Description: Dark Link
 */

#include "z_en_torch2.h"
#include "assets/objects/object_torch2/object_torch2.h"

#define FLAGS (ACTOR_FLAG_0 | ACTOR_FLAG_2 | ACTOR_FLAG_4 | ACTOR_FLAG_5)

typedef enum {
    /* 0 */ ENTORCH2_WAIT,
    /* 1 */ ENTORCH2_ATTACK,
    /* 2 */ ENTORCH2_DEATH,
    /* 3 */ ENTORCH2_DAMAGE
} EnTorch2ActionStates;

void EnTorch2_Init(Actor* thisx, PlayState* play2);
void EnTorch2_Destroy(Actor* thisx, PlayState* play);
void EnTorch2_Update(Actor* thisx, PlayState* play2);
void EnTorch2_Draw(Actor* thisx, PlayState* play2);

ActorInit En_Torch2_InitVars = {
    ACTOR_EN_TORCH2,
    ACTORCAT_BOSS,
    FLAGS,
    OBJECT_TORCH2,
    sizeof(PlayerEnemy),
    (ActorFunc)EnTorch2_Init,
    (ActorFunc)EnTorch2_Destroy,
    (ActorFunc)EnTorch2_Update,
    (ActorFunc)EnTorch2_Draw,
};

static DamageTable sDamageTable = {
    /* Deku nut      */ DMG_ENTRY(0, 0x1),
    /* Deku stick    */ DMG_ENTRY(2, 0x0),
    /* Slingshot     */ DMG_ENTRY(1, 0x0),
    /* Explosive     */ DMG_ENTRY(2, 0x0),
    /* Boomerang     */ DMG_ENTRY(0, 0x1),
    /* Normal arrow  */ DMG_ENTRY(2, 0x0),
    /* Hammer swing  */ DMG_ENTRY(2, 0x0),
    /* Hookshot      */ DMG_ENTRY(0, 0x1),
    /* Kokiri sword  */ DMG_ENTRY(1, 0x0),
    /* Master sword  */ DMG_ENTRY(2, 0x0),
    /* Giant's Knife */ DMG_ENTRY(4, 0x0),
    /* Fire arrow    */ DMG_ENTRY(2, 0x0),
    /* Ice arrow     */ DMG_ENTRY(2, 0x0),
    /* Light arrow   */ DMG_ENTRY(2, 0x0),
    /* Unk arrow 1   */ DMG_ENTRY(2, 0x0),
    /* Unk arrow 2   */ DMG_ENTRY(2, 0x0),
    /* Unk arrow 3   */ DMG_ENTRY(2, 0x0),
    /* Fire magic    */ DMG_ENTRY(2, 0xE),
    /* Ice magic     */ DMG_ENTRY(0, 0x6),
    /* Light magic   */ DMG_ENTRY(3, 0xD),
    /* Shield        */ DMG_ENTRY(0, 0x0),
    /* Mirror Ray    */ DMG_ENTRY(0, 0x0),
    /* Kokiri spin   */ DMG_ENTRY(1, 0x0),
    /* Giant spin    */ DMG_ENTRY(4, 0x0),
    /* Master spin   */ DMG_ENTRY(2, 0x0),
    /* Kokiri jump   */ DMG_ENTRY(2, 0x0),
    /* Giant jump    */ DMG_ENTRY(8, 0x0),
    /* Master jump   */ DMG_ENTRY(4, 0x0),
    /* Unknown 1     */ DMG_ENTRY(0, 0x0),
    /* Unblockable   */ DMG_ENTRY(0, 0x0),
    /* Hammer jump   */ DMG_ENTRY(4, 0x0),
    /* Unknown 2     */ DMG_ENTRY(0, 0x0),
};

void EnTorch2_Init(Actor* thisx, PlayState* play2) {
    PlayState* play = play2;
    PlayerEnemy* this = (PlayerEnemy*)thisx;

    // init dark link stuff
    this->sStickTilt = 0.0f;
    this->sStickAngle = 0;
    this->sSwordJumpHeight = 0.0f;
    this->sHoldShieldTimer = 0;
    this->sZTargetFlag = false;
    this->sDeathFlag = false;

    this->sInput.cur.button = this->sInput.press.button = this->sInput.rel.button = 0;
    this->sInput.cur.stick_x = this->sInput.cur.stick_y = 0;
    this->currentShield = PLAYER_SHIELD_HYLIAN;
    this->heldItemAction = this->heldItemId = PLAYER_IA_SWORD_MASTER;
    Player_SetModelGroup(this, PLAYER_MODELGROUP_SWORD);
    play->playerInit(this, play, &gDarkLinkSkel);
    this->actor.naviEnemyId = NAVI_ENEMY_DARK_LINK;
    this->cylinder.base.acFlags = AC_ON | AC_TYPE_PLAYER;
    this->meleeWeaponQuads[0].base.atFlags = this->meleeWeaponQuads[1].base.atFlags = AT_ON | AT_TYPE_ENEMY;
    this->meleeWeaponQuads[0].base.acFlags = this->meleeWeaponQuads[1].base.acFlags = AC_ON | AC_HARD | AC_TYPE_PLAYER;
    this->meleeWeaponQuads[0].base.colType = this->meleeWeaponQuads[1].base.colType = COLTYPE_METAL;
    this->meleeWeaponQuads[0].info.toucher.damage = this->meleeWeaponQuads[1].info.toucher.damage = 8;
    this->meleeWeaponQuads[0].info.bumperFlags = this->meleeWeaponQuads[1].info.bumperFlags = BUMP_ON;
    this->shieldQuad.base.atFlags = AT_ON | AT_TYPE_ENEMY;
    this->shieldQuad.base.acFlags = AC_ON | AC_HARD | AC_TYPE_PLAYER;
    this->actor.colChkInfo.damageTable = &sDamageTable;
    this->actor.colChkInfo.health = gSaveContext.healthCapacity >> 3;
    this->actor.colChkInfo.cylRadius = 60;
    this->actor.colChkInfo.cylHeight = 100;
    play->func_11D54(this, play);

    this->sActionState = ENTORCH2_WAIT;
    this->sDodgeRollState = 0;
    this->sSwordJumpHeight = 0.0f;
    this->sSwordJumpState = 0;
    this->sJumpslashTimer = 0;
    this->sJumpslashFlag = false;
    this->sCounterState = this->sStaggerTimer = this->sStaggerCount = 0;
    this->sLastSwordAnim = 0;
    this->sAlpha = 95;
    this->sSpawnPoint = this->actor.home.pos;
}

void EnTorch2_Destroy(Actor* thisx, PlayState* play) {
    s32 pad;
    PlayerEnemy* this = (PlayerEnemy*)thisx;

    Effect_Delete(play, this->meleeWeaponEffectIndex);
    func_800F5B58();
    Collider_DestroyCylinder(play, &this->cylinder);
    Collider_DestroyQuad(play, &this->meleeWeaponQuads[0]);
    Collider_DestroyQuad(play, &this->meleeWeaponQuads[1]);
    Collider_DestroyQuad(play, &this->shieldQuad);
}

Actor* EnTorch2_GetAttackItem(PlayState* play, PlayerEnemy* this) {
    Actor* rangedItem = Actor_GetProjectileActor(play, &this->actor, 4000.0f);

    if (rangedItem != NULL) {
        return rangedItem;
    } else {
        return func_80033684(play, &this->actor);
    }
}

s32 EnTorch2_SwingSword(PlayState* play, Input* input, PlayerEnemy* this) {
    f32 noAttackChance = 0.0f;
    s32 attackDelay = 7;
    Player* player = GET_PLAYER(play);

    if ((this->speedXZ < 0.0f) || (player->speedXZ < 0.0f)) {
        return 0;
    }
    if (gSaveContext.health < 0x50) {
        attackDelay = 15;
        noAttackChance += 0.3f;
    }
    if (this->sAlpha != 255) {
        noAttackChance += 2.0f;
    }
    if ((((play->gameplayFrames & attackDelay) == 0) || (this->sSwordJumpState != 0)) && (noAttackChance <= Rand_ZeroOne())) {
        if (this->sSwordJumpState == 0) {
            switch ((s32)(Rand_ZeroOne() * 7.0f)) {
                case 1:
                case 5:
                    this->sStickAngle += 0x4000;
                    this->sStickTilt = 127.0f;
                    break;
                case 2:
                case 6:
                    this->sStickAngle -= 0x4000;
                    this->sStickTilt = 127.0f;
                    break;
            }
        }
        input->cur.button = BTN_B;
        return 1;
    }
    return 0;
}

void EnTorch2_Backflip(PlayerEnemy* this, Input* input, Actor* thisx) {
    thisx->world.rot.y = thisx->shape.rot.y = thisx->yawTowardsPlayer;
    this->sStickAngle = thisx->yawTowardsPlayer + 0x8000;
    this->sStickTilt = 127.0f;
    this->sZTargetFlag = true;
    input->cur.button = BTN_A;
    this->invincibilityTimer = 10;
    this->sCounterState = 0;
}

void EnTorch2_Update(Actor* thisx, PlayState* play2) {
    PlayState* play = play2;
    Player* player2 = GET_PLAYER(play2);
    Player* player = player2;
    PlayerEnemy* this = (PlayerEnemy*)thisx;
    Input* input = &this->sInput;
    Camera* mainCam;
    s16 sp66;
    u8 staggerThreshold;
    s8 stickY;
    s32 pad60;
    Actor* attackItem;
    s16 sp5A;
    s16 pad58;
    u32 pad54;
    f32 sp50;
    s16 sp4E;

    sp5A = player->actor.shape.rot.y - this->actor.shape.rot.y;
    input->cur.button = 0;
    mainCam = Play_GetCamera(play, CAM_ID_MAIN);
    attackItem = EnTorch2_GetAttackItem(play, this);

    // punish cheaters who try to abuse dark link spawning off of a cliff
    if (play->sceneId != SCENE_WATER_TEMPLE) {
        if (this->invincibilityTimer <= 0) {
            CollisionPoly* groundPoly;
            Vec3f checkPos = this->actor.world.pos;
            checkPos.y += 10.0f;
            if (BgCheck_EntityRaycastDown1(&play->colCtx, &groundPoly, &checkPos) == BGCHECK_Y_MIN) {
                Math_Vec3f_Copy(&this->actor.world.pos, &(GET_PLAYER(play)->actor.world.pos));
            }
        }
    }

    switch (this->sActionState) {
        case ENTORCH2_WAIT:
            this->actor.shape.rot.y = this->actor.world.rot.y = this->actor.yawTowardsPlayer;
            this->skelAnime.curFrame = 0.0f;
            this->skelAnime.playSpeed = 0.0f;
            this->actor.world.pos.x = (Math_SinS(this->actor.world.rot.y) * 25.0f) + this->sSpawnPoint.x;
            this->actor.world.pos.z = (Math_CosS(this->actor.world.rot.y) * 25.0f) + this->sSpawnPoint.z;
            if ((this->actor.xzDistToPlayer <= 120.0f) || Actor_IsTargeted(play, &this->actor) ||
                (attackItem != NULL)) {
                if (attackItem != NULL) {
                    this->sDodgeRollState = 1;
                    this->sStickAngle = this->actor.yawTowardsPlayer;
                    this->sStickTilt = 127.0f;
                    input->cur.button = BTN_A;
                    this->sZTargetFlag = false;
                    sp66 = mainCam->camDir.y - this->sStickAngle;
                    this->sInput.cur.stick_x = this->sStickTilt * Math_SinS(sp66);
                    stickY = this->sStickTilt * Math_CosS(sp66);
                    if (stickY) {}
                    this->sInput.cur.stick_y = stickY;
                }
                func_800F5ACC(NA_BGM_MINI_BOSS);
                this->sActionState = ENTORCH2_ATTACK;
            }
            break;

        case ENTORCH2_ATTACK:
            this->sStickTilt = 0.0f;

            // Handles Dark Link's sword clanking on Link's sword

            if ((this->meleeWeaponQuads[0].base.acFlags & AC_BOUNCED) ||
                (this->meleeWeaponQuads[1].base.acFlags & AC_BOUNCED)) {
                this->meleeWeaponQuads[0].base.acFlags &= ~AC_BOUNCED;
                this->meleeWeaponQuads[1].base.acFlags &= ~AC_BOUNCED;
                this->meleeWeaponQuads[0].base.atFlags |= AT_BOUNCED;
                this->meleeWeaponQuads[1].base.atFlags |= AT_BOUNCED;
                this->cylinder.base.acFlags &= ~AC_HIT;

                if (this->sLastSwordAnim != this->meleeWeaponAnimation) {
                    this->sStaggerCount++;
                    this->sLastSwordAnim = this->meleeWeaponAnimation;
                }
                /*! @bug
                 *  This code is needed to reset sCounterState, and should run regardless
                 *  of how much health Link has. Without it, sCounterState stays at 2 until
                 *  something else resets it, preventing Dark Link from using his shield and
                 *  creating a hole in his defenses. This also makes Dark Link harder at low
                 *  health, while the other health checks are intended to make him easier.
                 */
                if ((gSaveContext.health < 0x50) && (this->sCounterState != 0)) {
                    this->sCounterState = 0;
                    this->sStaggerTimer = 50;
                }
            }
            if ((this->sCounterState != 0) && (this->meleeWeaponState != 0)) {
                CollisionCheck_SetAC(play, &play->colChkCtx, &this->meleeWeaponQuads[0].base);
                CollisionCheck_SetAC(play, &play->colChkCtx, &this->meleeWeaponQuads[1].base);
            }

            // Ignores hits when jumping on Link's sword
            if ((this->invincibilityTimer < 0) && (this->sActionState != ENTORCH2_DAMAGE) &&
                (this->cylinder.base.acFlags & AC_HIT)) {
                this->cylinder.base.acFlags &= ~AC_HIT;
            }

            // Handles Dark Link rolling to dodge item attacks

            if (this->sDodgeRollState != 0) {
                this->sStickTilt = 127.0f;
            } else if (attackItem != NULL) {
                this->sDodgeRollState = 1;
                this->sStickAngle = this->actor.yawTowardsPlayer;
                this->sStickTilt = 127.0f;
                input->cur.button = BTN_A;
            } else if (this->sJumpslashTimer == 0) {

                // Handles Dark Link's initial reaction to jumpslashes

                if (((player->meleeWeaponState != 0) || (player->actor.velocity.y > -3.0f)) &&
                    (player->meleeWeaponAnimation == PLAYER_MWA_JUMPSLASH_START)) {
                    this->actor.world.rot.y = this->actor.shape.rot.y = this->actor.yawTowardsPlayer;

                    if (play->gameplayFrames % 2) {
                        this->sStickAngle = this->actor.yawTowardsPlayer + 0x4000;
                    } else {
                        this->sStickAngle = this->actor.yawTowardsPlayer - 0x4000;
                    }
                    this->sStickTilt = 127.0f;
                    this->sJumpslashTimer = 15;
                    this->sJumpslashFlag = false;
                    input->cur.button |= BTN_A;

                    // Handles jumping on Link's sword

                } else if (this->sSwordJumpState != 0) {
                    this->sStickTilt = 0.0f;
                    player->stateFlags3 |= PLAYER_STATE3_2;
                    Math_SmoothStepToF(&this->actor.world.pos.x,
                                       (Math_SinS(player->actor.shape.rot.y - 0x3E8) * 45.0f) +
                                           player->actor.world.pos.x,
                                       1.0f, 5.0f, 0.0f);
                    Math_SmoothStepToF(&this->actor.world.pos.z,
                                       (Math_CosS(player->actor.shape.rot.y - 0x3E8) * 45.0f) +
                                           player->actor.world.pos.z,
                                       1.0f, 5.0f, 0.0f);
                    this->sSwordJumpTimer--;
                    if (((u32)this->sSwordJumpTimer == 0) ||
                        ((player->invincibilityTimer > 0) && (this->meleeWeaponState == 0))) {
                        this->actor.world.rot.y = this->actor.shape.rot.y = this->actor.yawTowardsPlayer;
                        input->cur.button = BTN_A;
                        player->stateFlags3 &= ~PLAYER_STATE3_2;
                        this->sStickTilt = 127.0f;
                        player->skelAnime.curFrame = 3.0f;
                        this->sStickAngle = this->actor.yawTowardsPlayer + 0x8000;
                        this->sSwordJumpTimer = this->sSwordJumpState = 0;
                        this->actor.flags |= ACTOR_FLAG_0;
                    } else if (this->sSwordJumpState == 1) {
                        if (this->sSwordJumpTimer < 16) {
                            EnTorch2_SwingSword(play, input, this);
                            this->sSwordJumpState++;
                        } else if (this->sSwordJumpTimer == 19) {
                            func_800F4190(&this->actor.projectedPos, NA_SE_VO_LI_AUTO_JUMP);
                        }
                    }
                } else {
                    // This does nothing, as sHoldShieldTimer is never set.
                    if (this->sHoldShieldTimer != 0) {
                        this->sHoldShieldTimer--;
                        input->cur.button = BTN_R;
                    }

                    // Handles Dark Link's reaction to sword attack other than jumpslashes

                    if (func_800354B4(play, &this->actor, 120.0f, 0x7FFF, 0x7FFF, this->actor.world.rot.y)) {
                        if ((player->meleeWeaponAnimation == PLAYER_MWA_STAB_1H) &&
                            (this->actor.xzDistToPlayer < 90.0f)) {

                            // Handles the reaction to a one-handed stab. If the conditions are satisfied,
                            // Dark Link jumps on Link's sword. Otherwise he backflips away.

                            if ((this->meleeWeaponState == 0) && (this->sCounterState == 0) &&
                                (player->invincibilityTimer == 0) &&
                                (player->meleeWeaponAnimation == PLAYER_MWA_STAB_1H) &&
                                (this->actor.xzDistToPlayer <= 85.0f) && Actor_IsTargeted(play, &this->actor)) {

                                this->sStickTilt = 0.0f;
                                this->sSwordJumpState = 1;
                                player->stateFlags3 |= PLAYER_STATE3_2;
                                this->actor.flags &= ~ACTOR_FLAG_0;
                                this->sSwordJumpTimer = 27;
                                player->meleeWeaponState = 0;
                                player->speedXZ = 0.0f;
                                this->invincibilityTimer = -7;
                                this->speedXZ = 0.0f;
                                player->skelAnime.curFrame = 2.0f;
                                LinkAnimation_Update(play, &player->skelAnime);
                                this->sHoldShieldTimer = 0;
                                input->cur.button = BTN_A;
                            } else {
                                EnTorch2_Backflip(this, input, &this->actor);
                            }
                        } else {

                            // Handles reactions to all other sword attacks

                            this->sStickAngle = thisx->yawTowardsPlayer;
                            input->cur.button = BTN_B;

                            if (player->meleeWeaponAnimation <= PLAYER_MWA_FORWARD_COMBO_2H) {
                                this->sStickTilt = 0.0f;
                            } else if (player->meleeWeaponAnimation <= PLAYER_MWA_RIGHT_COMBO_2H) {
                                this->sStickTilt = 127.0f;
                                this->sStickAngle += 0x4000;
                            } else if (player->meleeWeaponAnimation <= PLAYER_MWA_LEFT_COMBO_2H) {
                                this->sStickTilt = 127.0f;
                                this->sStickAngle -= 0x4000;
                            } else if (player->meleeWeaponAnimation <= PLAYER_MWA_HAMMER_SIDE) {
                                input->cur.button = BTN_R;
                            } else if (player->meleeWeaponAnimation <= PLAYER_MWA_BIG_SPIN_2H) {
                                EnTorch2_Backflip(this, input, &this->actor);
                            } else {
                                EnTorch2_Backflip(this, input, &this->actor);
                            }
                            if (!CHECK_BTN_ANY(input->cur.button, BTN_A | BTN_R) && (this->meleeWeaponState == 0) &&
                                (player->meleeWeaponState != 0)) {
                                this->sCounterState = 1;
                            }
                        }
                    } else {

                        // Handles movement and attacks when not reacting to Link's actions

                        this->sStickAngle = thisx->yawTowardsPlayer;
                        sp50 = 0.0f;
                        if ((90.0f >= this->actor.xzDistToPlayer) && (this->actor.xzDistToPlayer > 70.0f) &&
                            (ABS(sp5A) >= 0x7800) &&
                            (this->actor.isTargeted || !(player->stateFlags1 & PLAYER_STATE1_22))) {
                            EnTorch2_SwingSword(play, input, this);
                        } else if (((this->actor.xzDistToPlayer <= 70.0f) ||
                                    ((this->actor.xzDistToPlayer <= 80.0f + sp50) &&
                                     (player->meleeWeaponState != 0))) &&
                                   (this->meleeWeaponState == 0)) {
                            if (!EnTorch2_SwingSword(play, input, this) && (this->meleeWeaponState == 0) &&
                                (this->sCounterState == 0)) {
                                EnTorch2_Backflip(this, input, &this->actor);
                            }
                        } else if (this->actor.xzDistToPlayer <= 50 + sp50) {
                            this->sStickTilt = 127.0f;
                            this->sStickAngle = this->actor.yawTowardsPlayer;
                            if (!this->actor.isTargeted) {
                                Math_SmoothStepToS(&this->sStickAngle, player->actor.shape.rot.y + 0x7FFF, 1, 0x2328, 0);
                            }
                        } else if (this->actor.xzDistToPlayer > 100.0f + sp50) {
                            if ((player->meleeWeaponState == 0) ||
                                !((player->meleeWeaponAnimation >= PLAYER_MWA_SPIN_ATTACK_1H) &&
                                  (player->meleeWeaponAnimation <= PLAYER_MWA_BIG_SPIN_2H)) ||
                                (this->actor.xzDistToPlayer >= 280.0f)) {
                                this->sStickTilt = 127.0f;
                                this->sStickAngle = this->actor.yawTowardsPlayer;
                                if (!this->actor.isTargeted) {
                                    Math_SmoothStepToS(&this->sStickAngle, player->actor.shape.rot.y + 0x7FFF, 1, 0x2328, 0);
                                }
                            } else {
                                EnTorch2_Backflip(this, input, &this->actor);
                            }
                        } else if (((ABS(sp5A) < 0x7800) && (ABS(sp5A) >= 0x3000)) ||
                                   !EnTorch2_SwingSword(play, input, this)) {
                            this->sStickAngle = this->actor.yawTowardsPlayer;
                            this->sStickTilt = 127.0f;
                            if (!this->actor.isTargeted) {
                                Math_SmoothStepToS(&this->sStickAngle, player->actor.shape.rot.y + 0x7FFF, 1, 0x2328, 0);
                            }
                        }
                    }
                }

                // Handles Dark Link's counterattack to jumpslashes

            } else if (this->sJumpslashFlag && (this->sAlpha == 255) && (this->actor.velocity.y > 0)) {
                input->cur.button |= BTN_B;
            } else if (!this->sJumpslashFlag && (this->actor.bgCheckFlags & BGCHECKFLAG_GROUND)) {
                this->actor.world.rot.y = this->actor.shape.rot.y = this->actor.yawTowardsPlayer;
                this->sStickAngle = this->actor.yawTowardsPlayer;
                if (this->sAlpha != 255) {
                    this->sStickAngle += 0x8000;
                    this->sStickTilt = 127.0f;
                    this->sZTargetFlag = true;
                }
                input->cur.button |= BTN_A;
                this->sJumpslashFlag = true;
                this->invincibilityTimer = 10;
            }

            // Rotates Dark Link's stick angle from Link-relative to camera-relative.

            sp66 = mainCam->camDir.y - this->sStickAngle;
            this->sInput.cur.stick_x = this->sStickTilt * Math_SinS(sp66);
            stickY = this->sStickTilt * Math_CosS(sp66);
            if (this->sAlpha) {}
            this->sInput.cur.stick_y = stickY;

            if ((this->sAlpha != 255) && ((play->gameplayFrames % 8) == 0)) {
                this->sAlpha++;
            }
            break;

        case ENTORCH2_DAMAGE:
            this->meleeWeaponState = 0;
            input->cur.stick_x = input->cur.stick_y = 0;
            if ((this->invincibilityTimer > 0) && (this->actor.world.pos.y < (this->actor.floorHeight - 160.0f))) {
                this->stateFlags3 &= ~PLAYER_STATE3_0;
                this->actor.flags |= ACTOR_FLAG_0;
                this->invincibilityTimer = 0;
                this->actor.velocity.y = 0.0f;
                this->actor.world.pos.y = this->sSpawnPoint.y + 40.0f;
                this->actor.world.pos.x = (Math_SinS(player->actor.shape.rot.y) * -120.0f) + player->actor.world.pos.x;
                this->actor.world.pos.z = (Math_CosS(player->actor.shape.rot.y) * -120.0f) + player->actor.world.pos.z;
                if ((Actor_WorldDistXYZToPoint(&this->actor, &this->sSpawnPoint) > 800.0f) && play->sceneId == SCENE_WATER_TEMPLE) {
                    sp50 = Rand_ZeroOne() * 20.0f;
                    sp4E = Rand_CenteredFloat(4000.0f);
                    this->actor.shape.rot.y = this->actor.world.rot.y =
                        Math_Vec3f_Yaw(&this->sSpawnPoint, &player->actor.world.pos);
                    this->actor.world.pos.x =
                        (Math_SinS(this->actor.world.rot.y + sp4E) * (25.0f + sp50)) + this->sSpawnPoint.x;
                    this->actor.world.pos.z =
                        (Math_CosS(this->actor.world.rot.y + sp4E) * (25.0f + sp50)) + this->sSpawnPoint.z;
                    this->actor.world.pos.y = this->sSpawnPoint.y;
                } else {
                    this->actor.world.pos.y = this->actor.floorHeight;
                }
                
                Math_Vec3f_Copy(&this->actor.home.pos, &this->actor.world.pos);
                play->func_11D54(this, play);
                this->sActionState = ENTORCH2_ATTACK;
                this->sStickTilt = 0.0f;
                if (this->sAlpha != 255) {
                    this->sStaggerCount = 0;
                    this->sStaggerTimer = 0;
                }
            }
            break;

        case ENTORCH2_DEATH:
            if (this->sAlpha - 13 <= 0) {
                this->sAlpha = 0;
                Actor_Kill(&this->actor);
                return;
            }
            this->sAlpha -= 13;
            this->actor.shape.shadowAlpha -= 13;
            break;
    }

    // Causes Dark Link to shield in place when Link is using magic attacks other than the spin attack

    if ((gSaveContext.magicState == MAGIC_STATE_METER_FLASH_1) &&
        (player->meleeWeaponState == 0 || !((player->meleeWeaponAnimation >= PLAYER_MWA_SPIN_ATTACK_1H) &&
                                            (player->meleeWeaponAnimation <= PLAYER_MWA_BIG_SPIN_2H)))) {
        this->sStickTilt = 0.0f;
        input->cur.stick_x = 0;
        input->cur.stick_y = 0;
        input->cur.button = BTN_R;
    }

    if ((this->sActionState == ENTORCH2_ATTACK) && (this->actor.xzDistToPlayer <= 610.0f) && this->sZTargetFlag) {
        input->cur.button |= BTN_Z;
    }

    // Updates Dark Link's "controller". The conditional seems to cause him to
    // stop targeting and hold shield if he's been holding it long enough.

    pad54 = input->prev.button ^ input->cur.button;
    input->press.button = input->cur.button & pad54;
    if (CHECK_BTN_ANY(input->cur.button, BTN_R)) {
        input->cur.button = ((this->sCounterState == 0) && (this->meleeWeaponState == 0)) ? BTN_R : input->cur.button ^ BTN_R;
    }
    input->rel.button = input->prev.button & pad54;
    input->prev.button = input->cur.button & (u16) ~(BTN_A | BTN_B);
    PadUtils_UpdateRelXY(input);

    input->press.stick_x += (s8)(input->cur.stick_x - input->prev.stick_x);
    input->press.stick_y += (s8)(input->cur.stick_y - input->prev.stick_y);

    // Handles Dark Link being damaged

    if ((this->actor.colChkInfo.health == 0) && this->sDeathFlag) {
        this->csMode = PLAYER_CSMODE_24;
        this->unk_448 = &player->actor;
        this->doorBgCamIndex = 1;
        this->sDeathFlag = false;
    }
    if ((this->invincibilityTimer == 0) && (this->actor.colChkInfo.health != 0) &&
        (this->cylinder.base.acFlags & AC_HIT) && !(this->stateFlags1 & PLAYER_STATE1_26) &&
        !(this->meleeWeaponQuads[0].base.atFlags & AT_HIT) && !(this->meleeWeaponQuads[1].base.atFlags & AT_HIT)) {

        if (!Actor_ApplyDamage(&this->actor)) {
            func_800F5B58();
            this->actor.flags &= ~(ACTOR_FLAG_0 | ACTOR_FLAG_2);
            this->unk_8A1 = 2;
            this->unk_8A4 = 6.0f;
            this->unk_8A8 = 6.0f;
            this->unk_8A0 = this->actor.colChkInfo.damage;
            this->unk_8A2 = this->actor.yawTowardsPlayer + 0x8000;
            this->sDeathFlag++;
            this->sActionState = ENTORCH2_DEATH;
            Enemy_StartFinishingBlow(play, &this->actor);
            Item_DropCollectibleRandom(play, &this->actor, &thisx->world.pos, 0xC0);
            this->stateFlags3 &= ~PLAYER_STATE3_2;
        } else {
            func_800F5ACC(NA_BGM_MINI_BOSS);
            if (this->actor.colChkInfo.damageEffect == 1) {
                if (this->sAlpha == 255) {
                    Actor_SetColorFilter(&this->actor, COLORFILTER_COLORFLAG_BLUE, 255, COLORFILTER_BUFFLAG_OPA, 80);
                } else {
                    Actor_SetColorFilter(&this->actor, COLORFILTER_COLORFLAG_BLUE, 255, COLORFILTER_BUFFLAG_XLU, 80);
                }
            } else {
                this->actor.flags &= ~ACTOR_FLAG_0;
                this->unk_8A0 = this->actor.colChkInfo.damage;
                this->unk_8A1 = 1;
                this->unk_8A8 = 6.0f;
                this->unk_8A4 = 8.0f;
                this->unk_8A2 = this->actor.yawTowardsPlayer + 0x8000;
                Actor_SetDropFlag(&this->actor, &this->cylinder.info, true);
                this->stateFlags3 &= ~PLAYER_STATE3_2;
                this->stateFlags3 |= PLAYER_STATE3_0;
                this->sActionState = ENTORCH2_DAMAGE;
                if (this->sAlpha == 255) {
                    Actor_SetColorFilter(&this->actor, COLORFILTER_COLORFLAG_RED, 255, COLORFILTER_BUFFLAG_OPA, 12);
                } else {
                    Actor_SetColorFilter(&this->actor, COLORFILTER_COLORFLAG_RED, 255, COLORFILTER_BUFFLAG_XLU, 12);
                }
            }
        }
        this->actor.colChkInfo.damage = 0;
        this->unk_8A0 = 0;
    }

    // Handles being frozen by a deku nut

    if ((this->actor.colorFilterTimer == 0) || (this->actor.colorFilterParams & 0x4000)) {
        this->stateFlags3 &= ~PLAYER_STATE3_2;
    } else {
        this->stateFlags3 |= PLAYER_STATE3_2;
        this->stateFlags1 &= ~PLAYER_STATE1_26;
        this->invincibilityTimer = 0;
        input->press.stick_x = input->press.stick_y = 0;
        /*! @bug
         *  Setting cur.button to 0 clears the Z-trigger, causing Dark Link to break his
         *  lock on Link. If he presses A while not locked on, he'll put his sword away.
         *  This clears his held item param permanently and makes him unable to attack.
         */
        input->cur.button = 0;
        input->press.button = 0;
        this->speedXZ = 0.0f;
    }

    play->playerUpdate(this, play, input);

    /*
     * Handles sword clanks and removes their recoil for both Links. Dark Link staggers
     * if he's had to counter with enough different sword animations in a row.
     */
    if (this->speedXZ == -18.0f) {
        staggerThreshold = (u32)Rand_CenteredFloat(2.0f) + 6;
        if (gSaveContext.health < 0x50) {
            staggerThreshold = (u32)Rand_CenteredFloat(2.0f) + 3;
        }
        if (this->actor.xzDistToPlayer > 80.0f) {
            this->speedXZ = 1.2f;
        } else if (this->actor.xzDistToPlayer < 70.0f) {
            this->speedXZ = -1.5f;
        } else {
            this->speedXZ = 1.0f;
        }
        if (staggerThreshold < this->sStaggerCount) {
            this->skelAnime.playSpeed *= 0.6f;
            func_800F4190(&this->actor.projectedPos, NA_SE_PL_DAMAGE);
            this->sStaggerTimer = 0;
            this->sStaggerCount = 0;
        }
    }
    if (player->speedXZ == -18.0f) {
        if (this->actor.xzDistToPlayer > 80.0f) {
            player->speedXZ = 1.2f;
        } else if (this->actor.xzDistToPlayer < 70.0f) {
            player->speedXZ = -1.5f;
        } else {
            player->speedXZ = 1.0f;
        }
    }
    /*
     * This ensures Dark Link's counter animation mirrors Link's exactly.
     */
    if ((this->sCounterState != 0) && (this->sCounterState == 1)) {
        if (this->meleeWeaponState == 0) {
            this->sCounterState = 0;
        } else {
            this->sCounterState = 2;
            this->meleeWeaponState = 1;
            this->skelAnime.curFrame = player->skelAnime.curFrame - player->skelAnime.playSpeed;
            this->skelAnime.playSpeed = player->skelAnime.playSpeed;
            LinkAnimation_Update(play, &this->skelAnime);
            Collider_ResetQuadAT(play, &this->meleeWeaponQuads[0].base);
            Collider_ResetQuadAT(play, &this->meleeWeaponQuads[1].base);
        }
    }
    if (this->sStaggerTimer != 0) {
        this->sStaggerTimer--;
        if (this->sStaggerTimer == 0) {
            this->sCounterState = 0;
            this->sStaggerCount = 0;
        }
    }
    if (this->sDodgeRollState != 0) {
        if (this->sDodgeRollState == 1) {
            this->invincibilityTimer = 20;
        }
        this->sDodgeRollState = (this->invincibilityTimer > 0) ? 2 : 0;
    }
    if (this->invincibilityTimer != 0) {
        this->cylinder.base.colType = COLTYPE_NONE;
        this->cylinder.info.elemType = ELEMTYPE_UNK5;
    } else {
        this->cylinder.base.colType = COLTYPE_HIT5;
        this->cylinder.info.elemType = ELEMTYPE_UNK1;
    }
    /*
     * Handles the jump movement onto Link's sword. Dark Link doesn't move during the
     * sword jump. Instead, his shape y-offset is increased (see below). Once the sword
     * jump is finished, the offset is added to his position to fix the discrepancy.
     */
    if (this->sSwordJumpState != 0) {
        Math_SmoothStepToF(&this->sSwordJumpHeight, 2630.0f, 1.0f, 2000.0f, 0.0f);
        this->actor.velocity.y -= 0.6f;
    } else if (this->sSwordJumpHeight != 0) {
        this->actor.world.pos.y += this->sSwordJumpHeight * 0.01f;
        this->sSwordJumpHeight = 0;
    }
    if ((this->sActionState == ENTORCH2_WAIT) || (this->invincibilityTimer < 0)) {
        this->sZTargetFlag = false;
    } else {
        this->sZTargetFlag = true;
    }
    if (this->sJumpslashTimer != 0) {
        this->sJumpslashTimer--;
    }
    this->actor.focus.pos = this->actor.world.pos;
    this->actor.focus.pos.y += 20.0f;
    this->actor.shape.yOffset = this->sSwordJumpHeight;
}

s32 EnTorch2_OverrideLimbDraw(PlayState* play, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot, void* thisx,
                              Gfx** gfx) {
    PlayerEnemy* this = (PlayerEnemy*)thisx;

    return Player_OverrideLimbDrawGameplayCommon(play, limbIndex, dList, pos, rot, &this->actor);
}

void EnTorch2_PostLimbDraw(PlayState* play, s32 limbIndex, Gfx** dList, Vec3s* rot, void* thisx, Gfx** gfx) {
    PlayerEnemy* this = (PlayerEnemy*)thisx;

    Player_PostLimbDrawGameplay(play, limbIndex, dList, rot, &this->actor);
}

void EnTorch2_Draw(Actor* thisx, PlayState* play2) {
    PlayState* play = play2;
    PlayerEnemy* this = (PlayerEnemy*)thisx;
    s32 pad;

    OPEN_DISPS(play->state.gfxCtx, "../z_en_torch2.c", 1050);
    func_80093C80(play);
    Gfx_SetupDL_25Xlu(play->state.gfxCtx);
    if (this->sAlpha == 255) {
        gDPSetEnvColor(POLY_OPA_DISP++, 255, 0, 0, this->sAlpha);
        gSPSegment(POLY_OPA_DISP++, 0x0C, D_80116280 + 2);
        func_8002EBCC(&this->actor, play, 0);
        func_8002ED80(&this->actor, play, 0);
        POLY_OPA_DISP =
            SkelAnime_DrawFlex(play, this->skelAnime.skeleton, this->skelAnime.jointTable, this->skelAnime.dListCount,
                               EnTorch2_OverrideLimbDraw, EnTorch2_PostLimbDraw, this, POLY_OPA_DISP);
    } else {
        gDPSetEnvColor(POLY_XLU_DISP++, 255, 0, 0, this->sAlpha);
        gSPSegment(POLY_XLU_DISP++, 0x0C, D_80116280);
        func_8002EBCC(&this->actor, play, 0);
        func_8002ED80(&this->actor, play, 0);
        POLY_XLU_DISP =
            SkelAnime_DrawFlex(play, this->skelAnime.skeleton, this->skelAnime.jointTable, this->skelAnime.dListCount,
                               EnTorch2_OverrideLimbDraw, EnTorch2_PostLimbDraw, this, POLY_XLU_DISP);
    }
    CLOSE_DISPS(play->state.gfxCtx, "../z_en_torch2.c", 1114);
}
