#include "gpio.hh"
#include "RTE_Components.h"
#include CMSIS_device_header

void gpio::init()
{
    /*
     * GPIOA CRL  — PA0–PA7: input pull-up/down (CNF=10, MODE=00 → 0x8 each)
     * GPIOA CRH  — PA9 only: AF push-pull 2 MHz (CNF=10, MODE=10 → 0xA)
     *              all other PA8/PA10–PA15 left as input floating (0x4)
     */
    GPIOA->CRL = 0x88888888U;
    GPIOA->ODR |= 0x00FFU;      /* ODR=1 → pull-up for PA0–PA7 */
    GPIOA->CRH  = 0x444444A4U;  /* PA9 = AF push-pull (USART1 TX) */

    /*
     * GPIOB CRL bit fields (LSB first):
     *   PB0  [3:0]  = 0x8  input pull-up/down
     *   PB1  [7:4]  = 0x8  input pull-up/down
     *   PB2  [11:8] = 0x8  input pull-up/down
     *   PB3  [15:12]= 0x8  input pull-up/down
     *   PB4  [19:16]= 0x2  output push-pull 2 MHz  (trigger)
     *   PB5  [23:20]= 0x4  input floating  (unused)
     *   PB6  [27:24]= 0xE  AF open-drain 2 MHz     (I2C1 SCL)
     *   PB7  [31:28]= 0xE  AF open-drain 2 MHz     (I2C1 SDA)
     */
    GPIOB->CRL = 0xEE428888U;
    GPIOB->ODR = 0x000FU;       /* pull-up PB0–PB3; PB4 starts low */
}

int gpio::readKey(uint8_t idx)
{
    if (idx < 8U) {
        return !(GPIOA->IDR & (1UL << idx));
    } else {
        return !(GPIOB->IDR & (1UL << (idx - 8U)));
    }
}

void gpio::sendTrigger()
{
    GPIOB->BSRR = (1UL << TRIGGER_PIN);           /* set high */
    for (volatile uint32_t i = 0; i < 720U; i++); /* ~10 µs @ 72 MHz */
    GPIOB->BSRR = (1UL << (TRIGGER_PIN + 16));    /* set low  */
}
