#ifndef LED_HH
#define LED_HH

#include "stm32f401xc.h"
#include <cstdint>

class LED {
    GPIO_TypeDef* gpio_port;
    uint16_t gpio_pin;
public:
    LED(GPIO_TypeDef* gpio_port, uint16_t gpio_pin)
        : gpio_port(gpio_port), gpio_pin(gpio_pin) {}
    bool init();
    void toggle();
};

#endif