cmake_minimum_required(VERSION 3.14)

include_directories(${PROJECT_SOURCE_DIR}/include)

file(GLOB_RECURSE sources CONFIGURE_DEPENDS "*.c")

add_executable(ninechippers ${sources})
