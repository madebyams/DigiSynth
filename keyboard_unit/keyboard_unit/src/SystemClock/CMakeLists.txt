add_library(SystemClock
    system_clock.cc
)

target_link_libraries(SystemClock
    mcu_flags
    HAL
)