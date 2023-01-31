#!/bin/sh

mkdir -p build
cd build

# gcc -ggdb3 ../*.c -o test -Wall -Wextra || exit 1
gcc -O2 -g ../*.c -o test -Wall -Wextra || exit 1
valgrind --tool=callgrind --dump-instr=yes --simulate-cache=yes --collect-jumps=yes \
         --verbose \
         --log-file=valgrind-out.txt ./test ../data/pride-en.txt.words || exit 1
less valgrind-out.txt
