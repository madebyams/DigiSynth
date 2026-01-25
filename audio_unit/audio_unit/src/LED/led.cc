#include "led.hh"

#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_gpio.h"

bool LED::init() {
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    HAL_GPIO_WritePin(this->gpio_port, this->gpio_pin, GPIO_PIN_RESET);

    /*Configure GPIO pin : PA12 */
    GPIO_InitStruct.Pin = this->gpio_pin;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(this->gpio_port, &GPIO_InitStruct);

    return true;
}

void LED::toggle() {
    HAL_GPIO_TogglePin(this->gpio_port, this->gpio_pin);
}