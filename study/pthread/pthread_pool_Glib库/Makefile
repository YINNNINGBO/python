CC:=gcc
#链接Glib库命令
#CONNECT:= pkg-config --cflags --libs glib-2.0    $(CONNECT)
CONNECT := pkg-config --cflags --libs glib-2.0
#使用Glib 库
main: main.c
#  这里CONNECT  是命令  前+shell
	$(CC) $^ -o $@ $(shell $(CONNECT))
	./$@
	-rm -f $@
