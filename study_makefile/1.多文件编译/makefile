# 编译器
CC := gcc

# 目录设置
PWD_MAIN := main
PWD_USER := user
PWD_INCLUDE := head

# 源文件
SRC_MAIN := $(PWD_MAIN)/main.c
SRC_USER := $(wildcard $(PWD_USER)/*.c)  # 自动列出 9.1user 目录下的所有 .c 文件
#SRC_USER := $(ls $(PWD_USER)/*.c)       # error

# 目标文件
OBJ_MAIN := $(PWD_MAIN)/main.o
#OBJ_USER := $(SRC_USER:$(PWD_USER)/%.c=$(PWD_USER)/%.o)  # 将所有 user.c 文件转换为 .o 文件
OBJ_USER := $(SRC_USER:.c=.o)  # 也可以

# 可执行文件
EXEC := my_program

# 编译选项
CFLAGS := -Wall -g -I$(PWD_INCLUDE)

# 默认目标
all: $(EXEC)

# 生成目标文件
$(OBJ_USER): $(PWD_USER)/%.o: $(PWD_USER)/%.c
	$(CC) -c $< -o $@ $(CFLAGS)

# 生成主目标文件
$(OBJ_MAIN): $(SRC_MAIN)
	$(CC) -c $< -o $@ $(CFLAGS)

# 生成可执行文件
$(EXEC): $(OBJ_MAIN) $(OBJ_USER)
	$(CC) $^ -o $@ $(CFLAGS)

# 清理规则
.PHONY: clean
clean:
	rm -f $(OBJ_MAIN) $(OBJ_USER) $(EXEC)
