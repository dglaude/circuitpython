#pragma once

#define MICROPY_HW_BOARD_NAME "Waveshare ESP32-C5 LCD 1.47"
#define MICROPY_HW_MCU_NAME "ESP32-C5"

#define MICROPY_HW_NEOPIXEL (&pin_GPIO8)
#define CIRCUITPY_STATUS_LED_POWER_INVERTED (0)

// Default I2C bus
#define DEFAULT_I2C_BUS_SDA (&pin_GPIO2)
#define DEFAULT_I2C_BUS_SCL (&pin_GPIO3)

// Default SPI bus (shared with LCD & SD slot)
#define DEFAULT_SPI_BUS_SCK (&pin_GPIO6)
#define DEFAULT_SPI_BUS_MOSI (&pin_GPIO7)
#define DEFAULT_SPI_BUS_MISO (&pin_GPIO5)

// Default UART
#define DEFAULT_UART_BUS_TX (&pin_GPIO16)
#define DEFAULT_UART_BUS_RX (&pin_GPIO17)
