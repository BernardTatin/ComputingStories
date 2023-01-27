# ==================================================
# testing PackCC
# ==================================================

CC = clang
COPT = -O3 -Wall -pedantic
PACKCC = packcc

TARGET ?= calc

all: $(TARGET)

$(TARGET).c: $(TARGET).y
	$(PACKCC) $<

$(TARGET): $(TARGET).c $(TARGET)-tools.h $(TARGET)-tools.c
	$(CC) $(COPT) -o $@ $< $(TARGET)-tools.c

clean:
	rm -fv $(TARGET) $(TARGET).h $(TARGET).c

.PHONY: all clean
