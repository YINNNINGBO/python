#include <stdio.h>
#include <curses.h>
int main(int argc, const char *argv[])
{
	char ch;
	initscr();								// 进入curses模式
	curs_set(0);							// 隐藏光标
	noecho();								// 禁止字符显示
	keypad(stdscr, 1);						// 允许使用功能键
	start_color();							// 启动颜色机制
	init_pair(1, COLOR_WHITE, COLOR_RED);	// 初始化颜色对1，前景色为白色，背景色为红色
	init_pair(2, COLOR_GREEN, COLOR_WHITE); // 初始化颜色对2，前景色为绿色，背景色为白色

	ch = getch(); // 获取用户输入的字符
	if (ch == 'Q')
	{
		attron(COLOR_PAIR(1));	// 启用颜色对1
		move(10, 10);			// 移动光标到(10, 10)位置
		addch('A');				// 在当前位置添加字符'A'
		refresh();				// 刷新屏幕，显示更改
		attroff(COLOR_PAIR(1)); // 关闭颜色对1
	}
	move(10, 10);	   // 移动光标到(10, 10)位置
	ch = (char)inch(); // 读取当前位置的字符
	if (ch == 'A')
	{
		attron(COLOR_PAIR(2));	// 启用颜色对2
		move(20, 21);			// 移动光标到(10, 11)位置
		addch('B');				// 在当前位置添加字符'B'
		refresh();				// 刷新屏幕，显示更改
		attroff(COLOR_PAIR(2)); // 关闭颜色对2
	}

	while (1)
		;	  // 无限循环，保持程序运行
	endwin(); // 退出curses模式
	return 0; // 返回0，表示程序正常结束
}
