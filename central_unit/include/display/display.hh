#ifndef DISPLAY_HH
#define DISPLAY_HH

#include <string>

#include "display_transport.hh"
#include "Fonts/fonts.hh"

using transport = display_transport;

class display {
public:
    enum color {
        Black = 0x00,
        White = 0x01
    };

    explicit display(i2c& i2c) : transport_(i2c) {}
    bool init();
    void invert();
    void fill(color color);
    char puts(const char* str, Fonts::FontDef_t* Font, color color);
    void terminate();

private:
    bool inverted = false;
    uint32_t x_cursor = 0;
    uint32_t y_cursor = 0;
    static constexpr uint32_t width = 128;
    static constexpr uint32_t height = 32;
    uint8_t buffer[width * height / 8] = {};

    display_transport transport_;

    void draw_pixel(uint16_t x, uint16_t y, color color);
    char putc(char ch, const Fonts::FontDef_t* Font, color color);
    void update_screen();
};

#endif
