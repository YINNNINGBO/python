
# 编译器
CC = gcc

# 编译选项
CFLAGS = -Wall -g

# 目标文件
CLIENT_TARGET = client/client
SERVER_TARGET = server/server

# 源文件
CLIENT_SRCS = client/client.c client/client_use.c
SERVER_SRCS = server/server.c server/server_use.c

# 头文件路径
INCLUDES = -Iclient -Iserver

# 生成目标文件
all: $(CLIENT_TARGET) $(SERVER_TARGET)

# 生成客户端可执行文件
$(CLIENT_TARGET): $(CLIENT_SRCS)
	$(CC) $(CFLAGS) $(INCLUDES)  $^ -o $@

# 生成服务端可执行文件
$(SERVER_TARGET): $(SERVER_SRCS)
	$(CC) $(CFLAGS) $(INCLUDES) $^ -o $@ 

# 清理生成的文件
.PHONY:  clean

clean:
	-rm -f $(CLIENT_TARGET) $(SERVER_TARGET)

