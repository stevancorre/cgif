CFLAGS=-Wall -Wextra -std=c11 -pedantic -ggdb
LIBS=-lm

all:
	$(CC) $(CFLAGS) $(LIBS) -o build/cgif src/gif.c src/main.c