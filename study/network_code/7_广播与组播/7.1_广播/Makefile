CC=gcc
CFLAGS=-Wall -g
ALL:sender receive
sender:sender.c
	$(CC) $^  -o $@ $(CFLAGS)
receive:receive.c
	$(CC) $^ -o  $@   $(CFLAGS) 
.PHONY: clean
clean:
	-rm -f sender receive