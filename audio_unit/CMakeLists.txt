cmake_minimum_required(VERSION 3.22)

#
# This file is generated only once,
# and is not re-generated if converter is called multiple times.
#
# User is free to modify the file as much as necessary
#

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
project(audio_unit)
message("Build type: " ${CMAKE_BUILD_TYPE})

# Enable CMake support for ASM and C languages
enable_language(C CXX ASM)

include(FetchContent)

FetchContent_Declare(stm32f4xx_hal_driver
    GIT_REPOSITORY https://github.com/STMicroelectronics/stm32f4xx_hal_driver.git
    GIT_TAG        v1.8.3
    GIT_SHALLOW    TRUE
)
FetchContent_Declare(cmsis_device_f4
    GIT_REPOSITORY https://github.com/STMicroelectronics/cmsis_device_f4.git
    GIT_TAG        v2.6.9
    GIT_SHALLOW    TRUE
)
FetchContent_Declare(cmsis_core
    GIT_REPOSITORY https://github.com/STMicroelectronics/cmsis_core.git
    GIT_TAG        v5.6.0_cm4
    GIT_SHALLOW    TRUE
)
FetchContent_MakeAvailable(stm32f4xx_hal_driver cmsis_device_f4 cmsis_core)

include_directories(
    ./audio_unit/include
    ${stm32f4xx_hal_driver_SOURCE_DIR}/Inc
    ${stm32f4xx_hal_driver_SOURCE_DIR}/Inc/Legacy
    ${cmsis_device_f4_SOURCE_DIR}/Include
    ${cmsis_core_SOURCE_DIR}/Core/Include
)

# Add STM32CubeMX generated sources
add_subdirectory(cmake/stm32cubemx)
add_subdirectory(audio_unit)

