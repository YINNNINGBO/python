CC:= gcc
AFLAN:= -pthread

mutex:mutex.c
	-$(CC) $^ -o $@ $(AFLAN)
	./$@
	-rm -f $@