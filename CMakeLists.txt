cmake_minimum_required(VERSION 3.27)
project(aoc2023 C)

set(CMAKE_C_STANDARD 23)

add_executable(aoc2023 main.c
        lib/messages.h
        lib/messages.c
        lib/reader.h
        lib/reader.c
        lib/lexer.h
        lib/lexer.c
        lib/01.h
        lib/01.c
        lib/02.h
        lib/02.c
)
