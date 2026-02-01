add_library(uart
    uart.cc
)

target_link_libraries(uart
    STM32_Drivers
    stm32cubemx
)