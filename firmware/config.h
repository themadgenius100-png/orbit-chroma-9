#pragma once

#include "config_common.h"

/* --- 9-Key Matrix Setup (3x3) --- */
#define MATRIX_ROWS 3
#define MATRIX_COLS 3
#define MATRIX_ROW_PINS { GP0, GP1, GP2 }
#define MATRIX_COL_PINS { GP3, GP4, GP5 }
#define DIODE_DIRECTION COL2ROW

/* --- Rotary Encoder Setup --- */
#define ENCODERS_PAD_A { GP6 }
#define ENCODERS_PAD_B { GP7 }
#define ENCODER_RESOLUTION 4

/* --- OLED Display Setup (I2C) --- */
#define I2C_DRIVER I2CD1
#define I2C1_SDA_PIN GP8
#define I2C1_SCL_PIN GP9
#define OLED_DISPLAY_128X64

/* --- SK6812MINI-E RGB Matrix Setup --- */
#define RGB_DI_PIN GP10
#define RGB_MATRIX_LED_COUNT 9      // 9 per-key LEDs
#define RGB_MATRIX_MAXIMUM_BRIGHTNESS 130
#define RGB_MATRIX_DEFAULT_MODE RGB_MATRIX_CYCLE_ALL
#define ENABLE_RGB_MATRIX_CYCLE_ALL
#define ENABLE_RGB_MATRIX_RAINBOW_MOVING_CHEVRON