# Microcontroller Target
MCU = RP2040
BOOTLOADER = rp2040

# Core Features
BOOTMAGIC_ENABLE = yes
MOUSEKEY_ENABLE = yes
EXTRAKEY_ENABLE = yes
CONSOLE_ENABLE = no
COMMAND_ENABLE = no
BACKLIGHT_ENABLE = no

# Hardware Add-ons
ENCODER_ENABLE = yes        # Rotary Encoder support
OLED_ENABLE = yes           # OLED Display support
RGB_MATRIX_ENABLE = yes     # SK6812MINI-E per-key RGB support
RGB_MATRIX_DRIVER = ws2812  # SK6812 uses WS2812 protocol