include(FetchContent)

FetchContent_Declare(
    pigpio
    GIT_REPOSITORY https://github.com/joan2937/pigpio
    GIT_TAG v79
)

FetchContent_MakeAvailable(pigpio)