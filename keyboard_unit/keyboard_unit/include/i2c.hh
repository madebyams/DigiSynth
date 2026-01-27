#ifndef I2C_HH
#define I2C_HH

#include "stm32f1xx_hal.h"

class I2C {
    I2C_HandleTypeDef hi2c1;
public:
    bool init();
};

#endif