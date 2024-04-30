#include "global.h"

#define DEBUG_CAM_CONTROLLER_PORT 2

static PlayState* sPlay;

// TODO: cleanup these arrays and UB access
char* D_8012CEE0[] = { GFXP_KATAKANA "ｷ-ﾌﾚ-ﾑ" GFXP_HIRAGANA "ｶﾞ" };
char* D_8012CEE4 = GFXP_HIRAGANA "ﾀﾘﾏｾﾝ｡";
char* D_8012CEE8 = GFXP_HIRAGANA "ｻｲｾｲﾃﾞｷﾏｾﾝ";
char* D_8012CEEC = GFXP_HIRAGANA "ｻｲｾｲｼｭｳﾘｮｳ";
char* D_8012CEF0 = GFXP_HIRAGANA "ｻｲｾｲﾁｭｳ!";

char* D_8012CEF4 = "DEMO CAMERA TOOL";
char* D_8012CEF8[] = { GFXP_HIRAGANA "ﾓｳﾊｲﾘﾏｾﾝ", GFXP_HIRAGANA "ﾄｳﾛｸ   ﾃﾝﾒ", GFXP_HIRAGANA "ﾍﾝｺｳ   /  " };
char* D_8012CF04 = ">            >";
char* D_8012CF08 = "<            <";
char* D_8012CF0C = "<          >";
char* D_8012CF10 = GFXP_KATAKANA "*ﾌﾟﾚｲﾔ-*";
char* D_8012CF14 = GFXP_KATAKANA "Eﾓ-ﾄﾞ" GFXP_HIRAGANA " ｿｳﾀｲ";
char* D_8012CF18[] = { GFXP_KATAKANA "Eﾓ-ﾄﾞ" GFXP_HIRAGANA "ｾﾞｯﾀｲ", GFXP_HIRAGANA "ｶﾞﾒﾝ" GFXP_KATAKANA "   ﾃﾞﾓ",
                       GFXP_HIRAGANA "ｶﾞﾒﾝ   ﾌﾂｳ" };
char* D_8012CF24[] = { GFXP_HIRAGANA "Pｼﾞｶﾝ  MAX", GFXP_KATAKANA "ﾘﾝｸ" GFXP_HIRAGANA "    ｷｵｸ",
                       GFXP_KATAKANA "ﾘﾝｸ" GFXP_HIRAGANA "     ﾑｼ" };
char* D_8012CF30 = GFXP_HIRAGANA "*ﾐﾃﾙｲﾁ*";
char* D_8012CF34 = GFXP_KATAKANA "*ｶﾒﾗ" GFXP_HIRAGANA "ｲﾁ*";
char* D_8012CF38 = "DEBUG CAMERA";
char* D_8012CF3C = GFXP_KATAKANA "ｾﾝﾀ-/ﾛｯｸ";
char* D_8012CF40 = GFXP_KATAKANA "ｾﾝﾀ-/ﾌﾘ-";

char* D_8012CF44 = "DEMO CONTROL";
char* D_8012CF48 = GFXP_KATAKANA "ﾒﾓﾘ" GFXP_HIRAGANA "ｶﾞﾀﾘﾏｾﾝ";
char* D_8012CF4C = "p";
char* D_8012CF50[] = { "e", "s", "l", "c" };

char* D_8012CF60[] = { GFXP_KATAKANA "ﾒﾓﾘﾊﾟｯｸ" }; // "Mempak"
char* D_8012CF64 = GFXP_KATAKANA "ｾｰﾌﾞ";          // "Save"
char* D_8012CF68 = GFXP_KATAKANA "ﾛｰﾄﾞ";          // "Load"
char* D_8012CF6C = GFXP_KATAKANA "ｸﾘｱ-";          // "Clear"
char* D_8012CF70 = GFXP_HIRAGANA "ｦﾇｶﾅｲﾃﾞﾈ";

char* D_8012CF74 = "FREE      BYTE";
char* D_8012CF78 = "NEED      BYTE";
char* D_8012CF7C = GFXP_KATAKANA "*ﾒﾓﾘ-ﾊﾟｯｸ*";
char* D_8012CF80 = GFXP_HIRAGANA "ｦﾐﾂｹﾗﾚﾏｾﾝ";
char* D_8012CF84 = GFXP_KATAKANA "ﾌｧｲﾙ " GFXP_HIRAGANA "ｦ";
char* D_8012CF88[] = { GFXP_HIRAGANA "ｼﾃﾓｲｲﾃﾞｽｶ?", GFXP_HIRAGANA "ｹﾞﾝｻﾞｲﾍﾝｼｭｳﾁｭｳﾉ",
                       GFXP_KATAKANA "ﾌｧｲﾙ" GFXP_HIRAGANA "ﾊﾊｷｻﾚﾏｽ" };
char* D_8012CF94 = GFXP_HIRAGANA "ﾊｲ";
char* D_8012CF98 = GFXP_HIRAGANA "ｲｲｴ";
char* D_8012CF9C[] = { GFXP_HIRAGANA "ｼﾃｲﾏｽ", GFXP_HIRAGANA "ｳﾜｶﾞｷ" };
char* D_8012CFA4 = GFXP_HIRAGANA "ｼﾏｼﾀ";
char* D_8012CFA8 = "USE       BYTE";
char* D_8012CFAC = GFXP_HIRAGANA "ﾆｼｯﾊﾟｲ";

