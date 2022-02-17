#include QMK_KEYBOARD_H
#include <color.h>
#include <rgblight.h>
#include "rgb_urainbow.h"

const int led_sequence[LED_SEQUENCE_SIZE] = {
    0, 1, 2, 3, 4, 5, //left
    32,31,30,29,28,27 //right
};

float time_per_sec = 0.1;

void reflesh_effect(void) {
    static float hue = 0;
    hue = (time_per_sec * sync_timer_read32() * UINT8_MAX) / 1000;
    RGB set_rgb = hsv_to_rgb((HSV){(uint8_t) hue, 255, 90});

    for(int i = 0; i < LED_SEQUENCE_SIZE; i++) {
        if(led_sequence[i] < RGBLED_NUM) {
            led[led_sequence[i]] = set_rgb;
        }
    }
    rgblight_set();
}
