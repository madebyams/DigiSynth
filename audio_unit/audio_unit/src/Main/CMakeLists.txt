
# Create an executable object type
add_executable(audio_unit
    ./main.cc
    ./stm32f4xx_it.c
    ./stm32f4xx_hal_msp.c
    ./sysmem.c
    ./syscalls.c
    ./startup_stm32f401xc.s
)


# Project static libraries
target_link_libraries(audio_unit PUBLIC
    STM32_Drivers
    ${TOOLCHAIN_LINK_LIBRARIES}
    stm32cubemx

    ADSR
    DAC
    Debug
    DMA
    GPIO
    LED
    MessageBus
    SystemClock
)

# Add the map file to the list of files to be removed with 'clean' target
set_target_properties(audio_unit PROPERTIES ADDITIONAL_CLEAN_FILES audio_unit.map)

# Remove wrong libob.a library dependency when using cpp files
list(REMOVE_ITEM CMAKE_C_IMPLICIT_LINK_LIBRARIES ob)

