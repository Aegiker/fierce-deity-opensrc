#ifndef Z_EN_TORCH2_H
#define Z_EN_TORCH2_H

#include "ultra64.h"
#include "global.h"

typedef struct PlayerEnemy {
    /* 0x0000 */ Actor      actor;
    /* 0x014C */ s8         currentTunic; // current tunic from `PlayerTunic`
    /* 0x014D */ s8         currentSwordItemId;
    /* 0x014E */ s8         currentShield; // current shield from `PlayerShield`
    /* 0x014F */ s8         currentBoots; // current boots from `PlayerBoots`
    /* 0x0150 */ s8         heldItemButton; // Button index for the item currently used
    /* 0x0151 */ s8         heldItemAction; // Item action for the item currently used
    /* 0x0152 */ u8         heldItemId; // Item id for the item currently used
    /* 0x0153 */ s8         prevBoots; // previous boots from `PlayerBoots`
    /* 0x0154 */ s8         itemAction; // the difference between this and heldItemAction is unclear
    /* 0x0155 */ char       unk_155[0x003];
    /* 0x0158 */ u8         modelGroup;
    /* 0x0159 */ u8         nextModelGroup;
    /* 0x015A */ s8         unk_15A;
    /* 0x015B */ u8         modelAnimType;
    /* 0x015C */ u8         leftHandType;
    /* 0x015D */ u8         rightHandType;
    /* 0x015E */ u8         sheathType;
    /* 0x015F */ u8         currentMask; // current mask equipped from `PlayerMask`
    /* 0x0160 */ Gfx**      rightHandDLists;
    /* 0x0164 */ Gfx**      leftHandDLists;
    /* 0x0168 */ Gfx**      sheathDLists;
    /* 0x016C */ Gfx**      waistDLists;
    /* 0x0170 */ u8         giObjectLoading;
    /* 0x0174 */ DmaRequest giObjectDmaRequest;
    /* 0x0194 */ OSMesgQueue giObjectLoadQueue;
    /* 0x01AC */ OSMesg     giObjectLoadMsg;
    /* 0x01B0 */ void*      giObjectSegment; // also used for title card textures
    /* 0x01B4 */ SkelAnime  skelAnime;
    /* 0x01F8 */ Vec3s      jointTable[PLAYER_LIMB_BUF_COUNT];
    /* 0x0288 */ Vec3s      morphTable[PLAYER_LIMB_BUF_COUNT];
    /* 0x0318 */ Vec3s      blendTable[PLAYER_LIMB_BUF_COUNT];
    /* 0x03A8 */ s16        unk_3A8[2];
    /* 0x03AC */ Actor*     heldActor;
    /* 0x03B0 */ Vec3f      leftHandPos;
    /* 0x03BC */ Vec3s      unk_3BC;
    /* 0x03C4 */ Actor*     unk_3C4;
    /* 0x03C8 */ Vec3f      unk_3C8;
    /* 0x03D4 */ char       unk_3D4[0x058];
    /* 0x042C */ s8         doorType;
    /* 0x042D */ s8         doorDirection;
    /* 0x042E */ s16        doorTimer;
    /* 0x0430 */ Actor*     doorActor;
    /* 0x0434 */ s8         getItemId;
    /* 0x0436 */ u16        getItemDirection;
    /* 0x0438 */ Actor*     interactRangeActor;
    /* 0x043C */ s8         mountSide;
    /* 0x043D */ char       unk_43D[0x003];
    /* 0x0440 */ Actor*     rideActor;
    /* 0x0444 */ u8         csMode;
    /* 0x0445 */ u8         prevCsMode;
    /* 0x0446 */ u8         cueId;
    /* 0x0447 */ u8         unk_447;
    /* 0x0448 */ Actor*     unk_448;
    /* 0x044C */ char       unk_44C[0x004];
    /* 0x0450 */ Vec3f      unk_450;
    /* 0x045C */ Vec3f      unk_45C;
    /* 0x0468 */ char       unk_468[0x002];
    /* 0x046A */ s16        doorBgCamIndex;
    /* 0x046C */ s16        subCamId;
    /* 0x046E */ char       unk_46E[0x02A];
    /* 0x0498 */ ColliderCylinder cylinder;
    /* 0x04E4 */ ColliderQuad meleeWeaponQuads[2];
    /* 0x05E4 */ ColliderQuad shieldQuad;
    /* 0x0664 */ Actor*     unk_664;
    /* 0x0668 */ char       unk_668[0x004];
    /* 0x066C */ s32        unk_66C;
    /* 0x0670 */ s32        meleeWeaponEffectIndex;
    /* 0x0674 */ PlayerFunc674 func_674;
    /* 0x0678 */ PlayerAgeProperties* ageProperties;
    /* 0x067C */ u32        stateFlags1;
    /* 0x0680 */ u32        stateFlags2;
    /* 0x0684 */ Actor*     unk_684;
    /* 0x0688 */ Actor*     boomerangActor;
    /* 0x068C */ Actor*     naviActor;
    /* 0x0690 */ s16        naviTextId;
    /* 0x0692 */ u16        stateFlags3;
    /* 0x0693 */ s8         exchangeItemId;
    /* 0x0694 */ Actor*     targetActor;
    /* 0x0698 */ f32        targetActorDistance;
    /* 0x069C */ char       unk_69C[0x004];
    /* 0x06A0 */ f32        unk_6A0;
    /* 0x06A4 */ f32        closestSecretDistSq;
    /* 0x06A8 */ Actor*     unk_6A8;
    /* 0x06AC */ s8         unk_6AC;
    /* 0x06AD */ u8         unk_6AD;
    /* 0x06AE */ u16        unk_6AE;
    /* 0x06B0 */ s16        unk_6B0;
    /* 0x06B2 */ char       unk_6B4[0x004];
    /* 0x06B6 */ s16        unk_6B6;
    /* 0x06B8 */ s16        unk_6B8;
    /* 0x06BA */ s16        unk_6BA;
    /* 0x06BC */ s16        unk_6BC;
    /* 0x06BE */ s16        unk_6BE;
    /* 0x06C0 */ s16        unk_6C0;
    /* 0x06C2 */ s16        unk_6C2;
    /* 0x06C4 */ f32        unk_6C4;
    /* 0x06C8 */ SkelAnime  skelAnime2;
    /* 0x070C */ Vec3s      jointTable2[PLAYER_LIMB_BUF_COUNT];
    /* 0x079C */ Vec3s      morphTable2[PLAYER_LIMB_BUF_COUNT];
    /* 0x082C */ PlayerFunc82C func_82C;
    /* 0x0830 */ f32        unk_830;
    /* 0x0834 */ s16        unk_834;
    /* 0x0836 */ s8         unk_836;
    /* 0x0837 */ u8         unk_837;
    /* 0x0838 */ f32        speedXZ; // Controls horizontal speed, used for `actor.speed`. Current or target value depending on context.
    /* 0x083C */ s16        yaw; // General yaw value, used both for world and shape rotation. Current or target value depending on context.
    /* 0x083E */ s16        zTargetYaw; // yaw relating to Z targeting/"parallel" mode
    /* 0x0840 */ u16        underwaterTimer;
    /* 0x0842 */ s8         meleeWeaponAnimation;
    /* 0x0843 */ s8         meleeWeaponState;
    /* 0x0844 */ s8         unk_844;
    /* 0x0845 */ u8         unk_845;
    /* 0x0846 */ u8         unk_846;
    /* 0x0847 */ s8         unk_847[4];
    /* 0x084B */ s8         unk_84B[4];
    /* 0x084F */ s8         unk_84F;
    /* 0x0850 */ s16        unk_850; // multipurpose timer
    /* 0x0854 */ f32        unk_854;
    /* 0x0858 */ f32        unk_858;
    /* 0x085C */ f32        unk_85C; // stick length among other things
    /* 0x0860 */ s16        unk_860; // stick flame timer among other things
    /* 0x0862 */ s8         unk_862; // get item draw ID + 1
    /* 0x0864 */ f32        unk_864;
    /* 0x0868 */ f32        unk_868;
    /* 0x086C */ f32        unk_86C;
    /* 0x0870 */ f32        unk_870;
    /* 0x0874 */ f32        unk_874;
    /* 0x0878 */ f32        unk_878;
    /* 0x087C */ s16        unk_87C;
    /* 0x087E */ s16        unk_87E;
    /* 0x0880 */ f32        unk_880;
    /* 0x0884 */ f32        wallHeight; // height used to determine whether link can climb or grab a ledge at the top
    /* 0x0888 */ f32        wallDistance; // distance to the colliding wall plane
    /* 0x088C */ u8         unk_88C;
    /* 0x088D */ u8         unk_88D;
    /* 0x088E */ u8         unk_88E;
    /* 0x088F */ u8         unk_88F;
    /* 0x0890 */ u8         unk_890;
    /* 0x0891 */ u8         shockTimer;
    /* 0x0892 */ u8         unk_892;
    /* 0x0893 */ u8         hoverBootsTimer;
    /* 0x0894 */ s16        fallStartHeight; // last truncated Y position before falling
    /* 0x0896 */ s16        fallDistance; // truncated Y distance the player has fallen so far (positive is down)
    /* 0x0898 */ s16        unk_898;
    /* 0x089A */ s16        unk_89A;
    /* 0x089C */ s16        unk_89C;
    /* 0x089E */ u16        floorSfxOffset;
    /* 0x08A0 */ u8         unk_8A0;
    /* 0x08A1 */ u8         unk_8A1;
    /* 0x08A2 */ s16        unk_8A2;
    /* 0x08A4 */ f32        unk_8A4;
    /* 0x08A8 */ f32        unk_8A8;
    /* 0x08AC */ f32        pushedSpeed; // Pushing player, examples include water currents, floor conveyors, climbing sloped surfaces
    /* 0x08B0 */ s16        pushedYaw; // Yaw direction of player being pushed
    /* 0x08B4 */ WeaponInfo meleeWeaponInfo[3];
    /* 0x0908 */ Vec3f      bodyPartsPos[PLAYER_BODYPART_MAX];
    /* 0x09E0 */ MtxF       mf_9E0;
    /* 0x0A20 */ MtxF       shieldMf;
    /* 0x0A60 */ u8         isBurning;
    /* 0x0A61 */ u8         flameTimers[PLAYER_BODYPART_MAX]; // one flame per body part
    /* 0x0A73 */ u8         unk_A73;
    /* 0x0A74 */ PlayerFuncA74 func_A74;
    /* 0x0A78 */ s8         invincibilityTimer; // prevents damage when nonzero (positive = visible, counts towards zero each frame)
    /* 0x0A79 */ u8         unk_A79;
    /* 0x0A7A */ u8         unk_A7A;
    /* 0x0A7B */ u8         unk_A7B;
    /* 0x0A7C */ f32        unk_A7C;
    /* 0x0A80 */ s16        unk_A80;
    /* 0x0A82 */ u16        prevFloorSfxOffset;
    /* 0x0A84 */ s16        unk_A84;
    /* 0x0A86 */ s8         unk_A86;
    /* 0x0A87 */ u8         unk_A87;
    /* 0x0A88 */ Vec3f      unk_A88; // previous body part 0 position
    /* deity  */ s16        naviWarning;
    /* deity  */ u8         lastItem;
    /* deity  */ u8         transformTargetForm;
    /* deity  */ u8         transformPreviousForm;
    /* deity  */ s8         transformEventTimer1;
    /* deity  */ s16        transformEventTimer2;
    /* deity  */ f32        transformMatrixModifiers[6]; // among other things, this is used to squish or stretch Link's head.
    /* deity  */ LightNode* lightNode;
    /* deity  */ LightInfo  lightInfo;
    /* deity  */ u8         maskObjectLoading; // 0 = not loaded, 1 = loading, 2 = loaded
    /* deity  */ u16        maskObjectId;
    /* deity  */ DmaRequest maskObjectDmaRequest;
    /* deity  */ OSMesgQueue maskObjectLoadQueue;
    /* deity  */ OSMesg     maskObjectLoadMsg;
    /* deity  */ void*      maskObjectSegment;
    f32 sStickTilt;
    s16 sStickAngle;
    f32 sSwordJumpHeight;
    s32 sHoldShieldTimer;
    u8 sZTargetFlag;
    u8 sDeathFlag;
    Input sInput;
    u8 sSwordJumpState;
    Vec3f sSpawnPoint;
    u8 sJumpslashTimer;
    u8 sJumpslashFlag;
    u8 sActionState;
    u8 sSwordJumpTimer;
    u8 sCounterState;
    u8 sDodgeRollState;
    u8 sStaggerCount;
    u8 sStaggerTimer;
    s8 sLastSwordAnim;
    u8 sAlpha;
} PlayerEnemy; // size = bigger

#endif
