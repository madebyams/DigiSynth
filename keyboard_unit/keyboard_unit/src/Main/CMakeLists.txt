add_executable(${CMAKE_PROJECT_NAME}
    main.cc
    
    syscall.c
	sysmem.c

	startup_stm32f103xx.S
    system_stm32f1xx.c
)

include(cubemx.cmake)

target_link_libraries(${CMAKE_PROJECT_NAME}
    Debug
    SystemClock
)