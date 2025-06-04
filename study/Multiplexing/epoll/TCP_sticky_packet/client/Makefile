CC := gcc
CFLAGS := -Wall -g

SRC := client.c ../USER/user.c
OBJ := $(SRC:.c=.o)
BIN := client

all: $(BIN)  

$(BIN): $(OBJ)
	$(CC) $^ -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@



clean:
	-rm -f $(BIN) $(OBJ)
	

