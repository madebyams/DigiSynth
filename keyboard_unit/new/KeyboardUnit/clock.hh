#pragma once

class sys_clock {
public:
    /* Enable APB1/APB2 sys_clocks for GPIOA, GPIOB, USART1, AFIO, I2C1 */
    void init();
};
