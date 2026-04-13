#include "clock.hh"
#include "RTE_Components.h"
#include CMSIS_device_header

void sys_clock::init()
{
    /* APB2: GPIOA, GPIOB, USART1, AFIO */
    RCC->APB2ENR |= RCC_APB2ENR_IOPAEN
                  | RCC_APB2ENR_IOPBEN
                  | RCC_APB2ENR_USART1EN
                  | RCC_APB2ENR_AFIOEN;
    /* APB1: I2C1 */
    RCC->APB1ENR |= RCC_APB1ENR_I2C1EN;
}
