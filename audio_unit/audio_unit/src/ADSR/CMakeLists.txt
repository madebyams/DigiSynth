add_library(ADSR
    adsr.cc
)

target_link_libraries(ADSR
    STM32_Drivers
    stm32cubemx
)