char* D_8012CFB0 = GFXP_KATAKANA "Eﾓ-ﾄﾞ" GFXP_HIRAGANA "  ｺﾃｲ";
char D_8012CFB4[] = GFXP_KATAKANA "ﾌﾚ-ﾑ       ";
char D_8012CFC4[] = GFXP_KATAKANA "ｷ-   /   ";
char D_8012CFD0[] = GFXP_HIRAGANA "(ｾﾝﾀ-ﾃﾝ)\0\0\0\0\0";
char D_8012CFE4[] = GFXP_HIRAGANA "(ｹﾞﾝﾃﾝ)\0\0\0\0\0\0";
char D_8012CFF8[] = GFXP_KATAKANA "(ﾌﾟﾚｲﾔ-)\0\0\0\0\0";
char D_8012D00C[] = GFXP_HIRAGANA "(ｲﾁｱﾜｾ)\0\0\0\0\0\0";
char D_8012D020[] = GFXP_HIRAGANA "(ｾｯﾃｲ)\0\0\0\0\0\0\0\0";
char D_8012D034[] = GFXP_HIRAGANA "(ｷｬｯｶﾝ)\0\0\0\0\0\0";
char D_8012D048[] = GFXP_KATAKANA "ﾎﾟｲﾝﾄNo.  \0\0\0";
char D_8012D05C[] = GFXP_HIRAGANA "ｶﾞｶｸ    \0\0\0";
char D_8012D070[] = GFXP_KATAKANA "Nﾌﾚ-ﾑ   \0\0\0\0";
char D_8012D084[] = GFXP_HIRAGANA "Zｶｲﾃﾝ   \0\0\0";
char D_8012D098[] = GFXP_KATAKANA "ﾓ-ﾄﾞ    \0\0\0\0";
char D_8012D0AC[] = "  R" GFXP_HIRAGANA "ﾁｭｳｼﾝ  \0\0\0";

char D_8012D0C0[] = GFXP_HIRAGANA "Pｼﾞｶﾝ       \0\0";
char D_8012D0D4[] = GFXP_HIRAGANA "ｷｮﾘ       \0";
char D_8012D0E4[] = GFXP_HIRAGANA "Xｶｲﾃﾝ       \0\0";
char D_8012D0F8[] = GFXP_HIRAGANA "Yｶｲﾃﾝ       \0\0";

#define ACTION_E 0
#define ACTION_SAVE 1
#define ACTION_LOAD 2
#define ACTION_CLEAR 3

#define MENU_INFO 0
#define MENU_CALLBACK 1
#define MENU_SUCCESS 2
#define MENU_ERROR 9

#define DEMO_CTRL_MENU(actionIdx, menuIdx) (actionIdx * 100 + menuIdx)

s32 DebugCamera_SaveCallback(char* c);
s32 DebugCamera_LoadCallback(char* c);
s32 DebugCamera_ClearCallback(char* c);
s32 DebugCamera_UpdateDemoControl(DebugCam* debugCam, Camera* cam);

static DebugCam* sDebugCamPtr;
static s16 D_8016110C;
static DebugCamAnim sDebugCamAnim;

Vec3f* DebugCamera_AddVecGeoToVec3f(Vec3f* dest, Vec3f* a, VecGeo* geo) {
    Vec3f sum;
    Vec3f b;

    OLib_VecGeoToVec3f(&b, geo);

    sum.x = a->x + b.x;
    sum.y = a->y + b.y;
    sum.z = a->z + b.z;

    *dest = sum;

    return dest;
}

/**
 * Calculates a new Up vector from the pitch, yaw, roll
 */
Vec3f* DebugCamera_CalcUpFromPitchYawRoll(Vec3f* viewUp, s16 pitch, s16 yaw, s16 roll) {
    f32 sinP = Math_SinS(pitch);
    f32 cosP = Math_CosS(pitch);
    f32 sinY = Math_SinS(yaw);
    f32 cosY = Math_CosS(yaw);
    f32 sinR = Math_SinS(-roll);
    f32 cosR = Math_CosS(-roll);
    Vec3f up;
    Vec3f baseUp;
    Vec3f u;
    Vec3f rollMtxRow1;
    Vec3f rollMtxRow2;
    Vec3f rollMtxRow3;

    // Axis to roll around
    u.x = cosP * sinY;
    u.y = sinP;
    u.z = cosP * cosY;

    // Up without roll
    baseUp.x = -sinP * sinY;
    baseUp.y = cosP;
    baseUp.z = -sinP * cosY;

    // Matrix to apply the roll to the Up vector without roll
    rollMtxRow1.x = ((1.0f - SQ(u.x)) * cosR) + SQ(u.x);
    rollMtxRow1.y = ((1.0f - cosR) * (u.x * u.y)) - (u.z * sinR);
    rollMtxRow1.z = ((1.0f - cosR) * (u.z * u.x)) + (u.y * sinR);

    rollMtxRow2.x = ((1.0f - cosR) * (u.x * u.y)) + (u.z * sinR);
    rollMtxRow2.y = ((1.0f - SQ(u.y)) * cosR) + SQ(u.y);
    rollMtxRow2.z = ((1.0f - cosR) * (u.y * u.z)) - (u.x * sinR);

    rollMtxRow3.x = ((1.0f - cosR) * (u.z * u.x)) - (u.y * sinR);
    rollMtxRow3.y = ((1.0f - cosR) * (u.y * u.z)) + (u.x * sinR);
    rollMtxRow3.z = ((1.0f - SQ(u.z)) * cosR) + SQ(u.z);

    // rollMtx * baseUp
    up.x = DOTXYZ(baseUp, rollMtxRow1);
    up.y = DOTXYZ(baseUp, rollMtxRow2);
    up.z = DOTXYZ(baseUp, rollMtxRow3);

    *viewUp = up;

    return viewUp;
}

