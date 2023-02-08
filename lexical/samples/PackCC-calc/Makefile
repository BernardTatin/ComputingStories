# ==================================================
# testing PackCC
# ==================================================

CC = clang
# COPT = -O3 -Wall -pedantic
CINC = -I./lib/include
CWARN =  -Wall -pedantic
COPT = -O0 -ggdb3
CALL = $(CINC) $(COPT) $(CWARN)
PACKCC = packcc

TARGET ?= calc
DEPS = lib/include/compat.h

all: $(TARGET)

$(TARGET).c: $(TARGET).peg
	$(PACKCC) $<

$(TARGET): $(TARGET).c $(TARGET)-tools.h $(TARGET)-tools.c $(DEPS)
	$(CC) $(CALL) -o $@ $< $(TARGET)-tools.c

clean:
	rm -fv $(TARGET) $(TARGET).h $(TARGET).c

test: $(TARGET)
	./$(TARGET) -q < tests/input > output
	diff output tests/reference
	rm -fv output

.PHONY: all clean test
