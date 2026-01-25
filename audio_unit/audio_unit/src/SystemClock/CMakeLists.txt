add_library(SystemClock
    system_clock.cc
)

target_link_libraries(SystemClock
    STM32_Drivers
    stm32cubemx
)