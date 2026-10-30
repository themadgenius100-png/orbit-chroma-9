#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(
        KC_1,    KC_2,    KC_3,
        KC_4,    KC_5,    KC_6,
        KC_7,    KC_8,    KC_9
    )
};

#if defined(ENCODER_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][2] = {
    [0] = { ENCODER_CW_CCW(KC_VOLU, KC_VOLD) } // Default encoder turns volume up/down
};
#endif

#ifdef OLED_ENABLE
bool oled_task_user(void) {
    oled_write_P(PSTR("Stardance Pad\n"), false);
    oled_write_P(PSTR("Status: Active\n"), false);
    return false;
}
#endif