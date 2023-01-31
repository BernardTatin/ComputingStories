#!/bin/sh

mkdir -p build
cd build

gcc -ggdb3 ../*.c -o test -Wall -Wextra || exit 1
valgrind --leak-check=full \
         --show-leak-kinds=all \
         --track-origins=yes \
         --verbose \
         --log-file=valgrind-out.txt ./test ../data/pride-en.txt.words || exit 1
less valgrind-out.txt
