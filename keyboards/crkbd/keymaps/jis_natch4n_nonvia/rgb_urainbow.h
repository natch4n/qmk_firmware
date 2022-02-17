#include QMK_KEYBOARD_H
#pragma once

#define LED_SEQUENCE_SIZE 12
extern const int led_sequence[LED_SEQUENCE_SIZE];

extern uint8_t sat,val;
extern float time_per_sec;

extern void reflesh_effect(void);
