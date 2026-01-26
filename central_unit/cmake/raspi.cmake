set(CMAKE_SYSTEM_NAME Linux)
set(CMAKE_SYSTEM_PROCESSOR arm)

if(NOT DEFINED ARM_ROOT)
    set(ARM_ROOT /Users/ams/dev/DigiSynth/central_unit/aarch64-unknown-linux-gnu/bin/ CACHE PATH "Root directory for ARM toolchain")
endif()

set(CMAKE_C_COMPILER ${ARM_ROOT}/aarch64-linux-gnu-gcc)
set(CMAKE_CXX_COMPILER ${ARM_ROOT}/aarch64-linux-gnu-g++)

set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)