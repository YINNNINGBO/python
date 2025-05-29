CC := gcc
SRC := $(wildcard *.c)
MIN := $(SRC:.c=.o)
OBJ := $(basename $(SRC))

all: $(OBJ) SH

# 每个可执行文件只链接对应的 .o 文件
$(OBJ): % : %.o
	$(CC) $< -o $@

# 编译规则，单个 .c 编译为 .o
%.o: %.c
	$(CC) -c $< -o $@ -Wall

SH:
	@bash ./mv.sh

.PHONY: clean
clean:
	rm -f $(OBJ) $(MIN)
	rm -rf MIN
