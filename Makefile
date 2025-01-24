CC=clang
CFLAGS=-Wall -Wextra -Werror -ggdb
LDFLAGS=
OBJS=file.o when.o

all:
	$(CC) $(CFLAGS) -c file.c
	$(CC) $(CFLAGS) -c when.c
	$(CC) $(LDFLAGS) -o when $(OBJS)

clean:
	rm -f *.o when
