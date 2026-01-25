#include "debug.hh"
#include "stm32f4xx_hal.h"

bool Debug::init() {
    HAL_DBGMCU_EnableDBGSleepMode();
    HAL_DBGMCU_EnableDBGStopMode();
    HAL_DBGMCU_EnableDBGStandbyMode();

    return true;
}