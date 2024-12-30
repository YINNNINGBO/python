CC:=g++

src := main.cpp 
obj := $(src:.cpp=.o)
exec := $(src:.cpp=)

all: $(obj) $(exec) 

%.o: %.cpp
	$(CC) -c $< -o $@
%: %.o
	$(CC) $^ -o $@
	./$(exec)
exec:
	./main

.PHONY: all clean
clean:
	-rm -f $(exec) $(obj)  
