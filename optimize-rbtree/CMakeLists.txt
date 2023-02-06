cmake_minimum_required(VERSION 3.24)
project(optimize_rbtree C)

set(CMAKE_VERBOSE_MAKEFILE ON)
#set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O0")
set(CMAKE_C_STANDARD 23)

add_executable(optimize_rbtree
        main.c
        rb_tree.h
        rb_tree.c
        private_rb_tree.h)
