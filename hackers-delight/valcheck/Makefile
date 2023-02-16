#
# Makefile
#
# project: hackers_delight
# author:  bernard
# date:    2023 - 02 - 14
#

SRCDIR	:= ..
SRCSA	:= ../safe-arithmetic
SRCLIB	:= ../../lib/include
SRCTST	:= ../testing

CC 		:=  clang-15	# gcc-12
CCOPTIM := -fprofile-instr-generate -fcoverage-mapping
CCDEBUG	:= -O2 -std=c2x
CCINC 	:= -I$(SRCSA) -I$(SRCLIB) -I$(SRCTST)
CCMORE	:= -s -Wall -Wextra -DBITS=128
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
SRCs	:= $(SRCSA)/sai-maths.c $(SRCSA)/sai-string.c $(SRCDIR)/main.c \
			$(SRCTST)/tfibo.c \
                      $(SRCTST)/toverflows.c \
                      $(SRCTST)/tstrings.c


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
