CC := gcc
CFLAGS := -Wall -g

SRC := server.c ../USER/user.c
OBJ := $(SRC:.c=.o)
BIN := server

all: $(BIN)

$(BIN): $(OBJ)
#	$(CC) $(OBJ) -o $@
	$(CC) $^ -o $@ $(CFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	-rm -f $(BIN) $(OBJ)
