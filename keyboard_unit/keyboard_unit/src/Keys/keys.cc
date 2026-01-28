#include "keys.hh"
#include "stm32f1xx_hal.h"

void Keys::react(uint16_t GPIO_Pin) {
    switch(GPIO_Pin) {
        case GPIO_PIN_2: {
            i2c.print("C\n");
            break;
        }
    
        case GPIO_PIN_3: {
            i2c.print("D\n");
            break;
        }

        case GPIO_PIN_4: {
            i2c.print("E\n");
            break;
        }
    
        case GPIO_PIN_5: {
            i2c.print("F\n");
            break;
        }
    
        case GPIO_PIN_6: {
            i2c.print("G\n");
            break;
        }

        case GPIO_PIN_7: {
            i2c.print("A\n");
            break;
        }

        case GPIO_PIN_0: {
            i2c.print("B\n");
            break;
        }
    
        case GPIO_PIN_1: {
            i2c.print("C#\n");
            break;
        }

        case GPIO_PIN_12: {
            i2c.print("D#\n");
            break;
        }
    
        case GPIO_PIN_13: {
            i2c.print("F#\n");
            break;
        }
    
        case GPIO_PIN_14: {
            i2c.print("G#\n");
            break;
        }

        case GPIO_PIN_15: {
            i2c.print("A#\n");
            break;
        }
    }
}