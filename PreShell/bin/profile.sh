#!/bin/sh

CC=gcc
WARNS="-pedantic -Wall -Wextra"
OPTIM="-O2 -ggdb3"
MORE="-D_POSIX_C_SOURCE -std=c2x -I../lib -I.."

BIN=test.exe

mkdir -p build
cd build

onerror() {
    echo "ERROR: $*"
    exit 1
}

# gcc -ggdb3 ../*.c -o test -Wall -Wextra || onerror "compilation failed"
${CC} ${WARNS} ${OPTIM} ${MORE}  -o ${BIN} ../*.c ../lib/rb_tree.c || onerror "compilation failed"
valgrind --tool=callgrind --dump-instr=yes --simulate-cache=yes --collect-jumps=yes \
         --verbose \
         --log-file=valgrind-out.txt ./${BIN} || onerror "Valgrind failed"
