#include "z_en_fall.h"
#include "assets/objects/gameplay_keep/gameplay_keep.h"

#define FLAGS (ACTOR_FLAG_4 | ACTOR_FLAG_5 | ACTOR_FLAG_10 | ACTOR_FLAG_20)

void EnFall_Init(Actor* thisx, PlayState* play);
void EnFall_Destroy(Actor* thisx, PlayState* play);
void EnFall_Update(Actor* thisx, PlayState* play);
void EnFall_Draw(Actor* thisx, PlayState* play);

ActorInit En_Fall_InitVars = {
    ACTOR_EN_FALL,
    ACTORCAT_ITEMACTION,
    FLAGS,
    OBJECT_GAMEPLAY_KEEP,
    sizeof(EnFall),
    (ActorFunc)EnFall_Init,
    (ActorFunc)EnFall_Destroy,
    (ActorFunc)EnFall_Update,
    (ActorFunc)EnFall_Draw,
};

void EnFall_Init(Actor* thisx, PlayState* play) {
    EnFall* this = (EnFall*)thisx;
    Vec3f gInitVec = {0.0f, 4000.0f, 0.0f};
    this->actor.home.pos = gInitVec;
    thisx->shape.rot.y = 0.0f;
    this->scale = (0.576000);
    this->fallMultiplier = 1.0f;
    thisx->room = 0xFF;
    switch (play->sceneId) {
        case SCENE_GANONS_TOWER_COLLAPSE_EXTERIOR:
            thisx->home.pos.x = 0.0f;
            thisx->home.pos.y = 4500.0f;
            thisx->home.pos.z = 7500.0f;
            thisx->shape.rot.y = 0;
            this->scale = (0.576000f);
            this->fallMultiplier = 0.5f;
        case SCENE_ZORAS_FOUNTAIN:
            thisx->home.pos.x = -1600.0f;
            thisx->home.pos.y = 5700.0f;
            thisx->home.pos.z = 13100.0f;
            thisx->shape.rot.y = -26368;
            this->scale = (0.296000f);
            this->fallMultiplier = 1.0f;
            break;
        case SCENE_FISHING_POND:
            thisx->home.pos.x = -9100.0f;
            thisx->home.pos.y = 4000.0f;
            thisx->home.pos.z = 13100.0f;
            thisx->shape.rot.y = 27392;
            this->scale = (0.376000f);
            this->fallMultiplier = 1.0f;
            break;
        case SCENE_GANON_BOSS:
            thisx->home.pos.x = 0.0f;
            thisx->home.pos.y = 4500.0f;
            thisx->home.pos.z = 7500.0f;
            thisx->shape.rot.y = 0;
            this->scale = (0.576000f);
            this->fallMultiplier = 0.5f;
            break;
        case SCENE_HYRULE_FIELD:
            thisx->home.pos.x = -20.0f;
            thisx->home.pos.y = 4000.0f;
            thisx->home.pos.z = -1800.0f;
            thisx->shape.rot.y = 0.0f;
            this->scale = (0.576000f);
            this->fallMultiplier = 1.0f;
            break;
        case SCENE_KAKARIKO_VILLAGE:
            thisx->home.pos.x = -13400.0f;
            thisx->home.pos.y = 4000.0f;
            thisx->home.pos.z = -6200.0f;
            thisx->shape.rot.y = 0.0f;
            this->scale = (1.405999f);
            this->fallMultiplier = 3.099999f;
            break;
        case SCENE_GRAVEYARD:
            thisx->home.pos.x = -14600.0f;
            thisx->home.pos.y = 2000.0f;
            thisx->home.pos.z = -4600.0f;
            thisx->shape.rot.y = 0.0f;
            this->scale = (0.806000f);
            this->fallMultiplier = 1.5f;
            break;
        case SCENE_ZORAS_RIVER:
            thisx->home.pos.x = -9300.0f;
            thisx->home.pos.y = 2600.0f;
            thisx->home.pos.z = 14200.0f;
            thisx->shape.rot.y = 16384;
            this->scale = (0.766000f);
            this->fallMultiplier = 2.0f;
            break;
        case SCENE_KOKIRI_FOREST:
            thisx->home.pos.x = -20000.0f;
            thisx->home.pos.y = 4000.0f;
            thisx->home.pos.z = -2800.0f;
            thisx->shape.rot.y = 16384;
            this->scale = (0.596000f);
            this->fallMultiplier = 2.0f;
            break;
        case SCENE_SACRED_FOREST_MEADOW:
            thisx->home.pos.x = -5900.0f;
            thisx->home.pos.y = 4000.0f;
            thisx->home.pos.z = 14000.0f;
            thisx->shape.rot.y = 16384;
            this->scale = (0.336000f);
            this->fallMultiplier = 1.0f;
            break;
        case SCENE_LAKE_HYLIA:
            thisx->home.pos.x = -7300.0f;
            thisx->home.pos.y = 3000.0f;
            thisx->home.pos.z = -9100.0f;
            thisx->shape.rot.y = 7168;
            this->scale = (0.446000f);
            this->fallMultiplier = 1.5f;
            break;
        case SCENE_GERUDO_VALLEY:
            thisx->home.pos.x = 3900.0f;
            thisx->home.pos.y = 4000.0f;
            thisx->home.pos.z = -15500.0f;
            thisx->shape.rot.y = 10240;
            this->scale = (0.436000f);
            this->fallMultiplier = 2.5f;
            break;
        case SCENE_LOST_WOODS:
            thisx->home.pos.x = -16400.0f;
            thisx->home.pos.y = 4000.0f;
            thisx->home.pos.z = 5400.0f;
            thisx->shape.rot.y = 16384;
            this->scale = (0.676000f);
            this->fallMultiplier = 3.0f;
            break;
        case SCENE_DESERT_COLOSSUS:
            thisx->home.pos.x = 16000.0f;
            thisx->home.pos.y = 600.0f;
            thisx->home.pos.z = -500.0f;
            thisx->shape.rot.y = 9216;
            this->scale = (0.166000f);
            this->fallMultiplier = 1.0f;
            break;
        case SCENE_GERUDOS_FORTRESS:
            thisx->home.pos.x = -3900.0f;
            thisx->home.pos.y = 1400.0f;
            thisx->home.pos.z = 6100.0f;
            thisx->shape.rot.y = -14080;
            this->scale = (0.446000f);
            this->fallMultiplier = 2.3f;
            break;
        case SCENE_HAUNTED_WASTELAND:
            thisx->home.pos.x = -200.0f;
            thisx->home.pos.y = 1800.0f;
            thisx->home.pos.z = 13800.0f;
            thisx->shape.rot.y = -11008;
            this->scale = (0.286000f);
            this->fallMultiplier = 1.0f;
            break;
        case SCENE_HYRULE_CASTLE:
            thisx->home.pos.x = 0.0f;
            thisx->home.pos.y = 4500.0f;
            thisx->home.pos.z = 7500.0f;
            thisx->shape.rot.y = 0;
            this->scale = (0.576000f);
            this->fallMultiplier = 0.5f;
            break;
        case SCENE_DEATH_MOUNTAIN_TRAIL:
            thisx->home.pos.x = -15400.0f;
            thisx->home.pos.y = 0.0f;
            thisx->home.pos.z = 9200.0f;
            thisx->shape.rot.y = 0;
            this->scale = (1.006000f);
            this->fallMultiplier = 7.199996f;
            break;
        case SCENE_DEATH_MOUNTAIN_CRATER:
            thisx->home.pos.x = -10100.0f;
            thisx->home.pos.y = 3000.0f;
            thisx->home.pos.z = 700.0f;
            thisx->shape.rot.y = -6400;
            this->scale = (0.436000f);
            this->fallMultiplier = 3.699999f;
            break;
        case SCENE_LON_LON_RANCH:
            thisx->home.pos.x = -5000.0f;
            thisx->home.pos.y = 1000.0f;
            thisx->home.pos.z = -16200.0f;
            thisx->shape.rot.y = 13056;
            this->scale = (0.576000f);
            this->fallMultiplier = 1.6f;
            break;
        case SCENE_OUTSIDE_GANONS_CASTLE:
            thisx->home.pos.x = 0.0f;
            thisx->home.pos.y = 4500.0f;
            thisx->home.pos.z = 7500.0f;
            thisx->shape.rot.y = 0;
            this->scale = (0.576000f);
            this->fallMultiplier = 0.5f;
            break;
        default:
            Actor_Kill(thisx);
    }
    this->actor.world.pos = this->actor.home.pos;
}

