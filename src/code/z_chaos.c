#include "global.h"
#include "chaos.h"

u32 Chaos_SecondsToFrames(u8 seconds) {
    return (20) * seconds;
}

u8 Check_Button_All(u16 state, u16 combo) {
    return (~((state) | ~(combo)) == 0);
}

u8 Check_Button_Any(u16 state, u16 combo) {
    return (((state) & (combo)) != 0);
}