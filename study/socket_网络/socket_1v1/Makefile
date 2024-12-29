# 定义编译器
CC := gcc
#可以生成 .o 文件
# 定义源文件和目标文件
SRC := socket_server.c socket_client.c
OBJ := $(SRC:.c=.o)
EXEC := $(SRC:.c= )

# 默认目标
all: $(EXEC)

# 单独链接每个目标可执行文件
socket_server: socket_server.o
	$(CC) $^ -o $@

socket_client: socket_client.o
	$(CC) $^ -o $@

# 编译规则：将 .c 文件编译成 .o 文件
%.o: %.c
	$(CC) -c $< -o $@

# 伪目标
.PHONY: all clean

# 清理规则
clean:
	-rm -f $(OBJ) $(EXEC)
