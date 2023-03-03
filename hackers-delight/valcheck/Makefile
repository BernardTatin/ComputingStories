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
## NOTE for clang:
## 	valgrind does not like clang debug info but
## 	give some good results with  -fno-omit-frame-pointer
##
## NOTE for gcc:
##	total failure with -O2 or -O3, works with -01
##

BITS 	?= 128

SRCDIR	:= ..
SRCSA	:= ../safe-arithmetic
SRCLIB	:= ../../lib/include
SRCTST	:= ../testing

cc		?= clang
os		:= $(shell uname)

ifeq ($(cc),clang)
ifeq ($(os),FreeBSD)
CC 		:=  clang15
else
CC 		:=  clang-15
endif
#CCOPTIM := -O2 -fprofile-instr-generate -fcoverage-mapping -ftrapv -fno-omit-frame-pointer
CCOPTIM := -O3 -fno-omit-frame-pointer
endif
ifeq ($(cc),gcc)
ifeq ($(os),FreeBSD)
CC 		:=  gcc12
else
CC 		:=  gcc-12
endif
CCOPTIM	:= -O1 -ggdb3 -free -fstrict-aliasing -flto
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
	@echo "running on $(os)"
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
