#ifndef KEYS_HH
#define KEYS_HH

#include <cstdint>

#include "i2c.hh"

class Keys {
    I2C& i2c;
public:
    explicit Keys(I2C& i2c)
        : i2c(i2c) {}

    void react(uint16_t GPIO_Pin);
};

#endif