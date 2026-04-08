# ZX Spectrum Emulator - External Display

ZX Spectrum 48K emulator for M5Stack Cardputer-Adv with external ILI9488 display (480×320).

## Features

- ✅ ZX Spectrum 48K emulation
- ✅ External ILI9488 display (480×320)
- ✅ Optimized rendering with DMA
- ✅ SD card support for ROMs and games
- ✅ Keyboard input support
- ✅ Audio support (Beeper) with dual-core processing
- ✅ TAP, .SNA, and .Z80 file loading
- ✅ Screenshot functionality (BMP format)
- ✅ Native 256×192 rendering centered on 480×320 display

## Hardware Requirements

- M5Stack Cardputer-Adv
- External ILI9488 display (480×320) via EXT connector
- SD card (optional, for games)

## Display Connection

External ILI9488 display connects via EXT 2.54-14P connector:

| Display Pin | Connect To | Description |
|-------------|-----------|-------------|
| **VCC** | 3.3V or 5V | Power (check your module) |
| **GND** | GND | Ground |
| **SCK** | GPIO 40 (EXT PIN 7) | SPI Clock |
| **MOSI** | GPIO 14 (EXT PIN 9) | SPI Data |
| **CS** | GPIO 5 (EXT PIN 13) | Chip Select |
| **DC** | GPIO 6 (EXT PIN 5) | Data/Command |
| **RST** | GPIO 3 (EXT PIN 1) | Reset |
| **BLK/LED** | 3.3V | Backlight (connect to 3.3V for always-on) |

SD card shares SPI bus with display:
- **SD CS** → GPIO 12

## Technical Specifications

- **CPU:** ESP32-S3 @ 240 MHz
- **Z80 Emulation:** 3.5 MHz
- **Memory:** 16 KB ROM + 48 KB RAM
- **Display:** ILI9488 480×320, RGB666 (18-bit), 50 MHz SPI with DMA
- **Audio:** 16 kHz I2S, double buffering, separate task on Core 1
- **SD Card:** 40 MHz High Speed, shared SPI bus
- **File Support:** .SNA, .Z80, .TAP formats
- **Screenshots:** BMP 256×192, 24-bit

## Performance

- **FPS:** Stable 40 FPS
- **Rendering:** Every 5th frame (balance between FPS and quality)
- **Memory Usage:** ~9.7% RAM, ~21.8% Flash
- **Audio:** Separate task on Core 1 for smooth playback

## Project Status

✅ **Fully Working** - All features implemented and tested.

## Key Features

1. ✅ External display support (LGFX_ILI9488)
2. ✅ Shared SPI bus for display and SD card
3. ✅ Optimized rendering (native 256×192, centered on 480×320)
4. ✅ Dual-core audio processing
5. ✅ File browser with filters (.SNA/.TAP/.Z80)
6. ✅ Screenshot capture (BMP format)
7. ✅ Menu system with scaled UI (2x for better visibility)
8. ✅ Game folder management (/ZXgames/)

## Installation

1. Clone this repository
2. Open project in PlatformIO
3. Connect external ILI9488 display as specified
4. Insert SD card with games in `/ZXgames/` folder
5. Build and upload to Cardputer-Adv

## Usage

- **Opt+ESC:** Open main menu
- **TAB:** Pause/Resume emulation
- **Opt+M:** Toggle sound
- **Opt+Up/Down:** Adjust volume
- **Opt+S:** Take screenshot
- **Arrow keys:** Navigate menus
- **Enter:** Select/Load
- **ESC:** Back

## Troubleshooting

### Display is blank / white screen
- Check all wiring connections (VCC, GND, SCK, MOSI, CS, DC, RST)
- Make sure BLK/LED pin is connected to 3.3V (backlight)
- Clean the contacts on the EXT connector
- Verify your display module is ILI9488 (480×320)

### Display image is mirrored or wrong orientation
Different ILI9488 modules may have different default orientations. To fix:
1. Open `src/main.cpp`
2. Find the line: `externalDisplay.setRotation(3);`
3. Try changing the value:
   - `0` = Portrait
   - `1` = Landscape (90°)
   - `2` = Portrait (180°)
   - `3` = Landscape (270°) -- default
4. Build and upload again

### No backlight
- Some ILI9488 modules have a BLK/LED pin that must be connected to 3.3V
- Some modules have backlight always on (internally connected)
- If your module has a BLK pin, connect it to 3.3V or 5V

### SD card not detected
- SD card must be FAT32 formatted
- Place game files in `/ZXgames/` folder on the SD card
- Supported formats: .SNA, .Z80, .TAP

## Based On

- Original ZX Spectrum emulator: `github_release` project
- External display code: `nes_cardputer_adv_external` project
- Z80 Core: Santiago Romero Iglesias
- Original ESP32 Rainbow: atomic14/esp32-zxspectrum

## Credits

- **Port to Cardputer-Adv:** AndyAiCardputer
- **Development:** AI Assistant (Claude)
- **Sound improvements:** ChatGPT (GPT-4)

## License

See LICENSE file for details.
