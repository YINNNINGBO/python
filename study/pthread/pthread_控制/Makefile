CC:= gcc
AFLAN:= -pthread

pthread_create:pthread_create.c
	-$(CC) $^ -o $@ $(AFLAN)
	./$@
	-rm -f $@