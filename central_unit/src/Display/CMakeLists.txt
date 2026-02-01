add_library(Display STATIC
        Display.cc
    Display_I2C.cc
)

target_include_directories(Display PUBLIC
    ${fmt_SOURCE_DIR}
)

target_link_libraries(Display
    Fonts
    fmt::fmt
    "-pthread"
)