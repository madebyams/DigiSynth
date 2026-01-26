add_library(Display STATIC
    Display.cc
        ../Fonts/Fonts.cc
)

target_include_directories(Display PUBLIC
    ${pigpio_SOURCE_DIR}
)

target_link_libraries(Display
    Fonts
    pigpio
    "-pthread"
)