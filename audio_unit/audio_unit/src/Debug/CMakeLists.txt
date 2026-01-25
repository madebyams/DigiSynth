add_library(Debug
    debug.cc
)

target_link_libraries(Debug
    STM32_Drivers
    stm32cubemx
)   