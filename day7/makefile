CC:= gcc 

PATH_M:= ./main
PATH_O:= ./obj
PATH_U:= ./user
CONFIG= -Wall -g -I$(PATH_U)

SRC_M:=$(wildcard $(PATH_M)/*.c)   
SRC_U:=$(wildcard $(PATH_U)/*.c)   

OBJ_M:=$(SRC_M:.c=.o)
OBJ_U:=$(SRC_U:.c=.o)

EXEC:= my_pro

all:$(EXEC)  MV  

$(PATH_M)%.o : $(PATH_M)%.c
	$(CC) -g -c $< -o $@ $(CONFIG)

$(PATH_U)/%.o : $(PATH_U)/%.c
	$(CC) -g -c $< -o $@ $(CONFIG)

$(EXEC): $(OBJ_M) $(OBJ_U)
	$(CC) $^ -o $@ $(CONFIG)

MV:
	mv $(OBJ_M) $(OBJ_U) $(PATH_O)
	tree -L 2
.PHONY :clean
clean:
	@rm -f $(PATH_O)/*.o $(EXEC)
	@tree -L 2
