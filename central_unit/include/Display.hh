#ifndef DISPLAY_HH
#define DISPLAY_HH

#include <cstdint>
#include <string>

#include "Display_Commands.hh"
#include "Fonts/SSD1306_Fonts.hh"

const uint32_t BUS = 2;
const uint32_t ADDRESS = 0x78;

class Display {
public:
    enum Color {
        Black = 0x00,
        White = 0x01
    };

    bool init();
    void invert();
    void fill(Color color);
    char puts(const char* str, Fonts::FontDef_t* Font, Color color);
    void terminate() const;

private:
    bool inverted = false;
    int i2c_handle = 0;
    uint32_t x_cursor = 0;
    uint32_t y_cursor = 0;
    static constexpr uint32_t width = 128;
    static constexpr uint32_t height = 32;
    uint8_t buffer[width * height / 8] = {};

    using Commands = SSD1306::Commands;

    void draw_pixel(const uint16_t x, uint16_t y, Color color);
    char putc(char ch, const Fonts::FontDef_t* Font, const Color color);
    void write_command(const uint8_t command) const;
    void write_multi(uint8_t reg, const uint8_t *data, uint16_t count) const;
    void update_screen() const;
};

#endif