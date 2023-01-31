cmake_minimum_required(VERSION 3.24)
project(optimize_rbtree C)

set(CMAKE_C_STANDARD 23)

add_executable(optimize_rbtree main.c rb_tree.h rb_tree.c)
