#include QMK_KEYBOARD_H
#include <keymap_jp.h>
#include "config.h"

enum user_key{
    //symbol keys
    U2J_2 = SAFE_RANGE_FOR_US2JP,
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
    U2J_SAFERANGE
};

#ifdef US2JP_ENABLE_NATIVE_CONVERT

const uint16_t my_symbols[14][3] = {
    {JP_2   , JP_AT  },
    {JP_6   , JP_CIRC},
    {JP_7   , JP_AMPR},
    {JP_8   , JP_ASTR},
    {JP_9   , JP_LPRN},
    {JP_0   , JP_RPRN},
    {JP_MINS, JP_UNDS},
    {JP_EQL , JP_PLUS},
    {JP_LBRC, JP_LCBR},
    {JP_RBRC, JP_RCBR},
    {JP_BSLS, JP_PIPE},
    {JP_SCLN, JP_COLN},
    {JP_QUOT, JP_DQUO},
    {JP_GRV , JP_TILD}
};

const int symbol_array_size = sizeof(my_symbols) / sizeof(uint16_t[2]);

bool native_convert(uint16_t keycode, keyrecord_t *record) {
    uint16_t index = keycode - MY_2;
    if(symbol_array_size <= index) return false;

    bool lshift = get_mods() & MOD_BIT(KC_LSFT);
    bool rshift = get_mods() & MOD_BIT(KC_RSFT);
    bool shift  = lshift | rshift;
    uint16_t stey_code = my_symbols[index][shift ? 2 : 1];

    tap_stey_code(stey_code, lshift, rshift, shift);

    return true;
}
#endif

#ifdef US2JP_ENABLE_UNIVERSAL_CONVERT
bool universal_convert(uint16_t keycode, keyrecord_t *record) {
    bool lshift = get_mods() & MOD_BIT(KC_LSFT);
    bool rshift = get_mods() & MOD_BIT(KC_RSFT);
    bool shift = lshift | rshift;
    uint16_t k = shift ? (keycode | QK_LSFT) : keycode;

    switch (k) {
        case KC_LPRN : k = JP_LPRN; break;
        case KC_RPRN : k = JP_RPRN; break;
        case KC_AT   : k = JP_AT  ; break;
        case KC_LBRC : k = JP_LBRC; break;
        case KC_RBRC : k = JP_RBRC; break;
        case KC_LCBR : k = JP_LCBR; break;
        case KC_RCBR : k = JP_RCBR; break;
        case KC_MINS : k = JP_MINS; break;
        case KC_EQL  : k = JP_EQL ; break;
        case KC_BSLS : k = JP_BSLS; break;
        case KC_SCLN : k = JP_SCLN; break;
        case KC_QUOT : k = JP_QUOT; break;
        case KC_GRV  : k = JP_GRV ; break;
        case KC_PLUS : k = JP_PLUS; break;
        case KC_COLN : k = JP_COLN; break;
        case KC_UNDS : k = JP_UNDS; break;
        case KC_PIPE : k = JP_PIPE; break;
        case KC_DQT  : k = JP_DQUO; break;
        case KC_ASTR : k = JP_ASTR; break;
        case KC_TILD : k = JP_TILD; break;
        case KC_AMPR : k = JP_AMPR; break;
        case KC_CIRC : k = JP_CIRC; break;
        default      : return false;
    }

    tap_stey_code(keycode, lshift, rshift, shift);

    return true;
}
#endif

void tap_stey_code(uint16_t keycode, bool lshift, bool rshift, bool shift) {
        if(((keycode & QK_LSFT) == QK_LSFT) | ((keycode & QK_RSFT) == QK_RSFT)) {
        if(!shift) register_code(KC_LSFT);
        tap_code(keycode);
        if(!shift) unregister_code(KC_LSFT);
    }else {
        if(lshift) unregister_code(KC_LSFT);
        if(rshift) unregister_code(KC_RSFT);
        tap_code(keycode);
        if(lshift) register_code(KC_LSFT);
        if(rshift) register_code(KC_RSFT);
    }
    return;
}

bool tap_jp_code(uint16_t keycode, keyrecord_t *record) {
    if(!record->event.pressed) return true;
    #ifdef JP2US_ENABLE_NATIVE_CONVERT
    if(native_convert(keycode, record)) return false;
    #endif

    #ifdef JP2US_ENABLE_UNIVERSAL_CONVERT
    if(universal_convert(keycode, record)) return false;
    #endif

    return true;
}
