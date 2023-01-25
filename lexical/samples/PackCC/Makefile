# ==================================================
# testing PackCC
# ==================================================

CC = clang
COPT = -O2 -Wall -pedantic
PACKCC = packcc

TARGET ?= calc

all: $(TARGET)

$(TARGET).c: $(TARGET).y
	$(PACKCC) $<

$(TARGET): $(TARGET).c
	$(CC) $(COPT) -o $@ $<

clean:
	rm $(TARGET) $(TARGET).h $(TARGET).c

.PHONY: all clean
