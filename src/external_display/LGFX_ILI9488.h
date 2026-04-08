#ifndef LGFX_ILI9488_H
#define LGFX_ILI9488_H

#include <M5GFX.h>
#include <lgfx/v1/panel/Panel_LCD.hpp>

// SPI pins for external ILI9488 display
#define PIN_SCK   40  // SCK  -> EXT PIN 7
#define PIN_MOSI  14  // MOSI -> EXT PIN 9
#define PIN_MISO  39  // MISO (not used for display, but for SD)
#define LCD_CS    5   // CS   -> EXT PIN 13
#define LCD_DC    6   // DC   -> EXT PIN 5
#define LCD_RST   3   // RST  -> EXT PIN 1

// SD card CS
#define SD_CS     12

// Local Panel_ILI9488 definition
struct Panel_ILI9488_Local : public lgfx::v1::Panel_LCD {
    Panel_ILI9488_Local(void) {
        // Panel config: 320×480 (physical 480x320, rotated)
        _cfg.memory_width  = _cfg.panel_width  = 320;
        _cfg.memory_height = _cfg.panel_height = 480;
    }

    void setColorDepth_impl(lgfx::v1::color_depth_t depth) override {
        // ILI9488 over SPI natively supports 18-bit (RGB666, 3 bytes/pixel)
        // RGB565 via SPI may not work reliably on all modules/library versions
        _write_depth = lgfx::v1::color_depth_t::rgb888_3Byte;
        _read_depth  = lgfx::v1::color_depth_t::rgb888_3Byte;
    }

protected:
    static constexpr uint8_t CMD_FRMCTR1 = 0xB1;
    static constexpr uint8_t CMD_INVCTR  = 0xB4;
    static constexpr uint8_t CMD_DFUNCTR = 0xB6;
    static constexpr uint8_t CMD_ETMOD   = 0xB7;
    static constexpr uint8_t CMD_PWCTR1  = 0xC0;
    static constexpr uint8_t CMD_PWCTR2  = 0xC1;
    static constexpr uint8_t CMD_VMCTR   = 0xC5;
    static constexpr uint8_t CMD_ADJCTL3 = 0xF7;

    const uint8_t* getInitCommands(uint8_t listno) const override {
        static constexpr uint8_t list0[] = {
            CMD_PWCTR1,  2, 0x17, 0x15,
            CMD_PWCTR2,  1, 0x41,
            CMD_VMCTR ,  3, 0x00, 0x12, 0x80,
            CMD_FRMCTR1, 1, 0xA0,
            CMD_INVCTR,  1, 0x02,
            CMD_DFUNCTR, 3, 0x02, 0x22, 0x3B,
            CMD_ETMOD,   1, 0xC6,
            CMD_ADJCTL3, 4, 0xA9, 0x51, 0x2C, 0x82,
            CMD_SLPOUT , 0+CMD_INIT_DELAY, 120,
            CMD_IDMOFF , 0,
            CMD_DISPON , 0+CMD_INIT_DELAY, 100,
            0xFF,0xFF,
        };
        switch (listno) {
        case 0: return list0;
        default: return nullptr;
        }
    }
};

// External ILI9488 display configuration
class LGFX_ILI9488 : public lgfx::v1::LGFX_Device {
    Panel_ILI9488_Local panel;
    lgfx::v1::Bus_SPI   bus;

public:
    LGFX_ILI9488() {
        // --- SPI bus ---
        auto b = bus.config();
        b.spi_host   = SPI3_HOST;     // Same host as SD (HSPI)
        b.spi_mode   = 0;
        b.freq_write = 50000000;      // ✅ 50 MHz (оптимально: 24 FPS, стабильно с DMA)
        b.freq_read  = 16000000;
        b.spi_3wire  = true;          // 3-wire SPI (without MISO)
        b.use_lock   = true;          // Transaction locking enabled
        b.dma_channel = 1;            // ✅ DMA enabled for better performance (channel 1, SD uses channel 0 or different)

        b.pin_sclk = PIN_SCK;        // SCK  -> PIN 7
        b.pin_mosi = PIN_MOSI;       // MOSI -> PIN 9
        b.pin_miso = -1;             // Explicit -1, since 3-wire
        b.pin_dc   = LCD_DC;         // DC   -> PIN 5
        
        bus.config(b);
        panel.setBus(&bus);

        // --- Panel config ---
        auto p = panel.config();
        p.pin_cs    = LCD_CS;        // CS   -> PIN 13
        p.pin_rst   = LCD_RST;       // RST  -> PIN 1
        p.bus_shared = true;         // IMPORTANT for shared SPI
        p.readable   = false;        // Display not readable via MISO
        p.invert     = false;
        p.rgb_order  = false;
        p.dlen_16bit = false;
        p.memory_width  = 320;
        p.memory_height = 480;
        p.panel_width   = 320;
        p.panel_height  = 480;
        p.offset_x = 0;
        p.offset_y = 0;
        p.offset_rotation = 0;
        p.dummy_read_pixel = 8;
        p.dummy_read_bits = 1;
        panel.config(p);

        setPanel(&panel);
    }
};

// Global external display object
extern LGFX_ILI9488 externalDisplay;

// Function to safely release LCD before SD operations
inline void lcd_quiesce() {
    externalDisplay.endWrite();
    externalDisplay.waitDisplay();
    digitalWrite(LCD_CS, HIGH);
}

#endif // LGFX_ILI9488_H

