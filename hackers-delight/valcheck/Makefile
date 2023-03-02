#
# Makefile
#
# project: hackers_delight
# author:  bernard
# date:    2023 - 02 - 14
#
# Usage:
# 	cc=clang|gcc BITS=4|8|16|32|64|128 make clean all
# defaults:
# 	cc=clang
#	BITS=128
#
## NOTE:
## 	valgrind does not like clang debug info.
##

BITS 	?= 128

SRCDIR	:= ..
SRCSA	:= ../safe-arithmetic
SRCLIB	:= ../../lib/include
SRCTST	:= ../testing

cc		?= clang

ifeq ($(cc),clang)
CC 		:=  clang-15	# gcc-12
#CCOPTIM := -O2 -fprofile-instr-generate -fcoverage-mapping -ftrapv -fno-omit-frame-pointer
CCOPTIM := -O3 -fno-omit-frame-pointer
else ifeq($(cc),gcc)
CC		:= gcc-12
CCOPTIM	:= -O2 -ggdb3 -free -fstrict-aliasing -flto
endif

CCDEBUG	:= -std=c2x
CCINC 	:= -I$(SRCSA) -I$(SRCLIB) -I$(SRCTST)
CCMORE	:= -Wall -Wextra -DBITS=$(BITS) # -s
CALL 	:= $(CCOPTIM) $(CCDEBUG) $(CCINC) $(CCMORE)

VALMEM	:= --leak-check=full		\
		  -s \
         --show-leak-kinds:=all	\
         --track-origins:=yes
VALPERF := --tool=callgrind \
		  --dump-instr:=yes\
		  --simulate-cache:=yes\
		  --collect-jumps:=yes
VALLOGM	:= leak-check.txt
VALLOGP := callgrind.txt

DEPS	:= $(SRCLIB)/compat.h $(SRCSA)/safe-int-arith.h \
			$(SRCTST)/testing.h
SRCs	:= $(SRCSA)/sai-maths.c $(SRCSA)/sai-string.c $(SRCSA)/sai_overflow.c \
			$(SRCDIR)/main.c \
			$(SRCTST)/tfibo.c $(SRCTST)/toverflows.c $(SRCTST)/tstrings.c


BINARY	:= hack-delights.bin

all: memory performances
	@echo "all: CALL := $(CALL)"

bin: $(BINARY)

$(BINARY): $(SRCs) $(DEPS)
	$(CC) -o $@ $(CALL) $(SRCs)

memory: $(BINARY)
	valgrind $(VALMEM) --log-file:=$(VALLOGM) ./$(BINARY)

performances: $(BINARY)
	valgrind $(VALPERF) --log-file:=$(VALLOGP) ./$(BINARY)


test: $(BINARY)
	./$(BINARY)


clean:
	rm -f $(BINARY)

.PHONY: all clean memory performances
