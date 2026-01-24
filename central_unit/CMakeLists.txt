cmake_minimum_required(VERSION 3.30)
include(cmake/raspi.cmake)

project(central_unit C CXX)
set(CMAKE_CXX_STANDARD 23)
include(cmake/deps.cmake)

include_directories(include)
add_subdirectory(src)