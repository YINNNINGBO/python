#include <stdio.h>
#include <curses.h>
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

	move(5,5);
	addch('C');
	refresh();
	ch = getch();
	if(ch == 'Q')
	{
		attron(COLOR_PAIR(1));
		move(10,10);
		addch('A');
		refresh();
		attroff(COLOR_PAIR(1));
	}
	move(10,10);
	ch = (char)inch();
	if(ch == 'A')
	{
		attron(COLOR_PAIR(2));
		move(10,11);
		addch('B');
		refresh();		
		attroff(COLOR_PAIR(2));
	}
	move(15,15);
	addch('D');
	refresh();


	while(1);
	endwin();//退出curses模式
	return 0;
}
