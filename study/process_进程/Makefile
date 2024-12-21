CC := gcc 
text_for_execve:text_for_execve.o
	$(CC) $^ -o $@ -Wall
	./$@
	
process:process.o
	-$(CC) $^ -o $@ -Wall
	./$@
	-rm -r $^ $@ 
stall:
	-rm -r *.o  text_for_execve process