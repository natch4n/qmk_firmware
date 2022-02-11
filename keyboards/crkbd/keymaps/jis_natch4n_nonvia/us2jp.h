#include "user_config.h"
#pragma once

enum u2j_key{
    //symbol keys
    U2J_2 = SAFE_RANGE_FOR_U2J,
    U2J_6,
    U2J_7,
    U2J_8,
    U2J_9,
    U2J_0,
    U2J_MINS,
    U2J_EQL,
    U2J_LBRC,
    U2J_RBRC,
    U2J_BSLS,
    U2J_SCLN,
    U2J_QUOT,
    U2J_GRV,
    U2J_SAFE_RANGE
};

#ifdef US2JP_ENABLE_NATIVE_CONVERT
extern uint16_t get_symbol_index(uint16_t keycode);
extern bool tap_u2j_code_as_jp(uint16_t keycode, keyrecord_t *record);
extern bool tap_u2j_code_as_us(uint16_t keycode, keyrecord_t *record);
#endif

#ifdef US2JP_ENABLE_UNIVERSAL_CONVERT
extern bool tap_qmk_code_as_jp(uint16_t keycode, keyrecord_t *record);
#endif

extern void tap_stey_code(uint16_t keycode, bool lshift, bool rshift, bool shift);
