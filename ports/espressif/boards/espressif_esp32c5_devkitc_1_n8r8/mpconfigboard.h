// This file is part of the CircuitPython project: https://circuitpython.org
//

#pragma once

#define MICROPY_HW_BOARD_NAME "ESP32-C5-DevKitC-1-N8R8"
#define MICROPY_HW_MCU_NAME "ESP32-C5"

#define CIRCUITPY_BOOT_BUTTON (&pin_GPIO0)

// Status NeoPixel sur GPIO8 pour la Waveshare
#define CIRCUITPY_STATUS_LED_POWER (&pin_GPIO8)
#define MICROPY_HW_NEOPIXEL (&pin_GPIO8)
#define MICROPY_HW_NEOPIXEL_COUNT (1)
