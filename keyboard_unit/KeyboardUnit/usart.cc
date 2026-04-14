#include "usart.hh"
#include "RTE_Components.h"
#include CMSIS_device_header

void usart::init()
{
    USART1->BRR = 0x0271U;                      /* 115200 baud @ 72 MHz APB2 */
    USART1->CR1 = USART_CR1_UE | USART_CR1_TE;
}

void usart::putc(char c)
{
    while (!(USART1->SR & USART_SR_TXE));
    USART1->DR = static_cast<uint8_t>(c);
}

void usart::puts(const char *s)
{
    while (*s) putc(*s++);
}
