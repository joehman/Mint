cmake_minimum_required(VERSION 3.10.0)
project(mint VERSION 0.1.0 LANGUAGES C)

set(include ${CMAKE_CURRENT_LIST_DIR}/include)

add_subdirectory(util)
add_subdirectory(parser)
add_subdirectory(objects)
add_subdirectory(modules)

add_subdirectory(mint)
