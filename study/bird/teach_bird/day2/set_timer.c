#include <stdio.h>
#include <curses.h>
#include <signal.h>
#include <sys/time.h>

int x=10,y=10;
int a=5,b=10;
void handler(int sig)
{
	move(a,b);
	addch('B');
	refresh();
	b++;

}
int main(int argc, const char *argv[])
{
	char ch;
	initscr();//进入curses模式
	curs_set(0);
	noecho();//禁止字符显示
	keypad(stdscr,1);//允许使用功能键
	start_color();//启动颜色机制
	init_pair(1,COLOR_WHITE, COLOR_RED);
	init_pair(2,COLOR_GREEN,COLOR_WHITE);

	signal(SIGALRM, handler);

	/*设置定时时间*/
	struct itimerval timer;
	timer.it_value.tv_sec = 3;//首次启动定时时间
	timer.it_value.tv_usec = 0;
	timer.it_interval.tv_sec = 1;//之后每次的定时时间
	timer.it_interval.tv_usec = 0;
	/*启动定时*/
	setitimer(ITIMER_REAL, &timer, NULL);

	while(1){
		ch = getch();
		if(ch == 'Q')
		{
			attron(COLOR_PAIR(1));
			move(x,y);
			addch('A');
			refresh();
			y++;
			attroff(COLOR_PAIR(1));
		}
	}

	while(1);
	endwin();//退出curses模式
	return 0;
}
