CC=gcc
CFlAGS=-Wall -g

all:server client

server:server.c
	$(CC) $(CFlAGS) -o server server.c

client:client.c
	$(CC) $(CFlAGS) -o client client.c

clean:
	-rm -f server client