char* DebugCamera_SetTextValue(s16 value, char* str, u8 endIdx) {
    char* strIter;
    char sign;

    strIter = str + (s32)endIdx - 1;
    str[endIdx] = '\0';

    if (value >= 0) {
        sign = ' ';
    } else {
        sign = '-';
        value = -value;
    }

    do {

        // clang-format off
        *strIter-- = (value % 10) + '0'; value /= 10;
        // clang-format on

    } while (value != 0);

    if (sign == '-') {
        *strIter-- = sign;
    }

    while (strIter >= str) {
        *str++ = ' ';
    }

    return strIter;
}

void DebugCamera_Vec3SToF(Vec3s* in, Vec3f* out) {
    out->x = in->x;
    out->y = in->y;
    out->z = in->z;
}

void DebugCamera_Vec3FToS(Vec3f* in, Vec3s* out) {
    out->x = in->x;
    out->y = in->y;
    out->z = in->z;
}

void DebugCamera_CopyVec3f(Vec3f* in, Vec3f* out) {
    out->x = in->x;
    out->y = in->y;
    out->z = in->z;
}

void DebugCamera_Vec3SToF2(Vec3s* in, Vec3f* out) {
    out->x = in->x;
    out->y = in->y;
    out->z = in->z;
}

void func_800B3F94(PosRot* posRot, Vec3f* vec, Vec3s* out) {
    VecGeo geo;
    Vec3f tempVec;

    OLib_Vec3fDiffToVecGeo(&geo, &posRot->pos, vec);
    geo.yaw -= posRot->rot.y;
    OLib_VecGeoToVec3f(&tempVec, &geo);
    DebugCamera_Vec3FToS(&tempVec, out);
}

void func_800B3FF4(PosRot* posRot, Vec3f* vec, Vec3f* out) {
    VecGeo geo;
    Vec3f tempVec;

    DebugCamera_CopyVec3f(vec, &tempVec);
    OLib_Vec3fToVecGeo(&geo, &tempVec);
    geo.yaw += posRot->rot.y;
    DebugCamera_AddVecGeoToVec3f(out, &posRot->pos, &geo);
}

void func_800B404C(PosRot* posRot, Vec3s* vec, Vec3f* out) {
    Vec3f tempVec;

    DebugCamera_Vec3SToF(vec, &tempVec);
    func_800B3FF4(posRot, &tempVec, out);
}

s32 func_800B4088(DebugCam* debugCam, Camera* cam) {
    CutsceneCameraPoint* position;
    CutsceneCameraPoint* lookAt;
    s32 i;

    position = &debugCam->sub.position[debugCam->sub.unkIdx];
    lookAt = &debugCam->sub.lookAt[debugCam->sub.unkIdx];

    position->continueFlag = CS_CAM_STOP;
    lookAt->continueFlag = position->continueFlag;
    position->nextPointFrame = 0;
    lookAt->nextPointFrame = 30;
    lookAt->cameraRoll = position->cameraRoll = debugCam->roll * (360.0f / 256.0f);
    lookAt->viewAngle = position->viewAngle = debugCam->fov;

    if (debugCam->sub.mode != 1) {
        DebugCamera_Vec3FToS(&debugCam->eye, &position->pos);
        DebugCamera_Vec3FToS(&debugCam->at, &lookAt->pos);
    } else {
        func_800B3F94(&cam->playerPosRot, &debugCam->at, &lookAt->pos);
        func_800B3F94(&cam->playerPosRot, &debugCam->eye, &position->pos);
    }

    for (i = 0; i < (debugCam->sub.nPoints - 2); i++) {
        debugCam->sub.position[i].continueFlag = debugCam->sub.lookAt[i].continueFlag = CS_CAM_CONTINUE;
    }

    debugCam->sub.position[i].continueFlag = debugCam->sub.lookAt[i].continueFlag = CS_CAM_STOP;

    return debugCam->sub.unkIdx;
}

s16 func_800B41DC(DebugCam* debugCam, s16 idx, Camera* cameraPtr) {
    CutsceneCameraPoint* position = &debugCam->sub.position[idx];
    CutsceneCameraPoint* lookAt = &debugCam->sub.lookAt[idx];

    if (debugCam->sub.mode != 1) {
        DebugCamera_Vec3SToF2(&position->pos, &debugCam->eye);
        DebugCamera_Vec3SToF2(&lookAt->pos, &debugCam->at);
    } else {
        func_800B404C(&cameraPtr->playerPosRot, &lookAt->pos, &debugCam->at);
        func_800B404C(&cameraPtr->playerPosRot, &position->pos, &debugCam->eye);
    }

    debugCam->roll = lookAt->cameraRoll;
    debugCam->rollDegrees = debugCam->roll * (360.0f / 256.0f);
    debugCam->fov = lookAt->viewAngle;
    return idx;
}

s32 func_800B42C0(DebugCam* debugCam, Camera* cameraPtr) {

    CutsceneCameraPoint* position = &debugCam->sub.position[debugCam->sub.unkIdx];
    CutsceneCameraPoint* lookAt = &debugCam->sub.lookAt[debugCam->sub.unkIdx];

    position->continueFlag = lookAt->continueFlag = CS_CAM_CONTINUE;

    if (debugCam->sub.mode != 1) {
        DebugCamera_Vec3FToS(&debugCam->eye, &position->pos);
        DebugCamera_Vec3FToS(&debugCam->at, &lookAt->pos);
    } else {
        func_800B3F94(&cameraPtr->playerPosRot, &debugCam->at, &lookAt->pos);
        func_800B3F94(&cameraPtr->playerPosRot, &debugCam->eye, &position->pos);
    }

    return debugCam->sub.unkIdx;
}

