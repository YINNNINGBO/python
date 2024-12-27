CC:= gcc
CONNECT:=-pthread

main:main.c user.c
	-$(CC) $^ -o $@  $(CONNECT)  
	./$@
	-rm -f $@

struct:struct.c 
	-$(CC) $^ -o $@  $(CONNECT)
	./$@
	-rm -f $@