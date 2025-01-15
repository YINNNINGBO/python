CC := g++            # 设置编译器

# 源文件列表
src := main.cpp user.cpp

# 目标文件列表
obj := main.o user.o

# 可执行文件名称
exec := main

# 默认目标

all:$(obj)
$(obj): $(src)
	$(CC) -c $< -o $@
#  makefile 这里有问题  无法通过
main: user.o main.o
	$(CC) $^ -o $@

# 编译源文件为目标文件


# 清理目标文件和可执行文件
.PHONY: clean
clean:
	-rm -r $(obj) $(exec)
