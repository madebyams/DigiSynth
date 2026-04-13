add_subdirectory(Fonts)

add_library(display STATIC
        display.cc
        display_transport.cc
)

target_include_directories(display PUBLIC
    ${fmt_SOURCE_DIR}
)

target_link_libraries(display
    fonts
    i2c
    fmt::fmt
    "-pthread"
)