s32 func_800B4370(DebugCam* debugCam, s16 idx, Camera* cam) {
    CutsceneCameraPoint* lookAt = &debugCam->sub.lookAt[idx];
    CutsceneCameraPoint* position = &debugCam->sub.position[idx];
    VecGeo geo;
    Vec3f at;

    if (debugCam->sub.mode != 1) {
        if (debugCam->sub.unk_0C) {
            DebugCamera_Vec3SToF2(&position->pos, &debugCam->at);
        } else {
            DebugCamera_Vec3SToF2(&lookAt->pos, &debugCam->at);
        }
    } else {
        if (debugCam->sub.unk_0C) {
            func_800B404C(&cam->playerPosRot, &position->pos, &at);
        } else {
            func_800B404C(&cam->playerPosRot, &lookAt->pos, &at);
        }
        debugCam->at = at;
    }
    geo.pitch = 0x2000;
    geo.yaw -= 0x7FFF;
    geo.r = 250.0f;
    DebugCamera_AddVecGeoToVec3f(&debugCam->eye, &debugCam->at, &geo);
    debugCam->roll = lookAt->cameraRoll;
    debugCam->rollDegrees = debugCam->roll * (360.0f / 256.0f);
    debugCam->fov = lookAt->viewAngle;
    return idx;
}

void func_800B44E0(DebugCam* debugCam, Camera* cam) {
    s32 i;

    if (CHECK_BTN_ALL(sPlay->state.input[DEBUG_CAM_CONTROLLER_PORT].press.button, BTN_CRIGHT)) {
        sDebugCamAnim.keyframe = 0;
        sDebugCamAnim.unk_0A = 1;
        sDebugCamAnim.curFrame = 0.0f;
        sDebugCamAnim.unk_04 = 0;

        for (i = 0; i < (debugCam->sub.nPoints - 2); i++) {
            debugCam->sub.position[i].continueFlag = debugCam->sub.lookAt[i].continueFlag = CS_CAM_CONTINUE;
        }

        debugCam->sub.position[i].continueFlag = debugCam->sub.lookAt[i].continueFlag = CS_CAM_STOP;
    }

    if (debugCam->sub.nPoints < 6) {
        if (sDebugCamAnim.unk_0A != 0) {
            Audio_PlaySfxGeneral(NA_SE_SY_ERROR, &gSfxDefaultPos, 4, &gSfxDefaultFreqAndVolScale,
                                 &gSfxDefaultFreqAndVolScale, &gSfxDefaultReverb);
            sDebugCamAnim.unk_0A = 0;
        }
        DebugCamera_ScreenTextColored(17, 23, DEBUG_CAM_TEXT_ORANGE, D_8012CEE0[0]);
        DebugCamera_ScreenTextColored(18, 24, DEBUG_CAM_TEXT_ORANGE, D_8012CEE4);
        DebugCamera_ScreenTextColored(16, 26, DEBUG_CAM_TEXT_PEACH, D_8012CEE8);
        return;
    }

    if (!func_800BB2B4(&sDebugCamAnim.positionPos, &sDebugCamAnim.roll, &sDebugCamAnim.fov, debugCam->sub.position,
                       &sDebugCamAnim.keyframe, &sDebugCamAnim.curFrame) &&
        !func_800BB2B4(&sDebugCamAnim.lookAtPos, &sDebugCamAnim.roll, &sDebugCamAnim.fov, debugCam->sub.lookAt,
                       &sDebugCamAnim.keyframe, &sDebugCamAnim.curFrame) &&
        sDebugCamAnim.unk_0A == 1) {
        Audio_PlaySfxGeneral(NA_SE_SY_HP_RECOVER, &gSfxDefaultPos, 4, &gSfxDefaultFreqAndVolScale,
                             &gSfxDefaultFreqAndVolScale, &gSfxDefaultReverb);
        sDebugCamAnim.unk_04++;

        if (debugCam->sub.nFrames > 0 && debugCam->sub.nFrames < sDebugCamAnim.unk_04) {
            sDebugCamAnim.unk_0A = 0;
            DebugCamera_ScreenTextColored(15, 26, DEBUG_CAM_TEXT_PEACH, D_8012CEEC);
        }

        if (debugCam->sub.mode != 1) {
            DebugCamera_CopyVec3f(&sDebugCamAnim.positionPos, &debugCam->eye);
            DebugCamera_CopyVec3f(&sDebugCamAnim.lookAtPos, &debugCam->at);
        } else {
            func_800B3FF4(&cam->playerPosRot, &sDebugCamAnim.lookAtPos, &debugCam->at);
            func_800B3FF4(&cam->playerPosRot, &sDebugCamAnim.positionPos, &debugCam->eye);
        }

        debugCam->fov = sDebugCamAnim.fov;
        debugCam->roll = sDebugCamAnim.roll;
        debugCam->rollDegrees = sDebugCamAnim.roll * (360.0f / 256.0f);

        DebugCamera_SetTextValue(sDebugCamAnim.unk_04, &D_8012CFB4[8], 4);
        DebugCamera_ScreenTextColored(16, 23, DEBUG_CAM_TEXT_ORANGE, D_8012CFB4);
        D_8012CFC4[5] = ((sDebugCamAnim.keyframe + 1) / 10) + '0';
        D_8012CFC4[6] = ((sDebugCamAnim.keyframe + 1) % 10) + '0';
        D_8012CFC4[8] = ((debugCam->sub.nPoints - 5) / 10) + '0';
        D_8012CFC4[9] = ((debugCam->sub.nPoints - 5) % 10) + '0';
        DebugCamera_ScreenTextColored(16, 24, DEBUG_CAM_TEXT_ORANGE, D_8012CFC4);
        DebugCamera_ScreenTextColored(16, 26, DEBUG_CAM_TEXT_PEACH, D_8012CEF0);
        return;
    }

    sDebugCamAnim.unk_0A = 0;
    DebugCamera_ScreenTextColored(15, 26, DEBUG_CAM_TEXT_PEACH, D_8012CEEC);
}

