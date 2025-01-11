CC:= g++
src:=main1.cpp
obj:=$(src:.cpp=.o)
exec:=$(src:.cpp=)

all:$(exec) $(obj)
$(exec):%:%.o
	$(CC)  $^ -o $@
$(obj):%.o:%.cpp
	$(CC)  -c $^ -o $@

.PHONY: all clean
clean:
	-rm $(obj) $(exec)