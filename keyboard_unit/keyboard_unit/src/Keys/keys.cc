#include "keys.hh"
#include "stm32f1xx_hal.h"
#include "stm32f1xx_hal_gpio.h"

extern "C" void Keys::react(uint16_t GPIO_Pin) {
    switch(GPIO_Pin) {
        case GPIO_PIN_2: {
            uart.print("C\r\n");
            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_9, GPIO_PIN_SET);
            //i2c.print("C\r\n");
            break;
        }
    
        case GPIO_PIN_3: {
            uart.print("D\r\n");
            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_9, GPIO_PIN_SET);
            //i2c.print("D\r\n");
            break;
        }

        case GPIO_PIN_4: {
            uart.print("E\r\n");
            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_9, GPIO_PIN_SET);
            //i2c.print("E\r\n");
            break;
        }
    
        case GPIO_PIN_5: {
            uart.print("F\r\n");
            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_9, GPIO_PIN_SET);
            //i2c.print("F\r\n");
            break;
        }
    
        case GPIO_PIN_6: {
            uart.print("G\r\n");
            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_9, GPIO_PIN_SET);
            //i2c.print("G\r\n");
            break;
        }

        case GPIO_PIN_7: {
            uart.print("A\r\n");
            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_9, GPIO_PIN_SET);
            //i2c.print("A\r\n");
            break;
        }

        case GPIO_PIN_0: {
            uart.print("B\r\n");
            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_9, GPIO_PIN_SET);
            //i2c.print("B\r\n");
            break;
        }
    
        case GPIO_PIN_1: {
            uart.print("C#\r\n");
            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_9, GPIO_PIN_SET);
            //i2c.print("C#\r\n");
            break;
        }

        case GPIO_PIN_12: {
            uart.print("D#\r\n");
            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_9, GPIO_PIN_SET);
            //i2c.print("D#\r\n");
            break;
        }
    
        case GPIO_PIN_13: {
            uart.print("F#\r\n");
            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_9, GPIO_PIN_SET);
            //i2c.print("F#\r\n");
            break;
        }
    
        case GPIO_PIN_14: {
            uart.print("G#\r\n");
            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_9, GPIO_PIN_SET);
            //i2c.print("G#\r\n");
            break;
        }

        case GPIO_PIN_15: {
            uart.print("A#\r\n");
            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_9, GPIO_PIN_SET);
            //i2c.print("A#\r\n");
            break;
        }
    }
}


extern "C" extern "C" void EXTI0_IRQHandler(void) {
  HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_0);
}


extern "C" void EXTI1_IRQHandler(void) {
  HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_1);
}


extern "C" void EXTI2_IRQHandler(void) {
  HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_2);
}


extern "C" void EXTI3_IRQHandler(void) {
  HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_3);
}


extern "C" void EXTI4_IRQHandler(void) {
  HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_4);
}


extern "C" void EXTI9_5_IRQHandler(void) {
  HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_5);
  HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_6);
  HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_7);
}


extern "C" void EXTI15_10_IRQHandler(void) {
  HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_12);
  HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_13);
  HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_14);
  HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_15);
}