void DebugCamera_PrintPoints(const char* name, s16 count, CutsceneCameraPoint* points) {
    s32 i;

    osSyncPrintf("@@@static SplinedatZ  %s[] = {\n", name);
    for (i = 0; i < count; i++) {
        osSyncPrintf("@@@    /* key frame %2d */ {\n", i);
        osSyncPrintf("@@@    /*     code     */ %d,\n", points[i].continueFlag);
        osSyncPrintf("@@@    /*     z        */ %d,\n", points[i].cameraRoll);
        osSyncPrintf("@@@    /*     T        */ %d,\n", points[i].nextPointFrame);
        osSyncPrintf("@@@    /*     zoom     */ %f,\n", points[i].viewAngle);
        osSyncPrintf("@@@    /*     pos      */ { %d, %d, %d }\n", points[i].pos.x, points[i].pos.y, points[i].pos.z);
        osSyncPrintf("@@@    },\n");
    }
    osSyncPrintf("@@@};\n@@@\n");
}

void DebugCamera_PrintF32Bytes(f32 value) {
    f32 b = value;
    char* a = (char*)&b;

    osSyncPrintf("\n@@@%d,%d,%d,%d,", a[0], a[1], a[2], a[3]);
}

void DebugCamera_PrintU16Bytes(u16 value) {
    u16 pad;
    u16 b = value;
    char* a = (char*)&b;

    osSyncPrintf("\n@@@%d,%d,", a[0], a[1]);
}

void DebugCamera_PrintS16Bytes(s16 value) {
    u16 pad;
    s16 b = value;
    char* a = (char*)&b;

    osSyncPrintf("\n@@@%d,%d,", a[0], a[1]);
}

void DebugCamera_PrintCutBytes(DebugCamCut* cut) {
    CutsceneCameraPoint* point;
    CutsceneCameraPoint* points;
    s32 i;

    points = cut->lookAt;
    osSyncPrintf("\n@@@ 0,0,0,2,\t/* Look Camera\t*/");
    osSyncPrintf("\n@@@ 0,1,\t/* dousa\t*/");

    osSyncPrintf("\n@@@ 0,0,\t/* Start Flame\t*/");
    DebugCamera_PrintU16Bytes(cut->nFrames);
    osSyncPrintf("\t/*  End   Flame\t*/");

    osSyncPrintf("\n@@@0,0,\t/*  Dammy\t*/\n@@@ ");
    for (i = 0; i < cut->nPoints; i++) {
        point = points + i;
        osSyncPrintf("\n@@@    %d, /*     code     */", point->continueFlag);
        osSyncPrintf("\n@@@    %d,  /*     z        */", point->cameraRoll);
        DebugCamera_PrintU16Bytes(point->nextPointFrame);
        osSyncPrintf("\t/*  sokudo\t*/");
        DebugCamera_PrintF32Bytes(point->viewAngle);
        osSyncPrintf("\t/*  zoom\t*/");
        DebugCamera_PrintS16Bytes(point->pos.x);
        osSyncPrintf("\t/*  x pos\t*/");
        DebugCamera_PrintS16Bytes(point->pos.y);
        osSyncPrintf("\t/*  y pos\t*/");
        DebugCamera_PrintS16Bytes(point->pos.z);
        osSyncPrintf("\t/*  z pos\t*/\n");
        osSyncPrintf("\n@@@0,0,\t/*  Dammy\t*/\n@@@ ");
    }

    points = cut->position;
    osSyncPrintf("\n@@@ 0,0,0,1,\t/* Position Camera */");
    osSyncPrintf("\n@@@ 0,1,\t/* dousa\t*/");

    osSyncPrintf("\n@@@ 0,0,\t/* Start Flame\t*/");
    DebugCamera_PrintU16Bytes(cut->nFrames);
    osSyncPrintf("\t/*  End   Flame\t*/");

    osSyncPrintf("\n@@@0,0,\t/*  Dammy\t*/\n@@@ ");
    for (i = 0; i < cut->nPoints; i++) {
        point = points + i;
        osSyncPrintf("\n@@@    %d, /*     code     */", point->continueFlag);
        osSyncPrintf("\n@@@    %d, /*     z        */", point->cameraRoll);
        DebugCamera_PrintU16Bytes(point->nextPointFrame);
        osSyncPrintf("\t/*  sokudo\t*/");
        DebugCamera_PrintF32Bytes(point->viewAngle);
        osSyncPrintf("\t/*  zoom\t*/");
        DebugCamera_PrintS16Bytes(point->pos.x);
        osSyncPrintf("\t/*  x pos\t*/");
        DebugCamera_PrintS16Bytes(point->pos.y);
        osSyncPrintf("\t/*  y pos\t*/");
        DebugCamera_PrintS16Bytes(point->pos.z);
        osSyncPrintf("\t/*  z pos\t*/");
        osSyncPrintf("\n@@@0,0,\t/*  Dammy\t*/\n@@@ ");
    }
}

void DebugCamera_Init(DebugCam* debugCam, Camera* cameraPtr) {
    debugCam->sub.unk_104A.z = 0;
    debugCam->unk_44 = 0;
    debugCam->unk_00 = 0;
    debugCam->unk_34 = 0;
    debugCam->unk_3C = false;
    debugCam->unk_38 = -1;
    debugCam->unk_40 = -1;
    debugCam->roll = 0;
    debugCam->sub.unk_104A.y = debugCam->sub.unk_104A.z;
    debugCam->sub.unk_104A.x = debugCam->sub.unk_104A.z;
    debugCam->fov = 0.0f;
    debugCam->rollDegrees = 0.0f;
    sPlay = cameraPtr->play;
    debugCam->sub.mode = 0;
    debugCam->sub.nFrames = -1;
    debugCam->sub.nPoints = 1;
    debugCam->sub.unkIdx = 0;
    debugCam->sub.unk_08 = 0;
    debugCam->sub.unk_0A = 0;
    debugCam->unk_78 = 0;
    debugCam->unk_7A = 0;
    debugCam->sub.demoCtrlMenu = DEMO_CTRL_MENU(ACTION_E, MENU_INFO);
    debugCam->sub.demoCtrlActionIdx = ACTION_E;
    debugCam->sub.demoCtrlToggleSwitch = 0;
    debugCam->unk_6C.x = 0;
    debugCam->unk_6C.y = 0;
    debugCam->unk_6C.z = 0;
}

