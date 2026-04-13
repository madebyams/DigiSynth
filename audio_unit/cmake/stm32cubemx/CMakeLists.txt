cmake_minimum_required(VERSION 3.22)
# Enable CMake support for ASM and C languages
enable_language(C ASM)
# STM32CubeMX generated symbols (macros)
set(MX_Defines_Syms 
	USE_HAL_DRIVER 
	STM32F401xC
    $<$<CONFIG:Debug>:DEBUG>
)


# STM32 HAL/LL Drivers
set(STM32_Drivers_Src
    ${CMAKE_CURRENT_SOURCE_DIR}/../../audio_unit/src/Main/system_stm32f4xx.c
    ${stm32f4xx_hal_driver_SOURCE_DIR}/Src/stm32f4xx_hal_adc.c
    ${stm32f4xx_hal_driver_SOURCE_DIR}/Src/stm32f4xx_hal_adc_ex.c
    ${stm32f4xx_hal_driver_SOURCE_DIR}/Src/stm32f4xx_hal_rcc.c
    ${stm32f4xx_hal_driver_SOURCE_DIR}/Src/stm32f4xx_hal_rcc_ex.c
    ${stm32f4xx_hal_driver_SOURCE_DIR}/Src/stm32f4xx_hal_flash.c
    ${stm32f4xx_hal_driver_SOURCE_DIR}/Src/stm32f4xx_hal_flash_ex.c
    ${stm32f4xx_hal_driver_SOURCE_DIR}/Src/stm32f4xx_hal_flash_ramfunc.c
    ${stm32f4xx_hal_driver_SOURCE_DIR}/Src/stm32f4xx_hal_gpio.c
    ${stm32f4xx_hal_driver_SOURCE_DIR}/Src/stm32f4xx_hal_dma_ex.c
    ${stm32f4xx_hal_driver_SOURCE_DIR}/Src/stm32f4xx_hal_dma.c
    ${stm32f4xx_hal_driver_SOURCE_DIR}/Src/stm32f4xx_hal_pwr.c
    ${stm32f4xx_hal_driver_SOURCE_DIR}/Src/stm32f4xx_hal_pwr_ex.c
    ${stm32f4xx_hal_driver_SOURCE_DIR}/Src/stm32f4xx_hal_cortex.c
    ${stm32f4xx_hal_driver_SOURCE_DIR}/Src/stm32f4xx_hal.c
    ${stm32f4xx_hal_driver_SOURCE_DIR}/Src/stm32f4xx_hal_exti.c
    ${stm32f4xx_hal_driver_SOURCE_DIR}/Src/stm32f4xx_hal_i2s.c
    ${stm32f4xx_hal_driver_SOURCE_DIR}/Src/stm32f4xx_hal_i2s_ex.c
    ${stm32f4xx_hal_driver_SOURCE_DIR}/Src/stm32f4xx_hal_spi.c
    ${stm32f4xx_hal_driver_SOURCE_DIR}/Src/stm32f4xx_hal_uart.c
)


# Interface library for includes and symbols
add_library(stm32cubemx INTERFACE)
target_compile_definitions(stm32cubemx INTERFACE ${MX_Defines_Syms})

# Create STM32_Drivers static library
add_library(STM32_Drivers OBJECT)
target_sources(STM32_Drivers PRIVATE ${STM32_Drivers_Src})
target_include_directories(STM32_Drivers PUBLIC ${STM32_Drivers_Include_Dirs})
target_link_libraries(STM32_Drivers PUBLIC stm32cubemx)


# Validate that STM32CubeMX code is compatible with C standard
if((CMAKE_C_STANDARD EQUAL 90) OR (CMAKE_C_STANDARD EQUAL 99))
    message(ERROR "Generated code requires C11 or higher")
endif()
