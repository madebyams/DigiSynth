
#include <fmt/base.h>
#include <cstring>

#include "display/display.hh"
#include "display/display_commands.hh"

bool display::init() {
    if(!transport_.init()) {
        fmt::print(stderr, "Failed to start I2C Display connection!\n");
        return false;
    }

    uint32_t p = 2500;
    while(p > 0) {
        p--;
    }


    transport_.write_command(DISPLAY_OFF);
    transport_.write_command(SET_MEMORY_ADDRESSING_MODE); // Set Memory Addressing Mode
    transport_.write_command(MEMORY_ADDRESSING_ARG);      // 00: Horizontal, 01: Vertical, 10: Page (RESET)
    transport_.write_command(SET_PAGE_START_ADDR);        // Set Page Start Address for Page Addressing Mode,0-7
    transport_.write_command(SET_COM_OUTPUT_SCAN_DIR);    // Set COM Output Scan Direction
    transport_.write_command(SET_LOW_COLUMN_ADDR);        // set low column address
    transport_.write_command(SET_HIGH_COLUMN_ADDR);       // set high column address
    transport_.write_command(SET_START_LINE_ADDR);        // set start line address
    transport_.write_command(SET_CONTRAST);               // set contrast control register
    transport_.write_command(CONTRAST_MAX);
    transport_.write_command(SET_SEGMENT_REMAP);          // set segment re-map 0 to 127
    transport_.write_command(SET_NORMAL_DISPLAY);         // set normal display
    transport_.write_command(SET_MULTIPLEX_RATIO);        // set multiplex ratio(1 to 64)
    transport_.write_command(height - 1);
    transport_.write_command(OUTPUT_FOLLOWS_RAM);         // Output follows RAM content
    transport_.write_command(SET_DISPLAY_OFFSET);         // set display offset
    transport_.write_command(DISPLAY_OFFSET_0);           // no offset
    transport_.write_command(SET_DISPLAY_CLK_DIV);        // set display clock divide ratio/oscillator frequency
    transport_.write_command(DISPLAY_CLK_DIV_F0);         // set divide ratio
    transport_.write_command(SET_PRECHARGE_PERIOD);       // set pre-charge period
    transport_.write_command(PRECHARGE_22);
    transport_.write_command(SET_COM_PINS_HW_CONFIG);     // set com pins hardware configuration
    transport_.write_command(COM_PINS_CFG_12);
    transport_.write_command(SET_VCOMH);                  // set vcomh
    transport_.write_command(VCOMH_77PCT_VCC);            // 0x20 -> ~0.77 x Vcc
    transport_.write_command(SET_CHARGE_PUMP);            // set DC-DC enable
    transport_.write_command(CHARGE_PUMP_ENABLE);
    transport_.write_command(DISPLAY_ON);                 // turn on SSD1306
    transport_.write_command(DEACTIVATE_SCROLL);

    fill(Black);
    update_screen();

    x_cursor = 0;
    y_cursor = 0;

    return true;
}

void display::invert() {
    this->inverted = !this->inverted;
}

void display::update_screen() {
    const uint8_t pages = height / 8;
    for (uint8_t m = 0; m < pages; m++) {
        transport_.write_command(SET_PAGE_START_ADDR + m);
        transport_.write_command(SET_LOW_COLUMN_ADDR);
        transport_.write_command(MEMORY_ADDRESSING_ARG);

        /* Write multi data */
        transport_.write_multi_data(&buffer[width * m], width);
    }
}

void display::fill(const color color) {
    std::memset(buffer, (color == Black) ? 0x00 : 0xFF, sizeof(buffer));
}

char display::puts(const char* str, Fonts::FontDef_t* Font, color color) {
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

void display::terminate() {
    this->transport_.terminate();
}

void display::draw_pixel(const uint16_t x, uint16_t y, color color) {
    if (
        x >= width ||
        y >= height
    ) {
        /* Error */
        return;
    }

    /* Check if pixels are inverted */
    if (inverted) {
        color = static_cast<display::color>(!color);
    }

    /* Set color */
    if (color == White) {
        buffer[x + (y / 8) * width] |= 1 << (y % 8);
    } else {
        buffer[x + (y / 8) * width] &= ~(1 << (y % 8));
    }
}

char display::putc(char ch, const Fonts::FontDef_t* Font, const color color) {
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
                draw_pixel(x_cursor + j, (y_cursor + i), static_cast<display::color>(!color));
            }
        }
    }

    /* Increase pointer */
    x_cursor += Font->FontWidth;

    /* Return character written */
    return ch;
}
