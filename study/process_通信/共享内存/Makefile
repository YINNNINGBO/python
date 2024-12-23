CC:= gcc
process_shared:process_shared.c
	-$(CC) $^ -o $@ -Wall
	-./$@
	-rm -r $@