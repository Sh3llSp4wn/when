CC=clang
#CFLAGS=-Wall -Wextra -Werror -O2
CFLAGS=-Wall -Wextra -Werror -O0 -ggdb
LDFLAGS=
OBJS=file.o when.o main.o
PREFIX=/usr/local

all:
	$(CC) $(CFLAGS) -c file.c
	$(CC) $(CFLAGS) -c when.c
	$(CC) $(CFLAGS) -c main.c
	$(CC) $(LDFLAGS) -o when $(OBJS)

clean:
	rm -f *.o when

install: all
	install -s when $(PREFIX)/bin/when
