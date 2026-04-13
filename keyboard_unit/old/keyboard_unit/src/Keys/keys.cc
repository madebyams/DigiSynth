#include "keys.hh"
#include "stm32f1xx_hal.h"
#include "stm32f1xx_hal_gpio.h"

extern "C" void trigger_external_interupt(const UART& uart) {
    uart.print("Interrupted");
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_9, GPIO_PIN_SET);
    HAL_Delay(2);
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_9, GPIO_PIN_RESET);
    HAL_Delay(2);
}

extern "C" void Keys::react(uint16_t GPIO_Pin) const {
    switch(GPIO_Pin) {
        case GPIO_PIN_2: {
            this->uart.print("C\r\n");
            trigger_external_interupt(this->uart);
            //i2c.print("C\r\n");
            break;
        }
    
        case GPIO_PIN_3: {
            this->uart.print("D\r\n");
            trigger_external_interupt(this->uart);
            //i2c.print("D\r\n");
            break;
        }

        case GPIO_PIN_4: {
            this->uart.print("E\r\n");
            trigger_external_interupt(this->uart);
            //i2c.print("E\r\n");
            break;
        }
    
        case GPIO_PIN_5: {
            this->uart.print("F\r\n");
            trigger_external_interupt(this->uart);
            //i2c.print("F\r\n");
            break;
        }
    
        case GPIO_PIN_6: {
            this->uart.print("G\r\n");
            trigger_external_interupt(this->uart);
            //i2c.print("G\r\n");
            break;
        }

        case GPIO_PIN_7: {
            this->uart.print("A\r\n");
            trigger_external_interupt(this->uart);
            //i2c.print("A\r\n");
            break;
        }

        case GPIO_PIN_0: {
            this->uart.print("B\r\n");
            trigger_external_interupt(this->uart);
            //i2c.print("B\r\n");
            break;
        }
    
        case GPIO_PIN_1: {
            this->uart.print("C#\r\n");
            trigger_external_interupt(this->uart);
            //i2c.print("C#\r\n");
            break;
        }

        case GPIO_PIN_12: {
            this->uart.print("D#\r\n");
            trigger_external_interupt(this->uart);
            //i2c.print("D#\r\n");
            break;
        }
    
        case GPIO_PIN_13: {
            this->uart.print("F#\r\n");
            trigger_external_interupt(this->uart);
            //i2c.print("F#\r\n");
            break;
        }
    
        case GPIO_PIN_14: {
            this->uart.print("G#\r\n");
            trigger_external_interupt(this->uart);
            //i2c.print("G#\r\n");
            break;
        }

        case GPIO_PIN_15: {
            this->uart.print("A#\r\n");
            trigger_external_interupt(this->uart);
            //i2c.print("A#\r\n");
            break;
        }
    }
}


extern "C" void EXTI0_IRQHandler(void) {
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