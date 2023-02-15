cmake_minimum_required(VERSION 3.24)
project(hackers_delight C)

set(CMAKE_C_STANDARD 23)

add_executable(hackers_delight
        main.c
        ../lib/include/compat.h
        safe-arithmetic/safe-int-arith.h
        safe-arithmetic/sai_string.c safe-arithmetic/sai-definitions.h safe-arithmetic/sai_overflow.h safe-arithmetic/sai-misc.h safe-arithmetic/sai-maths.h safe-arithmetic/sai-maths.c safe-arithmetic/sai-string.h)

target_include_directories(hackers_delight PUBLIC
        ../lib/include)
