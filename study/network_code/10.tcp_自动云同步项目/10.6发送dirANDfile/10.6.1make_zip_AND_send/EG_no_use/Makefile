CC=gcc
CFLAGS=-Wall -g
ALL:server client

server:server.c
	$(CC) $(CFLAGS) -o server server.c

client:client.c
	$(CC) $(CFLAGS)  client.c -o client 

.PHONY:clean
clean:
	rm -rf server client