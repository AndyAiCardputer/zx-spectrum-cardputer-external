# Firmware Binaries

## ZX_Spectrum_External_v3.138.bin (Latest)

**Version:** 3.138
**Date:** April 2026
**Platform:** M5Stack Cardputer-Adv (ESP32-S3)
**Display:** External ILI9488 (480×320)

### Changes in v3.138
- Fixed: Built-in display backlight control (was incorrectly applied to external display)
- Fixed: Color depth changed from RGB565 to native RGB666 (18-bit) for better compatibility with different ILI9488 display modules
- Improved: README with complete wiring diagram (including VCC, GND, BLK pins)
- Added: Troubleshooting section for common display issues

### Installation

1. Download the `.bin` file
2. Flash with esptool.py:
   ```bash
   esptool.py --chip esp32s3 --port /dev/cu.usbmodem* write_flash 0x10000 ZX_Spectrum_External_v3.138.bin
   ```

## ZX_Spectrum_External_v3.137.bin (Previous)

**Version:** 3.137
**Date:** November 2025

---

### Hardware Requirements

- M5Stack Cardputer-Adv
- External ILI9488 display (480×320) via EXT connector
- SD card (optional, for games)

### Display Connection

| Display Pin | Connect To | Description |
|-------------|-----------|-------------|
| **VCC** | 3.3V or 5V | Power |
| **GND** | GND | Ground |
| **SCK** | GPIO 40 (EXT PIN 7) | SPI Clock |
| **MOSI** | GPIO 14 (EXT PIN 9) | SPI Data |
| **CS** | GPIO 5 (EXT PIN 13) | Chip Select |
| **DC** | GPIO 6 (EXT PIN 5) | Data/Command |
| **RST** | GPIO 3 (EXT PIN 1) | Reset |
| **BLK/LED** | 3.3V | Backlight |
| **SD CS** | GPIO 12 | SD card chip select |

