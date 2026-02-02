add_library(UART
    uart.cc
)

target_link_libraries(UART
    STM32_Drivers
    stm32cubemx
)