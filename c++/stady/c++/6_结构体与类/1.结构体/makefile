cc=g++

src:=main.cpp
obj:=$(src:.cpp=.o)
exec:=$(src:.cpp=)

all:$(obj)  $(exec)  exec   clean
%.o:%.cpp
	$(cc) $^ -c -o $@
%:%.o
	$(cc) $^  -o $@

exec:
	./$(exec)
.PHONY:all  clean
clean:
	-rm -r $(obj) $(exec)
