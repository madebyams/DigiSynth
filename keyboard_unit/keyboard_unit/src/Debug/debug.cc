#include <stm32f1xx_hal.h>
#include "debug.hh"
#include "stm32f1xx_hal_gpio_ex.h"
#include "stm32f1xx_hal_rcc.h"

void Debug::init() {
    __HAL_RCC_GPIOA_CLK_ENABLE();
    __HAL_RCC_AFIO_CLK_ENABLE();
    __HAL_AFIO_REMAP_SWJ_NOJTAG();

    HAL_DBGMCU_EnableDBGSleepMode();
    HAL_DBGMCU_EnableDBGStopMode();
    HAL_DBGMCU_EnableDBGStandbyMode();
}