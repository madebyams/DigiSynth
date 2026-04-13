add_library(I2C
    i2c.cc
)


target_link_libraries(I2C
    STM32_Drivers
    stm32cubemx
)   