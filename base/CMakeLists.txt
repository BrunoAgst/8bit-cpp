cmake_minimum_required(VERSION 3.26)
project(base)

set(CMAKE_CXX_STANDARD 17)

add_executable(base src/main.cpp
        src/cpu/ula/ula.cpp
        src/cpu/ula/ula.h
        src/cpu/uc/uc.cpp
        src/cpu/uc/uc.h
        src/cpu/cpu.cpp
        src/cpu/cpu.h)
