CC=gcc
CFLAGS=-Wall -g
all:server client

server:server.c
	$(CC) $(CFLAGS) -o $@ $^ -lpthread
.PHONY:clean
clean:
	-rm -f server client