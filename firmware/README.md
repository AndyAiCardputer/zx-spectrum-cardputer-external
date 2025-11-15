# Firmware Binaries

## ZX_Spectrum_External_v3.137.bin

**Version:** 3.137  
**Date:** 2025-01-XX  
**Platform:** M5Stack Cardputer-Adv (ESP32-S3)  
**Display:** External ILI9488 (480×320)

### Installation

1. Download the `.bin` file
2. Use PlatformIO or esptool.py to flash:
   ```bash
   esptool.py --chip esp32s3 --port /dev/cu.usbmodem* write_flash 0x10000 ZX_Spectrum_External_v3.137.bin
   ```
3. Or use PlatformIO upload command:
   ```bash
   pio run -t upload
   ```

### Features

- Full ZX Spectrum 48K emulation
- External ILI9488 display support (480×320)
- SD card support for games
- Audio support (Beeper)
- Screenshot functionality
- Support for .SNA, .Z80, .TAP files

### Hardware Requirements

- M5Stack Cardputer-Adv
- External ILI9488 display (480×320) via EXT connector
- SD card (optional, for games)

### Display Connection

- **SCK** → PIN 7 (GPIO 40)
- **MOSI** → PIN 9 (GPIO 14)
- **CS** → PIN 13 (GPIO 5)
- **DC** → PIN 5 (GPIO 6)
- **RST** → PIN 1 (GPIO 3)
- **SD CS** → GPIO 12

