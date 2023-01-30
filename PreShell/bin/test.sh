#!/bin/sh

CC=clang
WARNS="-pedantic -Wall -Wextra"
OPTIM="-O2"
MORE="-D_POSIX_C_SOURCE -std=c2x -Ilib"

BIN=test.exe

${CC} ${WARNS} ${OPTIM} ${MORE}  -o ${BIN} *.c lib/rb_tree.c || exit 1
./test.exe || exit 1

 exit 0
