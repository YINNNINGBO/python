CC=gcc
CFLAGS=-Wall -g
ALL: server client

server:server.c tcp.c
	$(CC) $(CFLAGS)  $^ -o $@

client:client.c  tcp.c 
	$(CC) $(CFLAGS)  $^ -o $@


.PHONY: clean
clean:
	rm -f server client