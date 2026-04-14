PATH_M := main
PATH_O := obj
PATH_U := user

SRC_M := $(wildcard $(PATH_M)/*.c)
SRC_U := $(wildcard $(PATH_U)/*.c)

OBJ_M := $(SRC_M:.c=.o)
OBJ_U := $(SRC_U:.c=.o)

CFLAGS := -Wall -g -I$(PATH_U)

EXEC := my_program

all: $(EXEC) mv t

$(PATH_M)/%.o : $(PATH_M)/%.c
	$(CC) -c $< -o $@ $(CFLAGS)

$(PATH_U)/%.o : $(PATH_U)/%.c
	$(CC) -c $< -o $@ $(CFLAGS)

$(EXEC): $(OBJ_M) $(OBJ_U)
	$(CC) $^ -o $@ $(CFLAGS)

mv:
	@mv $(OBJ_M) $(OBJ_U) $(PATH_O)   # 必须使用Tab 缩进  ，空格不行

t:
	@tree -L 2

.PHONY: clean
clean:
	@rm -f $(PATH_O)/*.o $(EXEC)
	@tree
