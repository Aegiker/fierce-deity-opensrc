#ifndef Z_EN_FALL_H
#define Z_EN_FALL_H

#include "global.h"

typedef void (*EnFallActionFunc)(struct EnFall*, PlayState*);

typedef struct EnFall {
    /* 0x000 */ Actor actor;
    f32 eyeGlowIntensity;
    f32 scale;
    f32 fallMultiplier;

} EnFall;

#endif