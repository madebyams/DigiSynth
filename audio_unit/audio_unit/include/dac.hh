#ifndef DAC_HH
#define DAC_HH

#include "stm32f4xx_hal.h"

class DAC {
    I2S_HandleTypeDef hi2s2;

public:
    bool init();
};

#endif