add_library(GPIO
    gpio.cc
)

target_link_libraries(GPIO
    STM32_Drivers
    stm32cubemx
)   