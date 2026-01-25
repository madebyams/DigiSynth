#include "main.h"
#include "adsr.hh"
#include "dac.hh"
#include "debug.hh"
#include "dma.hh"
#include "gpio.hh"
#include "led.hh"
#include "message_bus.hh"
#include "stm32f4xx_hal.h"
#include "system_clock.hh"

SystemClock clock;
ADSR adsr;
DAC dac;
DMA dma;
LED led(GPIOA, GPIO_PIN_12);
MessageBus message_bus;

int main(void) {
  HAL_Init();


  if(!clock.init()) {
    Error_Handler();
  }

  if (!GPIO::init()) {
    Error_Handler();
  }

  if(!Debug::init()) {
    Error_Handler();
  }

  if(!dma.init()) {
    Error_Handler();
  }

  if(!adsr.init()) {
    Error_Handler();
  }

  if(!dac.init()) {
    Error_Handler();
  }

  if(!message_bus.init()) {
    Error_Handler();
  }

  if(!led.init()) {
    Error_Handler();
  }

  led.toggle();
  dac.play_sine(440.0f);

  while (true) {}
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
  led.toggle();
  while (true)
  {}
  /* USER CODE END Error_Handler_Debug */
}
#ifdef USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
