#ifndef KEYS_HH
#define KEYS_HH

#include <cstdint>

#include "i2c.hh"
#include "uart.hh"

class Keys {
    UART& uart;
    I2C& i2c;
public:
    explicit Keys(UART& uart, I2C& i2c)
        : uart(uart), i2c(i2c) {}

    void react(uint16_t GPIO_Pin);
};

extern "C" {
    void EXTI0_IRQHandler(void);
    void EXTI1_IRQHandler(void);
    void EXTI2_IRQHandler(void);
    void EXTI3_IRQHandler(void);
    void EXTI4_IRQHandler(void);
    void EXTI9_5_IRQHandler(void);
    void EXTI15_10_IRQHandler(void);
}
#endif