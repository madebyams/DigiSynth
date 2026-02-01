#ifndef KEYS_HH
#define KEYS_HH

#include <cstdint>

#include "i2c.hh"
#include "uart.hh"

class Keys {
    UART& uart;
    I2C& i2c;
public:
    explicit Keys(UART& uart, I2C& i2c)
        : uart(uart), i2c(i2c) {}

    void react(uint16_t GPIO_Pin);
};

#endif