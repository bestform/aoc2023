cmake_minimum_required(VERSION 3.27)
project(aoc2023 C)

set(CMAKE_C_STANDARD 23)

add_executable(aoc2023_tests messagesTests.c
        unity/src/unity.c
        ../lib/messages.h
        ../lib/messages.c
        ../lib/01.c
        ../lib/01.h
        ../lib/reader.c
        ../lib/reader.h
)
