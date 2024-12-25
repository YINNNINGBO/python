CC := gcc
CONNECT:= -pthread

unname_sem:unname_sem.c
	-$(CC) $^ -o $@ -Wall $(CONNECT)
	./$@
	-rm -f $@