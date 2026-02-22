add_executable(central_unit
    main.cc
)

target_link_libraries(central_unit PUBLIC
    display
    fmt::fmt
    pigpio::pigpio
    pigpio::pigpiod_if
    pigpio::pigpiod_if2
    "-pthread"
)