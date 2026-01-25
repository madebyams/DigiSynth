#ifndef ADSR_HH
#define ADSR_HH

#include "stm32f4xx_hal.h"

class ADSR {
    ADC_HandleTypeDef hadc1;
public:
    bool init();
};

#endif