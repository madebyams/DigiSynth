#include "uart.hh"
#include "stm32f1xx_hal_def.h"
#include "stm32f1xx_hal_uart.h"
#include <string>
#include <cstring>


bool UART::init() {
    huart1.Instance = USART1;
    huart1.Init.BaudRate = 115200;
    huart1.Init.WordLength = UART_WORDLENGTH_8B;
    huart1.Init.StopBits = UART_STOPBITS_1;
    huart1.Init.Parity = UART_PARITY_NONE;
    huart1.Init.Mode = UART_MODE_TX_RX;
    huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
    huart1.Init.OverSampling = UART_OVERSAMPLING_16;

    return HAL_UART_Init(&huart1) == HAL_OK;
}

void UART::print(std::string message) const {
    // Send the message via TX (PA9)
    HAL_StatusTypeDef status = HAL_UART_Transmit(const_cast<UART_HandleTypeDef*>(&huart1), reinterpret_cast<const uint8_t *>(message.c_str()), message.length(), 1000);
    if (status != HAL_OK) {
        return;
    }
}