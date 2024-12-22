CC := gcc


all: process_write process_read  text

process_write:process_write.c
	-$(CC) $^ -o $@ -Wall
process_read:process_read.c
	-$(CC) $^ -o $@ -Wall
text:
	
	./process_write  
	./process_read
	-rm -r process_write  process_read