void DebugCamera_Enable(DebugCam* debugCam, Camera* cam) {
    debugCam->at = cam->at;
    debugCam->eye = cam->eye;
    debugCam->unk_1C = cam->up;
    debugCam->fov = cam->fov;
    debugCam->roll = 0;
    debugCam->sub.nPoints = 1;
    debugCam->sub.unkIdx = 0;
    debugCam->sub.unk_08 = 0;
    debugCam->sub.unk_0A = 1;
    debugCam->sub.unk_0C = true;
    debugCam->unk_78 = 0;
    debugCam->unk_7A = 0;
    debugCam->rollDegrees = 0.0f;
    func_800B4088(debugCam, cam);
}

void DebugCamera_Update(DebugCam* debugCam, Camera* cam) {
    
}

static s16 sCurFileIdx;
static s16 sLastFileIdx; // holds the file index of the slot to move
// is the size correct? todo: add ALIGN32 for sizeof in Mempak functions, replace 0xF with sizeof()
static DebugCamCut sDebugCamCuts[16];
static char D_80161250[0x80];
static char sLetters[26];
static char D_801612EA;
static s32 sAllocSize;

s32 DebugCamera_GetFirstAvailableLetter(void) {
    s32 i;

    for (i = 0; i < ARRAY_COUNT(sLetters); i++) {
        switch (sLetters[i]) {
            case 'O':
                break;
            default:
                return MEMPAK_INDEX_TO_LETTER(i);
        }
    }
    return '?';
}

char DebugCamera_InitCut(s32 idx, DebugCamSub* sub) {
    s32 i;

    sDebugCamCuts[idx].unk_01 = 0x61;
    sDebugCamCuts[idx].letter = DebugCamera_GetFirstAvailableLetter();
    D_80161250[0x3F + sDebugCamCuts[idx].letter] = 'O';

    i = sub->nPoints * sizeof(CutsceneCameraPoint);
    sDebugCamCuts[idx].lookAt = DebugArena_MallocDebug(i, "../db_camera.c", 2748);
    if (sDebugCamCuts[idx].lookAt == NULL) {
        // "Debug camera memory allocation failure"
        osSyncPrintf("%s: %d: デバッグカメラ メモリ確保失敗！！\n", "../db_camera.c", 2751);
        return '?';
    }

    sDebugCamCuts[idx].position = DebugArena_MallocDebug(i, "../db_camera.c", 2754);
    if (sDebugCamCuts[idx].position == NULL) {
        // "Debug camera memory allocation failure"
        osSyncPrintf("%s: %d: デバッグカメラ メモリ確保失敗！！\n", "../db_camera.c", 2757);
        DebugArena_FreeDebug(sDebugCamCuts[idx].lookAt, "../db_camera.c", 2758);
        sDebugCamCuts[idx].lookAt = NULL;
        return '?';
    }

    sDebugCamCuts[idx].mode = sub->mode;
    sDebugCamCuts[idx].nFrames = sub->nFrames;
    sDebugCamCuts[idx].nPoints = sub->nPoints;

    for (i = 0; i < sub->nPoints; i++) {
        sDebugCamCuts[idx].lookAt[i] = sub->lookAt[i];
        sDebugCamCuts[idx].position[i] = sub->position[i];
    }

    return sDebugCamCuts[idx].letter;
}

void DebugCamera_ResetCut(s32 idx, s32 shouldFree) {
    if (sDebugCamCuts[idx].letter != '?') {
        D_80161250[0x3F + sDebugCamCuts[idx].letter] = 'X';
    }

    if (shouldFree) {
        DebugArena_FreeDebug(sDebugCamCuts[idx].lookAt, "../db_camera.c", 2784);
        DebugArena_FreeDebug(sDebugCamCuts[idx].position, "../db_camera.c", 2785);
    }

    sDebugCamCuts[idx].letter = '?';
    sDebugCamCuts[idx].lookAt = NULL;
    sDebugCamCuts[idx].position = NULL;
    sDebugCamCuts[idx].mode = 0;
    sDebugCamCuts[idx].nFrames = 0;
    sDebugCamCuts[idx].nPoints = 0;
}

s32 DebugCamera_CalcMempakAllocSize(void) {
    s32 i;

    sAllocSize = 0;
    for (i = 0; i < ARRAY_COUNT(sDebugCamCuts) - 1; i++) {
        if (sDebugCamCuts[i].letter != '?') {
            sAllocSize += ALIGN32(sDebugCamCuts[i].nPoints * sizeof(CutsceneCameraPoint)) * 2;
        }
    }
    sAllocSize += 0x100;
    sAllocSize = ALIGN256(sAllocSize);
    return sAllocSize;
}

s32 DebugCamera_GetMempakAllocSize(void) {
    return sAllocSize;
}

