CC:= g++


src:= main.cpp
obj:=$(src:.cpp=.o)
exec:=$(src:.cpp= )

ALL: $(obj) $(exec) exec clean
%.o:%.cpp
	$(CC) $^ -c  -o $@
%:%.o
	$(CC) $^ -o $@	


exec:
	./$(exec)
.PHONY: clean
clean:
	-rm -r $(obj) $(exec)
