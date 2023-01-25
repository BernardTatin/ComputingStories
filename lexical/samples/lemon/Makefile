# =================================================================
# playing with Lemon, the SQLite parser
# =================================================================

CC = clang
LD = clang

all: lemon.exe

lemon.exe: lemon.c
	$(CC) -O2 -o $@ $<

clean:
	rm -fv lemon.exe

.PHONY: all clean
