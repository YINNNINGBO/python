#include "user.h"
void *pthread_text(void *)
{
    printf("创建的线程\n");
    sleep(1);
}
int main(int argc, const char **argv)
{
    pthread_t tid;
    if (pthread_create(&tid, NULL, pthread_text, NULL))
    {
        perror("pthread_create is error!");
        fprintf(stderr, "errno is %d\n", errno);
        _exit(EXIT_FAILURE);
    }
    // 分离子线程

    if (pthread_detach(tid))
    {
        perror("pthread_create is error!");
        fprintf(stderr, "errno is %d\n", errno);
        _exit(EXIT_FAILURE);
    }

    // 延长父线程时间，使子线程得以被回收
    sleep(3);
    puts("子线程被回收\n");

    return 0;
}