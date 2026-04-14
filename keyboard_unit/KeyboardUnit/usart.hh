#pragma once

/*
 * USART1 driver — PA9 TX, 115200 8N1
 * APB2 = 72 MHz → BRR = 72 000 000 / 115 200 = 625 = 0x0271
 */
class usart {
public:
    void init();
    void putc(char c);
    void puts(const char *s);
};
