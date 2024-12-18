objects:=main.o fun.o
#引入变量
main:$(objects)
	gcc $(objects) -o main

main.o:  fun.h
# #gcc fun.c  fun.h -o fun.o
# 	gcc main.c fun.h -c 
fun.o:  fun.h
# 	gcc fun.c  fun.h -c 

clean:
	-rm -r *.o  main