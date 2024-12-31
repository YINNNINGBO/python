CC:=g++

src:=main.cpp
obj:=$(src:.cpp=.o)
exec:=$(src:.cpp=)

all:$(obj) $(exec) exec clean

%.o:%.cpp
	$(CC) -c $^ -o $@
%:%.o
	$(CC)  $^ -o $@

exec:
	./$(exec)

.PHONY:all  clean
claen:
	-rm -f $(obj) $(exec)

