add_library(DAC
    dac.cc
)

target_link_libraries(DAC
    STM32_Drivers
    stm32cubemx
)