add_executable(keyboard_unit
    main.cc          
    stm32f1xx_hal_msp.c
    stm32f1xx_it.c
    syscalls.c
    sysmem.c
    startup_stm32f103xb.s
)

target_link_libraries(keyboard_unit PUBLIC 
    STM32_Drivers
    ${TOOLCHAIN_LINK_LIBRARIES}
    stm32cubemx

    SystemClock
    GPIO
    I2C
    Keys
    uart
)

set_target_properties(keyboard_unit PROPERTIES ADDITIONAL_CLEAN_FILES keyboard_unit.map)

list(REMOVE_ITEM CMAKE_C_IMPLICIT_LINK_LIBRARIES ob)