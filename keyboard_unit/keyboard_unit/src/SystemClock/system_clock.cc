#include <stm32f1xx.h>

#include "system_clock.hh"
#include "stm32f1xx_hal_def.h"
#include "stm32f1xx_hal_flash.h"
#include "stm32f1xx_hal_rcc.h"
#include "stm32f1xx_hal_rcc_ex.h"

bool init_oscillator() {
    RCC_OscInitTypeDef oscillator_init = {
        .OscillatorType = RCC_OSCILLATORTYPE_HSI,
        .HSIState = RCC_HSI_ON,
        .HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT,
        .PLL = {
            .PLLState = RCC_PLL_NONE
        }
    };

    return HAL_RCC_OscConfig(&oscillator_init) == HAL_OK;
}

bool init_clock() {
    RCC_ClkInitTypeDef clock_init = {
        .ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2,
        .SYSCLKSource = RCC_SYSCLKSOURCE_HSI,
        .AHBCLKDivider = RCC_SYSCLK_DIV1,
        .APB1CLKDivider = RCC_HCLK_DIV1,
        .APB2CLKDivider = RCC_HCLK_DIV1
    };

    return HAL_RCC_ClockConfig(&clock_init, FLASH_LATENCY_0) == HAL_OK;
}

bool SystemClock::init() {
    auto osc_init = init_oscillator();
    auto clock_init = init_clock();

    return osc_init && clock_init;
}