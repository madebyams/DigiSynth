cmake_minimum_required(VERSION 3.22)


# Setup compiler settings
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS ON)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)


# Enable compile command to ease indexing with e.g. clangd
set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)

# Core project settings
project(keyboard_unit)
message("Build type: " ${CMAKE_BUILD_TYPE})

# Enable CMake support for ASM and C languages
enable_language(C CXX ASM)

# Fetch STM32 drivers at configure time
include(FetchContent)

FetchContent_Declare(
    stm32f1xx_hal_driver
    GIT_REPOSITORY https://github.com/STMicroelectronics/stm32f1xx-hal-driver.git
    GIT_TAG        v1.1.9
)

FetchContent_Declare(
    cmsis_device_f1
    GIT_REPOSITORY https://github.com/STMicroelectronics/cmsis_device_f1.git
    GIT_TAG        v4.3.4
)

FetchContent_Declare(
    cmsis_core
    GIT_REPOSITORY https://github.com/STMicroelectronics/cmsis_core.git
    GIT_TAG        v5.4.0_cm3
)

FetchContent_MakeAvailable(stm32f1xx_hal_driver cmsis_device_f1 cmsis_core)

include_directories(
    ./keyboard_unit/include
    ${stm32f1xx_hal_driver_SOURCE_DIR}/Inc
    ${stm32f1xx_hal_driver_SOURCE_DIR}/Inc/Legacy
    ${cmsis_device_f1_SOURCE_DIR}/Include
    ${cmsis_core_SOURCE_DIR}/Include
)


# Add STM32CubeMX generated sources
add_subdirectory(cmake/stm32cubemx)
add_subdirectory(keyboard_unit)