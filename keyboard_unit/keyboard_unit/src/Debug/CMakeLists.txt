add_library(Debug
    debug.cc
)

target_link_libraries(Debug
    mcu_flags
    HAL
)