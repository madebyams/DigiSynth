#include "gpio.hh"
#include "stm32f4xx_hal.h"


bool GPIO::init() {
    __HAL_RCC_GPIOH_CLK_ENABLE();
    __HAL_RCC_GPIOA_CLK_ENABLE();
    __HAL_RCC_GPIOB_CLK_ENABLE();

    return true;
}