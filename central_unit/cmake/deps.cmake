include(FetchContent)

FetchContent_Declare(
    fmt
    GIT_REPOSITORY https://github.com/fmtlib/fmt
    GIT_TAG 12.1.0
)

FetchContent_MakeAvailable(fmt)

FetchContent_Declare(
    pigpio
    GIT_REPOSITORY https://github.com/joan2937/pigpio
    GIT_TAG v79
)

FetchContent_MakeAvailable(pigpio)