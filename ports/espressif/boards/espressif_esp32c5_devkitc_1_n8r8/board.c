// This file is part of the CircuitPython project: https://circuitpython.org
//
// SPDX-License-Identifier: MIT

#include "supervisor/board.h"
#include "mpconfigboard.h"
#include "shared-bindings/microcontroller/Pin.h"
#include "shared-bindings/busio/SPI.h"
#include "shared-bindings/fourwire/FourWire.h"
#include "shared-module/displayio/__init__.h"
#include "shared-module/displayio/mipi_constants.h"
#include "shared-bindings/board/__init__.h"

#define DELAY 0x80

// Driver: ST7789V3, Panel: LBS147TC-IF15 (172x320 RGB)
static const uint8_t display_init_sequence[] = {
    0x01, 0 | DELAY, 120,
    0x11, 0 | DELAY, 120,
    0x13, 0,
    0x36, 1, 0x00,
    0x3A, 1 | DELAY, 0x05, 10,
    0xB2, 5, 0x0C, 0x0C, 0x00, 0x33, 0x33,
    0xB7, 1, 0x35,
    0xBB, 1, 0x20,
    0xC0, 1, 0x2C,
    0xC2, 2, 0x01, 0xFF,
    0xC3, 1, 0x13,
    0xC4, 1, 0x20,
    0xC6, 1, 0x0F,
    0xD0, 2, 0xA4, 0xA1,
    0xE0, 14, 0xF0, 0x00, 0x04, 0x04, 0x04, 0x05, 0x29, 0x33, 0x3E, 0x38, 0x12, 0x12, 0x28, 0x30,
    0xE1, 14, 0xF0, 0x07, 0x0A, 0x0D, 0x0B, 0x07, 0x28, 0x33, 0x3E, 0x36, 0x14, 0x14, 0x29, 0x32,
    0x21, 0,
    0x29, 0 | DELAY, 255,
};

static void display_init(void) {
    busio_spi_obj_t *spi = common_hal_board_create_spi(0);
    fourwire_fourwire_obj_t *bus = &allocate_display_bus()->fourwire_bus;
    bus->base.type = &fourwire_fourwire_type;

    common_hal_fourwire_fourwire_construct(
        bus,
        spi,
        MP_OBJ_FROM_PTR(&pin_GPIO24),    // LCD_DC
        MP_OBJ_FROM_PTR(&pin_GPIO23),    // LCD_CS
        MP_OBJ_FROM_PTR(&pin_GPIO26),    // LCD_RST
        40000000,                       // Baudrate (40 MHz)
        0,                              // Polarity
        0                               // Phase
        );

    busdisplay_busdisplay_obj_t *display = &allocate_display()->display;
    display->base.type = &busdisplay_busdisplay_type;

    common_hal_busdisplay_busdisplay_construct(
        display,
        bus,
        172,                            // Native width
        320,                            // Native height
        34,                             // Column start offset
        0,                              // Row start offset
        0,                              // Rotation (native portrait, changeable in Python)
        16,                             // Color depth
        false,                          // Grayscale
        false,                          // Pixels in byte share row
        1,                              // Bytes per cell
        false,                          // Reverse pixels in byte
        true,                           // Reverse pixels in word
        MIPI_COMMAND_SET_COLUMN_ADDRESS,
        MIPI_COMMAND_SET_PAGE_ADDRESS,
        MIPI_COMMAND_WRITE_MEMORY_START,
        display_init_sequence,
        sizeof(display_init_sequence),
        &pin_GPIO10,                    // Backlight pin (LCD_BL)
        NO_BRIGHTNESS_COMMAND,
        1.0f,                           // Brightness
        false,                          // Single byte bounds
        false,                          // Data as commands
        true,                           // Auto refresh
        60,                             // Native FPS
        true,                           // Backlight active high
        false,                          // SH1107 addressing
        50000                           // Backlight PWM frequency
        );
}

void board_init(void) {
    display_init();
}

bool board_reset_pin_number(mp_int_t pin_number) {
    // Preserve display lines and backlight during soft reset
    if (pin_number == 10 || pin_number == 23 || pin_number == 24 || pin_number == 26) {
        return true;
    }
    return false;
}
