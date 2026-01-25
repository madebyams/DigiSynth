add_executable(${CMAKE_PROJECT_NAME}
    main.cc

    syscall.c
    sysmem.c

    startup_stm32f401xx.S
    system_stm32f4xx.c
)

include(cubemx.cmake)