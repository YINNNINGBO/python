CC:=g++

src:=main1.cpp  
obj:=$(src:.cpp=.o)
exec:=$(src:.cpp=)
ALL:$(exec)
$(exec):%:%.o
# $^：全部依赖
	$(CC)  $^ -o $@
%.o:%.cpp
	$(CC) -c $^ -o $@
exec1:
	./main1
exec2:
	./main2  
.PHONY: clean
clean:
	-rm -r $(exec) $(obj)
