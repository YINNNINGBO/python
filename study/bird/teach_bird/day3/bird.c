#include <stdio.h>
#include <curses.h>
#include <signal.h>
#include <sys/time.h>
#include <stdlib.h>
#include <time.h>
#define BIRD '@'
#define BLANK ' '
#define PIPE '+'
/*定义关于管道的结构体*/
typedef struct Pipe
{
	int x; // 列坐标
	int y; // 横坐标
	struct Pipe *next;
} Pipe_node, *Pipe_list;

Pipe_list head, tail;

void creat_list(); // 创建链表
void show_pipe();  // 显示管道
void clear_pipe(); // 清除管道
void move_pipe();  // 移动管道

int bird_y, bird_x; // 小鸟坐标

void show_bird();  // 显示小鸟
void clear_bird(); // 清除小鸟
void move_bird();  // 移动小鸟

void init_curses();		 // curses库初始化
int set_timer(int ms_t); // 设置定时器--ms
void handler(int sig);	 // 信号处理函数

int main(int argc, const char *argv[])
{
	bird_y = 15; // 行
	bird_x = 10; // 列
	init_curses();
	signal(SIGALRM, handler);
	set_timer(500); // 500ms

	srand(time(0)); // 随机种子   可以使rand()函数每次生成的随机值不同
	creat_list();
	show_pipe();

	show_bird();
	move_bird();

	return 0;
}
void init_curses() // curses库初始化
{
	initscr();								// 进入curses模式
	curs_set(0);							// 禁止光标显示
	noecho();								// 禁止输入字符显示
	keypad(stdscr, 1);						// 启动功能按键
	start_color();							// 启动颜色机制
	init_pair(1, COLOR_WHITE, COLOR_RED);	// 小鸟颜色设置
	init_pair(2, COLOR_WHITE, COLOR_GREEN); // 管道颜色设置
}
int set_timer(int ms_t) // 设置定时器--ms
{
	struct itimerval timer;
	long t_sec, t_usec;
	int ret;

	t_sec = ms_t / 1000;		   // s
	t_usec = (ms_t % 1000) * 1000; // us

	timer.it_value.tv_sec = t_sec;
	timer.it_value.tv_usec = t_usec; // 首次启动定时值

	timer.it_interval.tv_sec = t_sec;
	timer.it_interval.tv_usec = t_usec; // 定时时间间隔

	ret = setitimer(ITIMER_REAL, &timer, NULL);
	return ret;
}
void handler(int sig)
{
	Pipe_list p, new; // 定义两个管道节点指针，p用于遍历当前管道链表，new用于创建新管道
	int i, j;		  // 定义两个整型变量，用于循环控制
	/*小鸟下落*/
	clear_bird();
	bird_y++;
	show_bird(); // 在新位置显示小鸟
	/*游戏结束判断*/
	if ((char)inch() == PIPE) // 检查小鸟当前位置是否与管道字符相同
	{
		set_timer(0); // 停止计时器
		endwin();	  // 结束ncurses窗口
		exit(1);	  // 退出程序
	}
	p = head->next; // 从管道链表的第二个节点开始遍历
	if (p->x == 0)	// 如果当前管道的x坐标为0，表示该管道已经完全进入屏幕 需要清楚当前管道并创建新管道
	{
		///*清除当前节点 p*/
		head->next = p->next; // 将头节点的下一个节点指向当前节点的下一个节点，即移除当前节点
		// 用 ' '  （空格）覆盖要清楚的节点 ,，表示清除
		for (i = p->x; i < p->x + 10; i++) // 遍历当前管道的宽度
		{
			/*上半部分管道*/
			for (j = 0; j < p->y; j++) // 遍历管道的上半部分高度
			{
				move(j, i);	  // 移动光标到管道的每个位置
				addch(BLANK); // 用空白字符替换管道字符，即清除管道
			}
			/*下半部分管道创建*/
			for (j = p->y + 5; j < 25; j++) // 遍历管道的下半部分高度
			{
				move(j, i);	  // 移动光标到管道的每个位置
				addch(BLANK); // 用空白字符替换管道字符，即清除管道
			}
			refresh(); // 刷新屏幕显示
		}
		free(p); // 释放当前管道节点的内存
		///*创建新管道*/
		new = (Pipe_list)malloc(sizeof(Pipe_node)); // 分配内存创建新管道节点
		new->x = tail->x + 20;						// 设置新管道的x坐标为尾节点的x坐标加20
		new->y = rand() % 11 + 5;					// 随机生成新管道的y坐标，范围在5到15之间
		new->next = NULL;							// 新管道的下一个节点为空
		tail->next = new;							// 将尾节点的下一个节点指向新管道
		tail = new;									// 更新尾节点为新管道
	}

	/*管道移动*/
	clear_pipe(); // 清除当前所有管道的位置
	move_pipe();  // 移动所有管道的位置
	show_pipe();  // 在新位置显示所有管道
}
void show_bird() // 显示小鸟
{
	// 启用颜色对1，用于设置小鸟的颜色属性
	attron(COLOR_PAIR(1));
	// 将光标移动到小鸟的位置 (bird_y, bird_x)
	move(bird_y, bird_x);
	// 在当前位置添加小鸟的字符表示 BIRD
	addch(BIRD);
	// 刷新屏幕，使添加的字符立即显示
	refresh();
	// 关闭颜色对1，恢复之前的颜色属性
	attroff(COLOR_PAIR(1));
}
void clear_bird() // 清除小鸟
{
	move(bird_y, bird_x); // 将光标移动到小鸟的当前位置 (bird_y, bird_x)
	addch(BLANK);		  // 在当前位置添加一个空白字符，即清除小鸟的显示
	refresh();			  // 刷新屏幕，使更改生效
}
void move_bird() // 移动小鸟
{
	char key; // 定义一个字符变量用于存储按键输入
	while (1) // 无限循环，持续检测按键输入
	{
		key = getch();	// 获取用户按键输入
		if (key == ' ') // 如果按键是空格键
		{
			clear_bird(); // 清除当前小鸟的位置
			bird_y--;	  // 小鸟的y坐标减1，即向上移动
			show_bird();  // 在新的位置显示小鸟
			/*游戏结束判断*/
			if ((char)inch() == PIPE) // 检查当前位置(光标)是否是管道（PIPE）
			{
				set_timer(0); // 停止计时器
				endwin();	  // 结束ncurses模式
				exit(1);	  // 退出游戏，返回状态码1
			}
		}
	}
}
void creat_list() // 创建链表
{
	int i;										 // 循环变量
	Pipe_list p, new;							 // 定义两个指针变量，p用于遍历链表，new用于创建新节点
	head = (Pipe_list)malloc(sizeof(Pipe_node)); // 分配内存空间给头节点
	head->next = NULL;							 // 头节点的下一个节点指针初始化为NULL
	p = head;									 // 将p指向头节点

	for (i = 0; i < 5; i++) // 循环5次，创建5个节点
	{
		new = (Pipe_list)malloc(sizeof(Pipe_node)); // 分配内存空间给新节点
		new->x = (i + 1) * 20;						// 设置新节点的x值为20的倍数
		new->y = rand() % 11 + 5;					// (5-15行)
		new->next = NULL;
		p->next = new;
		p = new;
	}
	tail = p;
}
void show_pipe() // 显示管道
{
	Pipe_list p;
	int i, j;
	p = head->next;
	attron(COLOR_PAIR(2));
	while (p)
	{
		for (i = p->x; i < p->x + 10; i++)
		{
			/*上半部分管道*/
			for (j = 0; j < p->y; j++)
			{
				move(j, i);
				addch(PIPE);
			}
			/*下半部分管道创建*/
			for (j = p->y + 5; j < 25; j++)
			{
				move(j, i);
				addch(PIPE);
			}
		}
		refresh();
		p = p->next;
	}
	attroff(COLOR_PAIR(2));
}
void clear_pipe() // 清除管道
{
	Pipe_list p;
	int i, j;
	p = head->next;
	while (p)
	{
		for (i = p->x; i < p->x + 10; i++)
		{
			/*上半部分管道*/
			for (j = 0; j < p->y; j++)
			{
				move(j, i);
				addch(BLANK);
			}
			/*下半部分管道创建*/
			for (j = p->y + 5; j < 25; j++)
			{
				move(j, i);
				addch(BLANK);
			}
		}
		refresh();
		p = p->next;
	}
}
void move_pipe() // 移动管道
{
	Pipe_list p;
	p = head->next;
	while (p)
	{
		p->x--;
		p = p->next;
	}
}
