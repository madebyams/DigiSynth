#include "Display.hh"
#include <fmt/base.h>
#include <cstring>

bool Display::init() {
    if(!i2c.init()) {
        fmt::print(stderr, "Failed to start I2C Display connection!\n");
        return false;
    }

    uint32_t p = 2500;
    while(p > 0) {
        p--;
    }


    i2c.write_command(Commands::DISPLAY_OFF);
    i2c.write_command(Commands::SET_MEMORY_ADDRESSING_MODE); // Set Memory Addressing Mode
    i2c.write_command(Commands::MEMORY_ADDRESSING_ARG);      // 00: Horizontal, 01: Vertical, 10: Page (RESET)
    i2c.write_command(Commands::SET_PAGE_START_ADDR);        // Set Page Start Address for Page Addressing Mode,0-7
    i2c.write_command(Commands::SET_COM_OUTPUT_SCAN_DIR);    // Set COM Output Scan Direction
    i2c.write_command(Commands::SET_LOW_COLUMN_ADDR);        // set low column address
    i2c.write_command(Commands::SET_HIGH_COLUMN_ADDR);       // set high column address
    i2c.write_command(Commands::SET_START_LINE_ADDR);        // set start line address
    i2c.write_command(Commands::SET_CONTRAST);               // set contrast control register
    i2c.write_command(Commands::CONTRAST_MAX);
    i2c.write_command(Commands::SET_SEGMENT_REMAP);          // set segment re-map 0 to 127
    i2c.write_command(Commands::SET_NORMAL_DISPLAY);         // set normal display
    i2c.write_command(Commands::SET_MULTIPLEX_RATIO);        // set multiplex ratio(1 to 64)
    i2c.write_command(height - 1);
    i2c.write_command(Commands::OUTPUT_FOLLOWS_RAM);         // Output follows RAM content
    i2c.write_command(Commands::SET_DISPLAY_OFFSET);         // set display offset
    i2c.write_command(Commands::DISPLAY_OFFSET_0);           // no offset
    i2c.write_command(Commands::SET_DISPLAY_CLK_DIV);        // set display clock divide ratio/oscillator frequency
    i2c.write_command(Commands::DISPLAY_CLK_DIV_F0);         // set divide ratio
    i2c.write_command(Commands::SET_PRECHARGE_PERIOD);       // set pre-charge period
    i2c.write_command(Commands::PRECHARGE_22);
    i2c.write_command(Commands::SET_COM_PINS_HW_CONFIG);     // set com pins hardware configuration
    i2c.write_command(Commands::COM_PINS_CFG_12);
    i2c.write_command(Commands::SET_VCOMH);                  // set vcomh
    i2c.write_command(Commands::VCOMH_77PCT_VCC);            // 0x20 -> ~0.77 x Vcc
    i2c.write_command(Commands::SET_CHARGE_PUMP);            // set DC-DC enable
    i2c.write_command(Commands::CHARGE_PUMP_ENABLE);
    i2c.write_command(Commands::DISPLAY_ON);                 // turn on SSD1306
    i2c.write_command(Commands::DEACTIVATE_SCROLL);

    fill(Black);
    update_screen();

    x_cursor = 0;
    y_cursor = 0;

    return true;
}

void Display::invert() {
    this->inverted = !this->inverted;
}

void Display::update_screen() {
    const uint8_t pages = height / 8;
    for (uint8_t m = 0; m < pages; m++) {
        i2c.write_command(Commands::SET_PAGE_START_ADDR + m);
        i2c.write_command(Commands::SET_LOW_COLUMN_ADDR);
        i2c.write_command(Commands::MEMORY_ADDRESSING_ARG);

        /* Write multi data */
        i2c.write_multi_data(&buffer[width * m], width);
    }
}

void Display::fill(const Color color) {
    std::memset(buffer, (color == Black) ? 0x00 : 0xFF, sizeof(buffer));
}

char Display::puts(const char* str, Fonts::FontDef_t* Font, Color color) {
    /* Write characters */
    while (*str) {
        /* Write character by character */
        if (putc(*str, Font, color) != *str) {
            /* Return error */
            return *str;
        }

        /* Increase string pointer */
        str++;
    }

    this->update_screen();
    /* Everything OK, zero should be returned */
    return *str;
}

void Display::terminate() {
    this->i2c.terminate();
}

void Display::draw_pixel(const uint16_t x, uint16_t y, Color color) {
    if (
        x >= width ||
        y >= height
    ) {
        /* Error */
        return;
    }

    /* Check if pixels are inverted */
    if (inverted) {
        color = static_cast<Color>(!color);
    }

    /* Set color */
    if (color == White) {
        buffer[x + (y / 8) * width] |= 1 << (y % 8);
    } else {
        buffer[x + (y / 8) * width] &= ~(1 << (y % 8));
    }
}

char Display::putc(char ch, const Fonts::FontDef_t* Font, const Color color) {
    /* Check available space in LCD */
    if (
        width <= (x_cursor + Font->FontWidth) ||
        height <= (y_cursor + Font->FontHeight)
    ) {
        /* Error */
        return 0;
    }

    /* Go through font */
    for (uint32_t i = 0; i < Font->FontHeight; i++) {
        uint32_t b = Font->data[(ch - 32) * Font->FontHeight + i];
        for (uint32_t j = 0; j < Font->FontWidth; j++) {
            if ((b << j) & 0x8000) {
                draw_pixel(x_cursor + j, (y_cursor + i), color);
            } else {
                draw_pixel(x_cursor + j, (y_cursor + i), static_cast<Color>(!color));
            }
        }
    }

    /* Increase pointer */
    x_cursor += Font->FontWidth;

    /* Return character written */
    return ch;
}
