add_library(LED
    led.cc
)

target_link_libraries(LED
    STM32_Drivers
    stm32cubemx
)