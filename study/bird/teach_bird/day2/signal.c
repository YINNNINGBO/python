#include <stdio.h>
#include <signal.h>

void handler(int sig)
{
	printf("HELLO\n");
	return;
}
int main(int argc, const char *argv[])
{
	signal(SIGINT, handler);

	while(1)
	{
		sleep(5);
		break;
	}
	return 0;
}
