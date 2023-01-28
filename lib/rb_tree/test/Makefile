#
# Makefile
# pour tester les rb-trees

CC = clang
CFLAGS = -I.. -O2 -Wall -Wextra
LDFLAGS =

OBJS = rb_tree.o test.o
DEPS = ../rb_tree.h
SRC = rb_tree.c test.c
TARGET = test.exe

all: $(TARGET)

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

%.o: ../%.c
	$(CC) $(CFLAGS) -c -o $@ $<

$(TARGET): $(OBJS)
	$(CC) $(LDFLAGS) -o $@ $(OBJS)

clean:
	rm -fv $(TARGET) $(OBJS)

.PHONY: all clean
