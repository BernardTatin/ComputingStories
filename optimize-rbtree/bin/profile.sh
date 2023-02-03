#!/bin/sh

CC=gcc

mkdir -p build
cd build

onerror() {
  echo "ERROR: $*"
  exit 1
}

# gcc -ggdb3 ../*.c -o test -Wall -Wextra || exit 1
${CC} -O2 -ggdb3 ../*.c -o test -Wall -Wextra || onerror "compilation"
valgrind --tool=callgrind --dump-instr=yes --simulate-cache=yes --collect-jumps=yes \
         --verbose \
         --log-file=valgrind-out.txt ./test ../data/pride-en.txt.words || onerror "valgrind"
less valgrind-out.txt
