CC = gcc        # 定义编译器
CFLAGS = -Wall  # 编译时的选项

# ***********具有关系的进程间通信
process_mq: process_mq.c use.h
	$(CC) $^ -o $@ $(CFLAGS)  # 编译源文件
	./$@                       # 运行可执行文件
	rm -f $@                   # 删除可执行文件


#****************不具有关系的进程间通信
#  先执行XXXwrite , 再执行XXXread  即可
ALL:use_mq_write use_mq_read
use_mq_write:use_mq_write.c
	$(CC) $^ -o $@ $(CFLAGS)  # 编译源文件
use_mq_read:use_mq_read.c
	$(CC) $^ -o $@ $(CFLAGS)  # 编译源文件
clean:
	-rm -f use_mq_write use_mq_read