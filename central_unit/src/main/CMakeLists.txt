add_executable(central_unit
    main.cc
)

target_link_libraries(central_unit
    display
    fmt::fmt
)