s32 DebugCamera_LoadCallback(char* c) {
    s32 i;
    s32 size;
    s32 off;

    for (i = 0; i < ARRAY_COUNT(sDebugCamCuts) - 1; i++) {
        if (sDebugCamCuts[i].letter != '?') {
            DebugCamera_ResetCut(i, true);
            sLetters[i] = 'X';
        }
    }

    if (!Mempak_Read(DEBUG_CAM_CONTROLLER_PORT, *c, sDebugCamCuts, 0, sizeof(sDebugCamCuts))) {
        return false;
    }

    off = sizeof(sDebugCamCuts);
    for (i = 0; i < ARRAY_COUNT(sDebugCamCuts) - 1; i++) {
        if (sDebugCamCuts[i].letter != '?') {
            size = sDebugCamCuts[i].nPoints * sizeof(CutsceneCameraPoint);

            sDebugCamCuts[i].lookAt = DebugArena_MallocDebug(ALIGN32(size), "../db_camera.c", 2844);
            if (sDebugCamCuts[i].lookAt == NULL) {
                // "Debug camera memory allocation failure"
                osSyncPrintf("%s: %d: デバッグカメラ メモリ確保失敗！！\n", "../db_camera.c", 2847);
                return false;
            }
            if (!Mempak_Read(DEBUG_CAM_CONTROLLER_PORT, *c, sDebugCamCuts[i].lookAt, off, ALIGN32(size))) {
                return false;
            }
            off += ALIGN32(size);

            sDebugCamCuts[i].position = DebugArena_MallocDebug(ALIGN32(size), "../db_camera.c", 2855);
            if (sDebugCamCuts[i].position == NULL) {
                // "Debug camera memory allocation failure"
                osSyncPrintf("%s: %d: デバッグカメラ メモリ確保失敗！！\n", "../db_camera.c", 2858);
                return false;
            }
            if (!Mempak_Read(DEBUG_CAM_CONTROLLER_PORT, *c, sDebugCamCuts[i].position, off, ALIGN32(size))) {
                return false;
            }
            off += ALIGN32(size);

            D_80161250[0x3F + sDebugCamCuts[i].letter] = 'O';
        }
    }

    return true;
}

s32 DebugCamera_SaveCallback(char* c) {
    s32 pad[2];
    s32 ret;
    u32 freeSize;
    s32 off;
    s32 size;
    s32 i;

    ret = Mempak_GetFileSize(DEBUG_CAM_CONTROLLER_PORT, *c);
    freeSize = Mempak_GetFreeBytes(DEBUG_CAM_CONTROLLER_PORT);

    if ((u32)sAllocSize < (freeSize + ret)) {
        if (!Mempak_CreateFile(DEBUG_CAM_CONTROLLER_PORT, c, sAllocSize)) {
            return false;
        }

        if (!Mempak_Write(DEBUG_CAM_CONTROLLER_PORT, *c, sDebugCamCuts, 0, sizeof(sDebugCamCuts))) {
            Mempak_DeleteFile(DEBUG_CAM_CONTROLLER_PORT, *c);
            return false;
        }

        off = sizeof(sDebugCamCuts);
        for (i = 0; i < ARRAY_COUNT(sDebugCamCuts) - 1; i++) {
            if (sDebugCamCuts[i].letter != '?') {
                size = sDebugCamCuts[i].nPoints * sizeof(CutsceneCameraPoint);

                ret = Mempak_Write(DEBUG_CAM_CONTROLLER_PORT, *c, sDebugCamCuts[i].lookAt, off, ALIGN32(size));
                if (!ret) {
                    break;
                }
                off += ALIGN32(size);

                ret = Mempak_Write(DEBUG_CAM_CONTROLLER_PORT, *c, sDebugCamCuts[i].position, off, ALIGN32(size));
                if (!ret) {
                    break;
                }

                off += ALIGN32(size);
            }
            ret = true;
        }

        if (ret) {
            return *c;
        } else {
            Mempak_DeleteFile(DEBUG_CAM_CONTROLLER_PORT, *c);
            return false;
        }
    }

    return false;
}

s32 DebugCamera_ClearCallback(char* c) {
    return Mempak_DeleteFile(DEBUG_CAM_CONTROLLER_PORT, *c);
}

void DebugCamera_DrawSlotLetters(char* str, s16 y, s16 x, s32 colorIndex) {
    s32 i;

    for (i = 0; i < ARRAY_COUNT(sDebugCamCuts) - 1; i++) {
        str[i * 2 + 1] = sDebugCamCuts[i].letter;
        str[i * 2 + 0] = '-';
    }

    str[0x14] = str[i * 2 + 1] = '\0';
    DebugCamera_ScreenTextColored(x, y, colorIndex, str);
    str[0x14] = str[i * 2 + 0] = '-';
    DebugCamera_ScreenTextColored(20 + x, y, colorIndex, str + 0x14);
}

void DebugCamera_PrintAllCuts(Camera* cam) {
    s32 i;

    Audio_PlaySfxGeneral(NA_SE_SY_GET_RUPY, &gSfxDefaultPos, 4, &gSfxDefaultFreqAndVolScale,
                         &gSfxDefaultFreqAndVolScale, &gSfxDefaultReverb);
    osSyncPrintf("@@@\n@@@\n@@@/* ****** spline point data ** start here ***** */\n@@@\n");

    for (i = 0; i < ARRAY_COUNT(sDebugCamCuts) - 1; i++) {
        DebugCamCut* cut = &sDebugCamCuts[i];
        if (cut->nPoints != 0) {
            if (i != 0) {
                osSyncPrintf("@@@\n@@@/* ** %d ** */\n@@@\n", i);
            }

            DebugCamera_PrintPoints("Lookat", cut->nPoints, cut->lookAt);
            DebugCamera_PrintPoints("Position", cut->nPoints, cut->position);
            osSyncPrintf("@@@static short  nPoints = %d;\n@@@\n", cut->nPoints);
            osSyncPrintf("@@@static short  nFrames = %d;\n@@@\n", cut->nFrames);
            osSyncPrintf("@@@static short  Mode = %d;\n@@@\n", cut->mode);
        }
    }

    osSyncPrintf("@@@\n@@@\n@@@/* ****** spline point data ** finish! ***** */\n@@@\n");
}

