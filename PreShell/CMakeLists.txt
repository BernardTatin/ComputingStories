cmake_minimum_required(VERSION 3.24)
project(PreShell C)

set(CMAKE_C_STANDARD 23)

add_executable(PreShell
        main.c
        path-loader.c path-loader.h
        config.h
        lib/rb_tree.c lib/rb_tree.h
        )
target_include_directories(PreShell PUBLIC
        lib)
