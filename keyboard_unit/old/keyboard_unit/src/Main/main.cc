#include <stm32f1xx_hal.h>

#include "main.h"
#include "gpio.hh"
#include "i2c.hh"
#include "keys.hh"
#include "system_clock.hh"
#include "uart.hh"

static SystemClock clock;
static I2C i2c;
static UART uart;
static Keys keys(uart, i2c);

int main(void) {
  HAL_Init();

  if(!clock.init()) {
    Error_Handler();
  }

  if (!GPIO::init()) {
    Error_Handler();
  }

  if(!uart.init()) {
    Error_Handler();
  }

  if(!i2c.init()) {
    Error_Handler();
  }

  while (true){}
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin) {
    keys.react(GPIO_Pin);
}

void I2C1_EV_IRQHandler(void) {
  HAL_I2C_EV_IRQHandler(i2c.get_handler());
}


/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}
