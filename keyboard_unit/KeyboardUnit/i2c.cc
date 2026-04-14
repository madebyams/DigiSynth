#include "i2c.hh"
#include "RTE_Components.h"
#include CMSIS_device_header

void i2c::init()
{
    I2C1->CR1   = I2C_CR1_SWRST; /* reset peripheral */
    I2C1->CR1   = 0;
    I2C1->CR2   = 36U;            /* FREQ = APB1 in MHz */
    I2C1->CCR   = 180U;           /* standard mode 100 kHz */
    I2C1->TRISE = 37U;
    I2C1->CR1   = I2C_CR1_PE;     /* enable */
}

int i2c::sendNote(uint8_t note)
{
    uint32_t timeout;

    /* Wait for bus to become free */
    timeout = TIMEOUT;
    while ((I2C1->SR2 & I2C_SR2_BUSY) && --timeout);
    if (!timeout) return -1;

    /* START condition */
    I2C1->CR1 |= I2C_CR1_START;
    timeout = TIMEOUT;
    while (!(I2C1->SR1 & I2C_SR1_SB) && --timeout);
    if (!timeout) return -1;

    /* Slave address + write bit */
    I2C1->DR = static_cast<uint8_t>(SLAVE_ADDR << 1);
    timeout = TIMEOUT;
    while (!(I2C1->SR1 & I2C_SR1_ADDR) && --timeout);
    if (!timeout) { I2C1->CR1 |= I2C_CR1_STOP; return -1; }
    /* Clear ADDR flag: read SR1 then SR2 */
    (void)I2C1->SR1;
    (void)I2C1->SR2;

    /* Data byte */
    timeout = TIMEOUT;
    while (!(I2C1->SR1 & I2C_SR1_TXE) && --timeout);
    if (!timeout) { I2C1->CR1 |= I2C_CR1_STOP; return -1; }
    I2C1->DR = note;

    /* Wait for byte transfer to finish */
    timeout = TIMEOUT;
    while (!(I2C1->SR1 & I2C_SR1_BTF) && --timeout);
    if (!timeout) { I2C1->CR1 |= I2C_CR1_STOP; return -1; }

    /* STOP condition */
    I2C1->CR1 |= I2C_CR1_STOP;
    return 0;
}
