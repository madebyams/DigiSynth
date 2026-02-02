add_library(i2c STATIC
    i2c.cc
)

target_link_libraries(i2c
    fmt::fmt
    "-pthread"
)