char D_8012D114[] = GFXP_KATAKANA "ﾌﾚ-ﾑ         ";
char D_8012D128[] = GFXP_KATAKANA "ﾄ-ﾀﾙ         ";
char D_8012D13C[] = GFXP_KATAKANA "ｷ-     /   ";

s32 func_800B91B0(Camera* cam, DebugCam* debugCam) {
    s32 pointCount;
    s32 curPoint;

    while (sDebugCamCuts[D_8016110C].letter == '?') {
        D_8016110C++;
        if (D_8016110C >= ARRAY_COUNT(sDebugCamCuts) - 1) {
            sDebugCamAnim.curFrame = 0.0f;
            sDebugCamAnim.unk_04 = 0;
            sDebugCamAnim.keyframe = 0;
            sDebugCamAnim.unk_0A = 0;
            D_8016110C = 0;
            return 0;
        }
    }

    if (!func_800BB2B4(&sDebugCamAnim.positionPos, &sDebugCamAnim.roll, &sDebugCamAnim.fov,
                       sDebugCamCuts[D_8016110C].position, &sDebugCamAnim.keyframe, &sDebugCamAnim.curFrame) &&
        !func_800BB2B4(&sDebugCamAnim.lookAtPos, &sDebugCamAnim.roll, &sDebugCamAnim.fov,
                       sDebugCamCuts[D_8016110C].lookAt, &sDebugCamAnim.keyframe, &sDebugCamAnim.curFrame)) {

        D_8012D13C[7] = ((sDebugCamAnim.keyframe + 1) / 10) + '0';
        D_8012D13C[8] = ((sDebugCamAnim.keyframe + 1) % 10) + '0';
        D_8012D13C[10] = ((sDebugCamCuts[D_8016110C].nPoints - 5) / 10) + '0';
        D_8012D13C[11] = ((sDebugCamCuts[D_8016110C].nPoints - 5) % 10) + '0';
        DebugCamera_SetTextValue(sDebugCamAnim.unk_04, &D_8012D114[10], 4);
        DebugCamera_ScreenTextColored(15, 22, DEBUG_CAM_TEXT_ORANGE, D_8012D114);
        DebugCamera_SetTextValue(sDebugCamAnim.unk_0C, &D_8012D128[10], 4);
        DebugCamera_ScreenTextColored(15, 23, DEBUG_CAM_TEXT_ORANGE, D_8012D128);
        DebugCamera_ScreenTextColored(15, 24, DEBUG_CAM_TEXT_ORANGE, D_8012D13C);
        DebugCamera_ScreenTextColored(16, 26, DEBUG_CAM_TEXT_PEACH, D_8012CEF0);

        sDebugCamAnim.unk_04++;
        sDebugCamAnim.unk_0C++;

        if (sDebugCamCuts[D_8016110C].nFrames > 0 && sDebugCamCuts[D_8016110C].nFrames < sDebugCamAnim.unk_04) {
            D_8016110C++;
            sDebugCamAnim.curFrame = 0.0f;
            sDebugCamAnim.unk_04 = 0;
            sDebugCamAnim.keyframe = 0;
            return D_8016110C | 0x8000;
        }

        if (sDebugCamCuts[D_8016110C].mode != 1) {
            DebugCamera_CopyVec3f(&sDebugCamAnim.positionPos, &debugCam->eye);
            DebugCamera_CopyVec3f(&sDebugCamAnim.lookAtPos, &debugCam->at);
        } else {
            func_800B3FF4(&cam->playerPosRot, &sDebugCamAnim.lookAtPos, &debugCam->at);
            func_800B3FF4(&cam->playerPosRot, &sDebugCamAnim.positionPos, &debugCam->eye);
        }

        debugCam->fov = sDebugCamAnim.fov;
        debugCam->roll = sDebugCamAnim.roll;
        debugCam->rollDegrees = sDebugCamAnim.roll * (360.0f / 256.0f);

    } else {
        D_8016110C++;
        sDebugCamAnim.keyframe = 0;
        sDebugCamAnim.curFrame = 0.0f;
        sDebugCamAnim.unk_04 = 0;
        if (D_8016110C == ARRAY_COUNT(sDebugCamCuts) - 1) {
            D_8016110C = 0;
            sDebugCamAnim.curFrame = 0.0f;
            sDebugCamAnim.keyframe = 0;
            sDebugCamAnim.unk_0A = 0;
            return -1;
        }
    }

    return D_8016110C | 0x8000;
}

void DebugCamera_Reset(Camera* cam, DebugCam* debugCam) {
    s32 i;

    D_801612EA = '*';
    for (i = 0; i < ARRAY_COUNT(sLetters); i++) {
        sLetters[i] = 'X';
    }

    for (i = 0; i < 0xF; i++) {
        DebugCamera_ResetCut(i, false);
    }
    sDebugCamPtr = debugCam;
    D_8016110C = 0;
    sCurFileIdx = 0;
    sLastFileIdx = -1;
    sDebugCamAnim.unk_0A = 0;
}

s32 DebugCamera_UpdateDemoControl(DebugCam* debugCam, Camera* cam) {
    return 1;
}

void func_800BB03C(Camera* cam) {
    func_800B91B0(cam, sDebugCamPtr);
}

void func_800BB060(void) {
    sDebugCamAnim.unk_0A = 0;
}

s32 func_800BB06C(void) {
    return sDebugCamPtr->unk_00 == 2 && sDebugCamAnim.unk_0A != 0;
}
