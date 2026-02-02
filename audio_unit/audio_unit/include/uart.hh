#pragma once

#include <stm32f4xx_hal.h>
#include <string>

class UART {
    UART_HandleTypeDef huart1;
public:
    bool init();
    void print(std::string message);
};