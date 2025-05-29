CC:=gcc

SRC:=$(wildcard *.c)
MIN:=$(SRC:.c=.o)
OBJ:=$(MIN:.o=)
all: $(OBJ) Mkdir


$(OBJ):$(MIN)
	$(CC) -o $@ $< -Wall  
Mkdir:
	@mkdir ./MIN
	@mv $(MIN) MIN/
.PHONY: all clean
clean:
	-rm -r  $(OBJ)
	-rm -r MIN