CC=gcc
CFLAGS=-Wall -g 
ALL:main


main:main.c user.c
	$(CC) $(CFLAGS) -o $@ $^ 



.PHONY:clean
clean:
	-rm -f main