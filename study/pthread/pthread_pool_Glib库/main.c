#include "user.h"
/*
创建线程池
    GThreadPool* g_thread_pool_new (GThreadFunc func,  gpointer user_data, gint max_threads, gboolean exclusive, GError **error);
    参数:>func :GThreadFunc（void (*func)(gpointer data, gpointer user_data)）
            data：     传递给线程池任务的数据，可以是任何类型的数据。
            user_data：传递给线程池创建时的附加用户数据。
        >user_data:传递给 func 中的 user_data 参数
        >max_threads:这个值决定了线程池最多同时运行多少个线程来处理任务
        >exclusive
            TRUE: 1 线程池中的线程是独占的，每个线程只会处理一个任务，不会共享任务（即，任务执行完成之前不会分配新的任务）。
            FALSE:0 线程池中的线程可以处理多个任务。
        >error:该参数将接收到错误信息。通常可以将其设置为 NULL
为线程池中添加任务：
    void g_thread_pool_push (GThreadPool * pool,gpointer data,GError * *error)
        pool：g_thread_pool_new  成功后的返回值
        data：g_thread_pool_new第一参数（函数指针）的第一个参数
        error： 同 g_thread_pool_new的
摧毁线程池：
    void g_thread_pool_free ( GThreadPool *pool,  gboolean immediate, gboolean wait);
        pool：g_thread_pool_new  成功后的返回值
        immediate：
            TRUE，表示立即销毁线程池并停止执行新的任务，不再添加任务到线程池。
            FALSE，线程池会等待所有任务执行完毕后再关闭。
        wait：
            TRUE，表示等待所有任务执行完成后再释放线程池。
            FALSE 则表示不等待任务完成，线程池会在任务仍在执行时立即销毁。
*/
void task_func(gpointer data, gpointer user_data)
{
    int tmp_num = *(int *)data;
    free(data);
    printf("开始执行%d任务\n", tmp_num);
    sleep(1);
    printf("%d任务完成\n", tmp_num);
    return;
}
int main(int argc, const char **argv)
{
    // 创建线程池
    GThreadPool *pool = g_thread_pool_new(task_func, NULL, 5, 1, NULL);
    // 像线程池中添加任务
    for (int i = 0; i < 10; i++)
    {
        int *tmp = malloc(sizeof(pool));
        *tmp = i + 1;
        g_thread_pool_push(pool, tmp, NULL);
    }
    g_thread_pool_free(pool, 0, 1);
    puts("所有任务都完成了");
    return 0;
}