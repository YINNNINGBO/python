CC:=gcc

SRC:=$(wildcard *.c)
MIN:=$(SRC:.c=.o)
OBJ:=$(MIN:.o=)
all: $(OBJ) Mkdir


$(OBJ):%:%.o
	$(CC) -o $@ $< -Wall
Mkdir:
	@echo "Creating directory for minimized files..."
	-@mkdir ./MIN
	@mv $(MIN) MIN/
.PHONY: all clean
clean:
	-rm -r  $(OBJ)
	-rm -r MIN