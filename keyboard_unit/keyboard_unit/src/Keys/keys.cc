#include "keys.hh"
#include "stm32f1xx_hal.h"

void Keys::react(uint16_t GPIO_Pin) {
    switch(GPIO_Pin) {
        case GPIO_PIN_2: {
            uart.print("C\r\n");
            i2c.print("C\r\n");
            break;
        }
    
        case GPIO_PIN_3: {
            uart.print("D\r\n");
            i2c.print("D\r\n");
            break;
        }

        case GPIO_PIN_4: {
            uart.print("E\r\n");
            i2c.print("E\r\n");
            break;
        }
    
        case GPIO_PIN_5: {
            uart.print("F\r\n");
            i2c.print("F\r\n");
            break;
        }
    
        case GPIO_PIN_6: {
            uart.print("G\r\n");
            i2c.print("G\r\n");
            break;
        }

        case GPIO_PIN_7: {
            uart.print("A\r\n");
            i2c.print("A\r\n");
            break;
        }

        case GPIO_PIN_0: {
            uart.print("B\r\n");
            i2c.print("B\r\n");
            break;
        }
    
        case GPIO_PIN_1: {
            uart.print("C#\r\n");
            i2c.print("C#\r\n");
            break;
        }

        case GPIO_PIN_12: {
            uart.print("D#\r\n");
            i2c.print("D#\r\n");
            break;
        }
    
        case GPIO_PIN_13: {
            uart.print("F#\r\n");
            i2c.print("F#\r\n");
            break;
        }
    
        case GPIO_PIN_14: {
            uart.print("G#\r\n");
            i2c.print("G#\r\n");
            break;
        }

        case GPIO_PIN_15: {
            uart.print("A#\r\n");
            i2c.print("A#\r\n");
            break;
        }
    }
}
