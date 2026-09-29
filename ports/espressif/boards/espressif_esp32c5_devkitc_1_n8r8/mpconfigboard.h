// This file is part of the CircuitPython project: https://circuitpython.org
//
// SPDX-FileCopyrightText: Copyright (c) 2019 Scott Shawcroft for Adafruit Industries
//
// SPDX-License-Identifier: MIT

#pragma once

// Micropython setup

#define MICROPY_HW_BOARD_NAME "ESP32-C5-DevKitC-1-N8R8"
#define MICROPY_HW_MCU_NAME "ESP32-C5"

#define CIRCUITPY_BOOT_BUTTON (&pin_GPIO0)

// Waveshare onboard NeoPixel on GPIO8
#define CIRCUITPY_STATUS_LED_POWER (&pin_GPIO8)
#define MICROPY_HW_NEOPIXEL (&pin_GPIO8)
#define MICROPY_HW_NEOPIXEL_COUNT (1)

// Default SPI bus definitions (shared between LCD and TF card)
#define DEFAULT_SPI_BUS_SCK (&pin_GPIO7)
#define DEFAULT_SPI_BUS_MOSI (&pin_GPIO6)
#define DEFAULT_SPI_BUS_MISO (&pin_GPIO5)
