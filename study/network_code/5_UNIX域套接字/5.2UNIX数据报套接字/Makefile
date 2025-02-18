CC=gcc
CFLAGS=-Wall -g 
ALL:UNIX_client UNIX_server


UNIX_client:UNIX_client.c
	$(CC) $(CFLAGS) -o UNIX_client UNIX_client.c

UNIX_server:UNIX_server.c
	$(CC) $(CFLAGS) -o UNIX_server UNIX_server.c
	
.PHONY:clean
clean:
	rm -f UNIX_client UNIX_server
