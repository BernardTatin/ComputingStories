cmake_minimum_required(VERSION 3.24)
project(hackers_delight C)

set(CMAKE_C_STANDARD 23)

add_executable(hackers_delight
        ../lib/include/int128.c ../lib/include/int128.h
        main.c hck-del.c hck-del.h)
target_include_directories(hackers_delight PUBLIC
        ../lib/include)
