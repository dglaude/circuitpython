USB_VID = 0x303A
USB_PID = 0x82C5
USB_PRODUCT = "ESP32-C5-DevKitC-1-N8R8"
USB_MANUFACTURER = "Espressif"

IDF_TARGET = esp32c5

# Selects sdkconfig-flash-qio.defaults
# was "CIRCUITPY_ESP_FLASH_MODE = qio" now is:
FLASH_MODE = qio

# Selects partitions-4MB.csv
CIRCUITPY_ESP_FLASH_SIZE = 4MB

CIRCUITPY_NEOPIXEL_WRITE = 1
