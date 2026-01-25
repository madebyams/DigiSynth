#ifndef MESSAGE_BUS_HH
#define MESSAGE_BUS_HH

#include "stm32f4xx_hal.h"


class MessageBus {
    SPI_HandleTypeDef hspi1;

public:
    bool init();
};

#endif