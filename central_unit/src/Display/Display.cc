#include "Display.hh"
#include <iostream>
#include <cstring>
#include <pigpio.h>

bool Display::init() {
    if(gpioInitialise() < 0) {
        std::cerr << "Failed to initailize GPIO!\n";
        return false; 
    }

    i2c_handle = i2cOpen(BUS, ADDRESS, 0);
    if(i2c_handle < 0) {
        std::cerr << "Failed to start I2C Display connection!\n";
        gpioTerminate();
        return false;
    }

    uint32_t p = 2500;
    while(p > 0) {
        p--;
    }

    this->write_command(Commands::DISPLAY_OFF);
    this->write_command(Commands::SET_MEMORY_ADDRESSING_MODE); // Set Memory Addressing Mode
    this->write_command(Commands::MEMORY_ADDRESSING_ARG);      // 00: Horizontal, 01: Vertical, 10: Page (RESET)
    this->write_command(Commands::SET_PAGE_START_ADDR);        // Set Page Start Address for Page Addressing Mode,0-7
    this->write_command(Commands::SET_COM_OUTPUT_SCAN_DIR);    // Set COM Output Scan Direction
    this->write_command(Commands::SET_LOW_COLUMN_ADDR);        // set low column address
    this->write_command(Commands::SET_HIGH_COLUMN_ADDR);       // set high column address
    this->write_command(Commands::SET_START_LINE_ADDR);        // set start line address
    this->write_command(Commands::SET_CONTRAST);               // set contrast control register
    this->write_command(Commands::CONTRAST_MAX);
    this->write_command(Commands::SET_SEGMENT_REMAP);          // set segment re-map 0 to 127
    this->write_command(Commands::SET_NORMAL_DISPLAY);         // set normal display
    this->write_command(Commands::SET_MULTIPLEX_RATIO);        // set multiplex ratio(1 to 64)
    this->write_command(height - 1); //
    this->write_command(Commands::OUTPUT_FOLLOWS_RAM);         // Output follows RAM content
    this->write_command(Commands::SET_DISPLAY_OFFSET);         // set display offset
    this->write_command(Commands::DISPLAY_OFFSET_0);           // no offset
    this->write_command(Commands::SET_DISPLAY_CLK_DIV);        // set display clock divide ratio/oscillator frequency
    this->write_command(Commands::DISPLAY_CLK_DIV_F0);         // set divide ratio
    this->write_command(Commands::SET_PRECHARGE_PERIOD);       // set pre-charge period
    this->write_command(Commands::PRECHARGE_22);
    this->write_command(Commands::SET_COM_PINS_HW_CONFIG);     // set com pins hardware configuration
    this->write_command(Commands::COM_PINS_CFG_12);
    this->write_command(Commands::SET_VCOMH);                  // set vcomh
    this->write_command(Commands::VCOMH_77PCT_VCC);            // 0x20 -> ~0.77 x Vcc
    this->write_command(Commands::SET_CHARGE_PUMP);            // set DC-DC enable
    this->write_command(Commands::CHARGE_PUMP_ENABLE);
    this->write_command(Commands::DISPLAY_ON);                 // turn on SSD1306
    this->write_command(Commands::DEACTIVATE_SCROLL);

    fill(Black);
    update_screen();

    return true;
}

void Display::invert() {
    this->inverted = !this->inverted;
}

void Display::update_screen() const {
    const uint8_t pages = height / 8;
    for (uint8_t m = 0; m < pages; m++) {
        write_command(0xB0 + m);
        write_command(0x00);
        write_command(0x10);

        /* Write multi data */
        write_multi(0x40, &buffer[width * m], width);
    }
}

void Display::fill(const Color color) {
    std::memset(buffer, (color == Black) ? 0x00 : 0xFF, sizeof(buffer));
}

char Display::puts(const char* str, Fonts::FontDef_t* Font, const Color color) {
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

    /* Everything OK, zero should be returned */
    return *str;
}

void Display::terminate() const {
    i2cClose(i2c_handle);
    gpioTerminate();
}

void Display::write_command(const uint8_t command) const {
    i2cWriteByteData(i2c_handle, 0x00, command);
}

void Display::write_multi(uint8_t reg, const uint8_t* data, uint16_t count) const {
    char dt[256];
    uint8_t i;
    for(i = 0; i < count; i++)
        dt[1] = data[i];

    i2cWriteBlockData(i2c_handle, reg, dt, count);
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