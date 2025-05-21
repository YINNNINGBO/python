CC := gcc 

all: text_for_execve  process
text_for_execve:text_for_execve.o
	$(CC) $^ -o $@ -Wall
	
	
process:process.o
	-$(CC) $^ -o $@ -Wall


.PHONY: clean
clean:
	-rm -r *.o  text_for_execve process