void EnFall_Destroy(Actor* thisx, PlayState* play) {

}

void EnFall_Update(Actor* thisx, PlayState* play) {
    EnFall* this = (EnFall*)thisx;

    Actor_SetScale(&this->actor, this->scale);
    if (gSaveContext.finalHoursFlag == 0) {
        Actor_Kill(thisx);
    } else {
        f32 add;
        this->actor.world.pos = this->actor.home.pos;
        add = (((0x4000 - gSaveContext.finalHoursTimer) * 0.2f));
        add *= this->fallMultiplier;
        this->actor.world.pos.y += add;
    }
}

void EnFall_Debug(PlayState* this, EnFall* thisy) {
    GraphicsContext* gfxCtx = this->state.gfxCtx;
    Gfx* gfx;
    Gfx* opaStart;
    GfxPrint printer;

    OPEN_DISPS(gfxCtx, "../z_debug.c", 628);

    GfxPrint_Init(&printer);
    opaStart = POLY_OPA_DISP;
    gfx = Graph_GfxPlusOne(POLY_OPA_DISP);

    gSPDisplayList(OVERLAY_DISP++, gfx);

    GfxPrint_Open(&printer, gfx);
    
    GfxPrint_SetColor(&printer, 255, 155, 255, 255);
    GfxPrint_SetPos(&printer, 4, 8);
    GfxPrint_Printf(&printer, "x init pos: %f", thisy->actor.home.pos.x);
    GfxPrint_SetPos(&printer, 4, 9);
    GfxPrint_Printf(&printer, "y init pos: %f", thisy->actor.home.pos.y);
    GfxPrint_SetPos(&printer, 4, 10);
    GfxPrint_Printf(&printer, "z init pos: %f", thisy->actor.home.pos.z);
    GfxPrint_SetPos(&printer, 4, 11);
    GfxPrint_Printf(&printer, "y rot: %d", thisy->actor.shape.rot.y);
    GfxPrint_SetPos(&printer, 4, 12);
    GfxPrint_Printf(&printer, "scale: %f", thisy->scale);
    GfxPrint_SetPos(&printer, 4, 13);
    GfxPrint_Printf(&printer, "fall multiplier: %f", thisy->fallMultiplier);

    gfx = GfxPrint_Close(&printer);
    gSPEndDisplayList(gfx++);
    Graph_BranchDlist(opaStart, gfx);
    POLY_OPA_DISP = gfx;

    CLOSE_DISPS(gfxCtx, "../z_debug.c", 664);

    GfxPrint_Destroy(&printer);

    if (CHECK_BTN_ALL(this->state.input[1].cur.button, BTN_A)) {
        if (CHECK_BTN_ALL(this->state.input[1].cur.button, BTN_DUP)) {
            thisy->actor.home.pos.z += 1.0f;
        }
        if (CHECK_BTN_ALL(this->state.input[1].cur.button, BTN_DDOWN)) {
            thisy->actor.home.pos.z -= 1.0f;
        }
        if (CHECK_BTN_ALL(this->state.input[1].cur.button, BTN_DLEFT)) {
            thisy->actor.home.pos.x -= 1.0f;
        }
        if (CHECK_BTN_ALL(this->state.input[1].cur.button, BTN_DRIGHT)) {
            thisy->actor.home.pos.x += 1.0f;
        }
        if (CHECK_BTN_ALL(this->state.input[1].cur.button, BTN_CUP)) {
            thisy->actor.home.pos.y += 1.0f;
        }
        if (CHECK_BTN_ALL(this->state.input[1].cur.button, BTN_CDOWN)) {
            thisy->actor.home.pos.y -= 1.0f;
        }
    } else {
        if (CHECK_BTN_ALL(this->state.input[1].cur.button, BTN_DUP)) {
            thisy->actor.home.pos.z += 100.0f;
        }
        if (CHECK_BTN_ALL(this->state.input[1].cur.button, BTN_DDOWN)) {
            thisy->actor.home.pos.z -= 100.0f;
        }
        if (CHECK_BTN_ALL(this->state.input[1].cur.button, BTN_DLEFT)) {
            thisy->actor.home.pos.x -= 100.0f;
        }
        if (CHECK_BTN_ALL(this->state.input[1].cur.button, BTN_DRIGHT)) {
            thisy->actor.home.pos.x += 100.0f;
        }
        if (CHECK_BTN_ALL(this->state.input[1].cur.button, BTN_CUP)) {
            thisy->actor.home.pos.y += 100.0f;
        }
        if (CHECK_BTN_ALL(this->state.input[1].cur.button, BTN_CDOWN)) {
            thisy->actor.home.pos.y -= 100.0f;
        }
    }

    if (CHECK_BTN_ALL(this->state.input[1].cur.button, BTN_CLEFT)) {
        thisy->scale += 0.01f;
    }
    if (CHECK_BTN_ALL(this->state.input[1].cur.button, BTN_CRIGHT)) {
        thisy->scale -= 0.01f;
        if (thisy->scale <= 0.01f) {
            thisy->scale = 0.01f;
        }
    }

    if (CHECK_BTN_ALL(this->state.input[1].cur.button, BTN_L)) {
        thisy->actor.shape.rot.y += 0x100;
    }
    if (CHECK_BTN_ALL(this->state.input[1].cur.button, BTN_R)) {
        thisy->actor.shape.rot.y -= 0x100;
    }

    if (this->state.input[1].cur.stick_y > 0) {
        thisy->fallMultiplier += 0.1f;
    }
    if (this->state.input[1].cur.stick_y < 0) {
        thisy->fallMultiplier -= 0.1f;
        if (thisy->fallMultiplier <= 0.1f) {
            thisy->fallMultiplier = 0.1f;
        }
    }

    if (this->state.input[1].cur.stick_x < 0) {
        gSaveContext.finalHoursTimer += 0x100;
    }
    if (this->state.input[1].cur.stick_x > 0) {
        if (gSaveContext.finalHoursTimer - 0x100 >= 0) {
            gSaveContext.finalHoursTimer -= 0x100;
        } else {
            gSaveContext.finalHoursTimer = 0x0;
        }
    }

    if (gSaveContext.finalHoursTimer >= 0x4000) {
        gSaveContext.finalHoursTimer = 0x3FFF;
    }
}

void EnFall_Draw(Actor* thisx, PlayState* play) {
    static Vec3f sFocusOffset[] = { 1800.0f, 1000.0f, 4250.0f };
    EnFall* this = (EnFall*)thisx;
    Input* input;
    s32 primColor;

    OPEN_DISPS(play->state.gfxCtx, "../z_en_fall.c", 40);

    Gfx_SetupDL_25Opa(play->state.gfxCtx);
    Matrix_RotateZYX(sFocusOffset->z * 3.0f, 0, 0, MTXMODE_APPLY);
    gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(play->state.gfxCtx, "../z_en_fall.c", 43), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    Matrix_MultVec3f(sFocusOffset, &this->actor.focus.pos);

    primColor = (this->eyeGlowIntensity * 200.0f) + 40.0f;
    gDPSetPrimColor(POLY_OPA_DISP++, 0, 0x80, primColor, primColor, primColor, 255);

    gSPDisplayList(POLY_OPA_DISP++, gMoonMMDL);

    CLOSE_DISPS(play->state.gfxCtx, "../z_en_fall", 51);
}