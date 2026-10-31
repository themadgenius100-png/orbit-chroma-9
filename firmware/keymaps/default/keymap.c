#include QMK_KEYBOARD_H

// 1. KEYMAP DEFINITION (3x3 Matrix + Encoder)
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    // Layer 0: Base / Default
    [0] = LAYOUT(
        KC_1,    KC_2,    KC_3,
        KC_4,    KC_5,    KC_6,
        KC_7,    KC_8,    KC_9
    ),
    // Layer 1: Gaming / Action
    [1] = LAYOUT(
        KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS
    ),
    // Layer 2: Media / Controls
    [2] = LAYOUT(
        KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS
    )
};

#if defined(ENCODER_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][2] = {
    [0] = { ENCODER_CW_CCW(KC_VOLU, KC_VOLD) },
    [1] = { ENCODER_CW_CCW(KC_TRNS, KC_TRNS) },
    [2] = { ENCODER_CW_CCW(KC_MNXT, KC_MPRV) }
};
#endif

// 2. CLEAN 8x8 PIXEL ICON ARRAYS (PROGMEM)
// Pose 0: Idle / Center Star
const char PROGMEM cat_pose_idle[] = {
    0x10, 0x28, 0x44, 0xfe, 0x44, 0x28, 0x10, 0x00
};

// Pose 1: Left Paw Active Icon
const char PROGMEM cat_pose_left[] = {
    0x00, 0x7e, 0x42, 0x42, 0x42, 0x42, 0x7e, 0x00
};

// Pose 2: Right Paw Active Icon
const char PROGMEM cat_pose_right[] = {
    0x18, 0x3c, 0x7e, 0xdb, 0x99, 0x18, 0x18, 0x18
};

// 3. DYNAMIC OLED RENDERING BASED ON ACTIVE LAYER
#ifdef OLED_ENABLE
bool oled_task_user(void) {
    uint8_t current_layer = get_highest_layer(layer_state);

    // Header Title & Inline Icon
    oled_write_P(PSTR("STARDANCE "), false);

    // Switch Icon graphics according to active layer
    switch (current_layer) {
        case 0:
            oled_write_raw_P(cat_pose_idle, sizeof(cat_pose_idle));
            break;
        case 1:
            oled_write_raw_P(cat_pose_left, sizeof(cat_pose_left));
            break;
        case 2:
            oled_write_raw_P(cat_pose_right, sizeof(cat_pose_right));
            break;
        default:
            oled_write_raw_P(cat_pose_idle, sizeof(cat_pose_idle));
            break;
    }

    oled_write_P(PSTR("\n--------------------\n"), false);

    // Layer Status Text
    oled_write_P(PSTR("Active Layer: "), false);
    switch (current_layer) {
        case 0:
            oled_write_P(PSTR("BASE\n"), false);
            break;
        case 1:
            oled_write_P(PSTR("GAMING\n"), false);
            break;
        case 2:
            oled_write_P(PSTR("MEDIA\n"), false);
            break;
        default:
            oled_write_P(PSTR("UNKNOWN\n"), false);
            break;
    }

    oled_write_P(PSTR("Status: Ready"), false);
    return false;
}
#endif