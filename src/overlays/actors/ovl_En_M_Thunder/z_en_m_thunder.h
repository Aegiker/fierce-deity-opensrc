#ifndef Z_EN_M_THUNDER_H
#define Z_EN_M_THUNDER_H

#include "ultra64.h"
#include "global.h"

struct EnMThunder;

typedef void (*EnMThunderActionFunc)(struct EnMThunder*, PlayState*);

typedef struct EnMThunder {
    /* 0x0000 */ Actor actor;
    /* 0x014C */ ColliderCylinder collider;
    /* 0x0198 */ LightNode* lightNode;
    /* 0x019C */ LightInfo lightInfo;
    /* 0x01AC */ f32 lightColorFrac;
    /* 0x01B0 */ f32 alphaFrac;
    /* 0x01B0 */ f32 scroll;
    /* 0x01B0 */ f32 unk_1B8;
    /* 0x01BC */ f32 adjustLightsArg1;
    /* 0x01C0 */ EnMThunderActionFunc actionFunc;
    /* 0x01C4 */ u16 timer;
    /* 0x01C6 */ u8 subtype;
    /* 0x01C7 */ u8 type;
    /* 0x01C8 */ u8 chargingAlpha;
    /* 0x01C9 */ u8 scaleTarget;
    /* 0x01CA */ u8 isCharging;
} EnMThunder; // size = 0x01CC

typedef enum {
    /* 0 */ ENMTHUNDER_SUBTYPE_SPIN_GREAT,
    /* 1 */ ENMTHUNDER_SUBTYPE_SPIN_REGULAR,
    /* 2 */ ENMTHUNDER_SUBTYPE_SWORDBEAM_GREAT,
    /* 3 */ ENMTHUNDER_SUBTYPE_SWORDBEAM_REGULAR
} EnMThunderSubType;

#endif
