#pragma once
#include QMK_KEYBOARD_H

enum my_key {
    //universal utils
    MY_ZKHK = SAFE_RANGE,
    MY_CAPS,

    //user utils
    MY_JP,
    MY_OLED,

    MY_SAFE_RANGE
};

enum my_td {
    TD_RALT_GUI
};

#define TD_RALT TD(TD_RALT_GUI)
#define SAFE_RANGE_FOR_U2J MY_SAFE_RANGE
#define US2JP_ENABLE_NATIVE_CONVERT
