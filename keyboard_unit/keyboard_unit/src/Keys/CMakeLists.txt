add_library(Keys
    keys.cc
)

target_link_libraries(Keys
    STM32_Drivers
    stm32cubemx
    I2C
)   