#ifndef I2C_HH
#define I2C_HH

#include <string>
#include "stm32f1xx_hal.h"
#include "stm32f1xx_hal_i2c.h"

class I2C {
    I2C_HandleTypeDef hi2c1;
public:
    bool init();
    void print(std::string text);
    I2C_HandleTypeDef* get_handler();
};

#endif