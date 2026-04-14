#pragma once

#include <stdint.h>

/*
 * I2C1 master driver — PB6 SCL, PB7 SDA
 * APB1 = 36 MHz, standard mode 100 kHz
 *   CCR   = 36 000 000 / (2 × 100 000) = 180
 *   TRISE = 36 + 1 = 37
 *
 * Note: external 4.7 kΩ pull-up resistors are required on SCL and SDA.
 */
class i2c {
public:
    static constexpr uint8_t  SLAVE_ADDR = 0x20;   /* 7-bit slave address */
    static constexpr uint32_t TIMEOUT    = 10000U;  /* loop iterations     */

    void init();

    /* Send note index (0–11) to slave. Returns 0 on success, -1 on error. */
    int sendNote(uint8_t note);
};
