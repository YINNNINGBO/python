CC:=g++

src:=main.cpp main2.cpp
obj:=$(src:.cpp=.o)
exec:=$(src:.cpp=)

all:$(obj) $(exec)  exec clean
#%.o 是指任意一个.o文件，而非同时包括所有.o文件
%.o:%.cpp
#-c: 仅编译，不链接
	$(CC) -c $< -o $@
%:%.o
	$(CC) $< -o $@
exec:
	./main
	
.PHONY :all clean
clean:
	-rm -f $(exec) $(obj)