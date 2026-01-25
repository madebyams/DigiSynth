#ifndef DMA_HH
#define DMA_HH

#include "stm32f4xx_hal.h"

class DMA {
    DMA_HandleTypeDef hdma_spi2_tx;
public:
    bool init();
};

#endif