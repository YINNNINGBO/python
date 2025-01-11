CC:= g++
src:=main.cpp main2.cpp main3.cpp
obj:=$(src:.cpp=.o)
exec:=$(src:.cpp=)

ALL:  $(exec) 
$(exec):%: %.o
	$(CC) $< -o $@
# 编译每个目标文件
%.o: %.cpp
	$(CC) -c $< -o $@

exec1:
	./main
exec2:
	./main2
exec3:
	./main3

.PHONY: clean
clean:
	-rm -r $(obj) $(exec)