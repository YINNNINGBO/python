CC:= gcc 
PATH_MAIN:=./main
PATH_OBJ:=./obj
PATH_USER:=./user
# 编译选项
CFLAGS := -Wall -g -I$(PATH_USER)

# .c 原文件
SRC_MAIN := $(PATH_MAIN)/main.c
SRC_USER := $(wildcard $(PATH_USER)/*.c) 

# .o 目标文件
OBJ_MAIN := $(PATH_MAIN)/main.o
OBJ_USER := $(PATH_USER)/user.o

EXEC := my_program

all :$(EXEC) mv tree

$(PATH_MAIN)/%.o : $(PATH_MAIN)/%.c
	$(CC) -c $< -o $@ $(CFLAGS)

$(PATH_USER)/%.o : $(PATH_USER)/%.c
	$(CC) -c $< -o $@ $(CFLAGS)

$(EXEC): $(OBJ_MAIN) $(OBJ_USER)
	$(CC) $^ -o $@ $(CFLAGS)
mv:
	@mv  $(OBJ_MAIN) $(OBJ_USER) ./obj
tree:
	@tree -L 2

.PHONY: clear
clear:
	rm -f  $(PATH_OBJ)/*.o  $(EXEC)
	@tree 