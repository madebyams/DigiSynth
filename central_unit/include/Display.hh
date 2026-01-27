#ifndef DISPLAY_HH
#define DISPLAY_HH

#include <string>

#include "SSD1306/SSD1306_I2C.hh"
#include "SSD1306/SSD1306_Commands.hh"
#include "SSD1306/Fonts/SSD1306_Fonts.hh"

const uint32_t ADDRESS = 0x3c;

class Display {
public:
    enum Color {
        Black = 0x00,
        White = 0x01
    };

    explicit Display() : i2c(ADDRESS) {}
    bool init();
    void invert();
    void fill(Color color);
    char puts(const char* str, Fonts::FontDef_t* Font, Color color);
    void terminate();

private:
    bool inverted = false;
    uint32_t x_cursor = 0;
    uint32_t y_cursor = 0;
    static constexpr uint32_t width = 128;
    static constexpr uint32_t height = 32;
    uint8_t buffer[width * height / 8] = {};

    using I2C = SSD1306::I2C;
    I2C i2c;

    using Commands = SSD1306::Commands;

    void draw_pixel(uint16_t x, uint16_t y, Color color);
    char putc(char ch, const Fonts::FontDef_t* Font, Color color);
    void update_screen();
};

#endif
