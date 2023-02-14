cmake_minimum_required(VERSION 3.24)
project(hackers_delight C)

set(CMAKE_C_STANDARD 23)

add_executable(hackers_delight
        ../lib/include/compat.h
        main.c
        safe-arithmetic/safe-int-arith.c safe-arithmetic/safe-int-arith
        safe-arithmetic/safe-128b-arith.c)

target_include_directories(hackers_delight PUBLIC
        ../lib/include)
