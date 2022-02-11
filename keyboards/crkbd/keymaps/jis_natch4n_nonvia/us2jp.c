#include QMK_KEYBOARD_H
#include <keymap_jp.h>
#include "config.h"
#include "user_config.h"
#include "us2jp.h"

#ifdef US2JP_ENABLE_NATIVE_CONVERT
#define SYMBOL_MAP_SIZE (U2J_SAFE_RANGE - SAFE_RANGE_FOR_U2J)

const uint16_t jp_symbol_map[SYMBOL_MAP_SIZE][2] = {
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

const uint16_t us_symbol_map[SYMBOL_MAP_SIZE] = {
    KC_2,
    KC_6,
    KC_7,
    KC_8,
    KC_9,
    KC_0,
    KC_MINS,
    KC_EQL,
    KC_LBRC,
    KC_RBRC,
    KC_BSLS,
    KC_SCLN,
    KC_QUOT,
    KC_GRV
};

uint16_t get_symbol_index(uint16_t keycode) {
    return keycode - SAFE_RANGE_FOR_U2J;
}


bool tap_u2j_code_as_jp(uint16_t keycode, keyrecord_t *record) {
    if(!record->event.pressed) return true;
    uint16_t index = get_symbol_index(keycode);
    if(SYMBOL_MAP_SIZE <= index) return true;

    bool lshift = get_mods() & MOD_BIT(KC_LSFT);
    bool rshift = get_mods() & MOD_BIT(KC_RSFT);
    bool shift  = lshift | rshift;
    uint16_t stey_code = jp_symbol_map[index][shift ? 1 : 0];

    tap_stey_code(stey_code, lshift, rshift, shift);

    return false;
}

bool tap_u2j_code_as_us(uint16_t keycode, keyrecord_t *record) {
    if(!record->event.pressed) return true;
    uint16_t index = get_symbol_index(keycode);
    if(SYMBOL_MAP_SIZE <= index) return true;

    tap_code(us_symbol_map[index]);
    return false;
}
#endif

#ifdef US2JP_ENABLE_UNIVERSAL_CONVERT
bool tap_qmk_code_as_jp(uint16_t keycode, keyrecord_t *record) {
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
        default      : return true;
    }

    tap_stey_code(keycode, lshift, rshift, shift);

    return false;
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
