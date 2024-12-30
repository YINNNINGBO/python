# 定义编译器
CC := g++

# 定义源文件、目标文件和可执行文件
SRC := main.cpp 
OBJ := $(SRC:.cpp=.o)
EXEC := $(SRC:.cpp=)

# 默认目标
all: $(OBJ) $(EXEC)

# 编译规则：将 .c 文件编译成 .o 文件
%.o: %.cpp
	$(CC) -c $< -o $@

# 链接规则：生成可执行文件
%: %.o
	$(CC) $^ -o $@

# 伪目标
.PHONY: all clean

# 清理规则
clean:
	-rm -f $(OBJ) $(EXEC)
