CC:=gcc

src:= main.c
obj:= $(src:.c=.o)
exec:= $(src:.c=) 

ALL:  $(exec)
$(exec):%:%.o
	$(CC)   $^ -o $@
%.o:%.cpp
	$(CC)  -c $^ -o $@

.PHONY: ALL clean
clean:
	-rm -r $(obj) $(exec)

