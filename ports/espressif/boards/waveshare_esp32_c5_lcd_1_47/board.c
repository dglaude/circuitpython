#include "supervisor/board.h"
#include "mpconfigboard.h"
#include "shared-bindings/busio/SPI.h"
#include "shared-bindings/fourwire/FourWire.h"
#include "shared-bindings/busdisplay/BusDisplay.h"
#include "shared-module/displayio/__init__.h"
#include "supervisor/shared/board.h"

#define DELAY 0x80

// ST7789 initialization sequence for 1.47" LCD (172x320)
static const uint8_t display_init_sequence[] = {
    0x01, DELAY, 150,               // SWRESET: Software reset
    0x11, DELAY, 150,               // SLPOUT: Exit sleep mode
    0x3A, 1, 0x55,                  // COLMOD: 16-bit color format
    0x36, 1, 0x60,                  // MADCTL: Landscape orientation (MX + MV)
    0x21, 0,                        // INVON: Inversion on (required for IPS panel)
    0x13, DELAY, 10,                // NORON: Normal display on
    0x29, DELAY, 100,               // DISPON: Main screen turn on
};

void board_init(void) {
    // 1. Initialize SPI bus (pins shared with SD Card)
    busio_spi_obj_t *spi = &allocate_display_bus()->spi;
    common_hal_busio_spi_construct(
        spi,
        &pin_GPIO6,                 // SCLK
        &pin_GPIO7,                 // MOSI
        NULL,                       // MISO (not needed for display output)
        false
    );
    common_hal_busio_spi_never_reset(spi);

    // 2. Initialize FourWire bus interface
    fourwire_fourwire_obj_t *bus = &allocate_display_bus_or_raise()->fourwire;
    common_hal_fourwire_fourwire_construct(
        bus,
        spi,
        &pin_GPIO15,                // DC
        &pin_GPIO14,                // CS
        &pin_GPIO21,                // RST
        40000000,                   // Baudrate (40 MHz)
        0,                          // Polarity
        0                           // Phase
    );

    // 3. Construct the BusDisplay object -> exposes board.DISPLAY
    busdisplay_busdisplay_obj_t *display = &allocate_display()->display;
    common_hal_busdisplay_busdisplay_construct(
        display,
        bus,
        320,                        // Width
        172,                        // Height
        0,                          // Colstart
        34,                         // Rowstart ((240 - 172) / 2)
        0,                          // Rotation
        16,                         // Color depth
        false,                      // Grayscale
        false,                      // Pixels in byte share row
        1,                          // Bytes per cell
        false,                      // Reverse pixels in byte
        true,                       // Reverse bytes in word
        0x2a,                       // Set column command
        0x2b,                       // Set row command
        0x2c,                       // Write RAM command
        display_init_sequence,
        sizeof(display_init_sequence),
        &pin_GPIO22,                // Backlight pin (LCD_BL)
        1.0f,                       // Brightness (1.0 = 100%)
        true,                       // Auto-refresh
        60,                         // Native FPS
        true,                       // Backlight active high
        false                       // SH1107 addressing
    );
}

bool board_reset_pin_number(mp_int_t pin_number) {
    // Protect display and backlight pins during soft reset
    if (pin_number == 14 || pin_number == 15 || pin_number == 21 || pin_number == 22) {
        return true;
    }
    return false;
}
