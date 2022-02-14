CFLAGS=-Wall -Wextra -std=c11 -pedantic -ggdb

all:
	$(CC) $(CFLAGS) $(LIBS) -o build/cgif src/main.c