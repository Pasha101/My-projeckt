cmake_minimum_required(VERSION 3.16)
project(ember CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(ember
    src/main.cpp
    src/memory.cpp
    src/dump.cpp
    src/alu.cpp
    src/cpu.cpp
)

target_compile_options(ember PRIVATE -Wall -Wextra -Werror)

# Sanitizers on Debug builds.
if(CMAKE_BUILD_TYPE STREQUAL "Debug" AND NOT MSVC)
    target_compile_options(ember PRIVATE -fsanitize=address,undefined -fno-omit-frame-pointer -g)
    target_link_options(ember PRIVATE -fsanitize=address,undefined)
endif()