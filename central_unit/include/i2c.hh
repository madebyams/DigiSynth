//
// Created by Amsakan on 29.01.26.
//

#ifndef CENTRAL_UNIT_I2C_HPP
#define CENTRAL_UNIT_I2C_HPP
#include <cstdint>

class i2c {
    int handle_ = 0;
    bool initialized_ = false;
public:
    bool init();
    bool select(uint8_t address);
    bool transmit(uint8_t* data, uint32_t count);
    bool terminate();
};
#endif //CENTRAL_UNIT_I2C_HPP