select函数详解

1. 函数原型：
   int select(int nfds, fd_set *readfds, fd_set *writefds,
              fd_set *exceptfds, struct timeval *timeout);

2. 参数说明：
   - nfds: 最大文件描述符值加1
   - readfds: 要监视可读的文件描述符集合
   - writefds: 要监视可写的文件描述符集合
   - exceptfds: 要监视异常的文件描述符集合
   - timeout: 超时时间

3. 相关宏：
   - FD_ZERO(fd_set *set): 清空集合
   - FD_SET(int fd, fd_set *set): 添加文件描述符
   - FD_CLR(int fd, fd_set *set): 移除文件描述符
   - FD_ISSET(int fd, fd_set *set): 检查文件描述符是否在集合中

4. 使用示例：
   fd_set read_fds;
   FD_ZERO(&read_fds);
   FD_SET(sockfd, &read_fds);

   struct timeval tv;
   tv.tv_sec = 5;
   tv.tv_usec = 0;

   int ret = select(sockfd + 1, &read_fds, NULL, NULL, &tv);
   if (ret > 0) {
       if (FD_ISSET(sockfd, &read_fds)) {
           // sockfd有数据可读
       }
   }

5. 注意事项：
   - 最大支持1024个文件描述符
   - 每次调用都需要重新设置文件描述符集合
   - 适合监视少量文件描述符的场景
   - 性能随着文件描述符数量增加而下降

poll函数详解

1. 函数原型：
   int poll(struct pollfd *fds, nfds_t nfds, int timeout);

2. 参数说明：
   - fds: 指向pollfd结构体数组的指针，每个元素描述一个要监视的文件描述符
   - nfds: fds数组的元素个数
   - timeout: 超时时间，单位毫秒。负数表示无限等待，0表示立即返回

3. pollfd结构体：
   struct pollfd {
       int fd;         // 文件描述符
       short events;   // 要监视的事件
       short revents;  // 实际发生的事件
   };

4. 事件标志：
   - POLLIN: 有数据可读
   - POLLOUT: 可写数据
   - POLLERR: 发生错误
   - POLLHUP: 连接挂起
   - POLLNVAL: 无效请求

5. 返回值：
   - 成功：返回就绪的文件描述符数量
   - 超时：返回0
   - 错误：返回-1，并设置errno

6. 使用示例：
   struct pollfd fds[2];
   fds[0].fd = sockfd1;
   fds[0].events = POLLIN;
   fds[1].fd = sockfd2; 
   fds[1].events = POLLOUT;

   int ret = poll(fds, 2, 1000);
   if (ret > 0) {
       if (fds[0].revents & POLLIN) {
           // sockfd1有数据可读
       }
       if (fds[1].revents & POLLOUT) {
           // sockfd2可写
       }
   }

7. 注意事项：
   - 与select相比，poll没有最大文件描述符限制
   - 每次调用都需要遍历整个fds数组
   - 适合监视少量文件描述符的场景
   - 对于大量文件描述符，epoll性能更好

epoll函数详解

1. epoll函数族：
   :********************************** 创建epoll实例
   - int epoll_create(int size); /int epoll_create1(int flags);
   return : 返回一个文件描述符，用于epoll_ctl和epoll_wait操作

   :**********************************添加/修改/删除要监视的文件描述符
   - int epoll_ctl(int epfd, int op, int fd, struct epoll_event *event);
   函数参数：
      epfd：epoll_create() 函数的返回值, 通过这个参数找到epoll实例
      op：这是一个枚举值，控制通过该函数执行什么操作
         EPOLL_CTL_ADD：往epoll模型中添加新的节点
         EPOLL_CTL_MOD：修改epoll模型中已经存在的节点
         EPOLL_CTL_DEL：删除epoll模型中的指定的节点
      fd：文件描述符，即要添加/修改/删除的文件描述符
      event：epoll事件，用来修饰第三个参数对应的文件描述符的，指定检测这个文件描述符的什么事件
            struct epoll_event {
                  uint32_t     events;      /* Epoll events */
                  epoll_data_t data;        /* User data variable */
            };
            typedef union epoll_data {
                  void        *ptr;
                  int          fd;
                  uint32_t     u32;
                  uint64_t     u64;
            } epoll_data_t;
         events：委托epoll检测的事件
            EPOLLIN：读事件, 接收数据, 检测读缓冲区，如果有数据该文件描述符就绪
            EPOLLOUT：写事件, 发送数据, 检测写缓冲区，如果可写该文件描述符就绪
            EPOLLERR：异常事件
         data：用户数据变量，这是一个联合体类型，通常情况下使用里边的fd成员，用于存储待检测的文件描述符的值，在调用epoll_wait()函数的时候这个值会被传出。
      函数返回值：
      失败：返回-1
      成功：返回0

   : ************************************等待事件发生  
   - int epoll_wait(int epfd, struct epoll_event *events,int maxevents, int timeout);
   函数参数：
      epfd：epoll_create() 函数的返回值, 通过这个参数找到epoll实例
      events：传出参数, 这是一个结构体数组的地址, 里边存储了已就绪的文件描述符的信息
      maxevents：修饰第二个参数, 结构体数组的容量（元素个数）
      timeout：如果检测的epoll实例中没有已就绪的文件描述符，该函数阻塞的时长, 单位ms 毫秒
         0：函数不阻塞，不管epoll实例中有没有就绪的文件描述符，函数被调用后都直接返回
         >0：如果epoll实例中没有已就绪的文件描述符，函数阻塞对应的毫秒数再返回
         -1：函数一直阻塞，直到epoll实例中有已就绪的文件描述符之后才解除阻塞
   函数返回值：
      成功：
         等于0：函数是阻塞被强制解除了, 没有检测到满足条件的文件描述符
         大于0：检测到的已就绪的文件描述符的总个数
      失败：返回-1




2. 主要优点：
   - 使用红黑树存储文件描述符，查找效率高
   - 使用事件驱动机制，只返回就绪的文件描述符
   - 支持边缘触发(ET)和水平触发(LT)模式
   - 适合处理大量并发连接

3. 使用步骤：
   a. 创建epoll实例：
      int epollfd = epoll_create1(0);
   
   b. 添加监视的文件描述符：
      struct epoll_event ev;
      ev.events = EPOLLIN | EPOLLET; // 监视读事件，边缘触发模式
      ev.data.fd = sockfd;
      epoll_ctl(epollfd, EPOLL_CTL_ADD, sockfd, &ev);

   c. 等待事件：
      struct epoll_event events[MAX_EVENTS];
      int nfds = epoll_wait(epollfd, events, MAX_EVENTS, -1);
      for (int i = 0; i < nfds; i++) {
          if (events[i].events & EPOLLIN) {
              // 处理读事件
          }
      }

4. 触发模式：
   - 水平触发(LT)：只要文件描述符就绪就会通知
   - 边缘触发(ET)：只在状态变化时通知一次

5. 注意事项：
   - 适合高并发场景
   - 需要配合非阻塞IO使用
   - 注意处理EAGAIN错误
   - 及时移除已关闭的文件描述符


/**********************************tcp保活机制***************************/
int keepalive = 1;         // 启用保活
int keepidle = 60;         // 60 秒无活动后开始探测
int keepintvl = 10;        // 每 10 秒发送一次探测包
int keepcnt = 3;           // 最多探测 3 次

// 启用保活
setsockopt(sockfd, SOL_SOCKET, SO_KEEPALIVE, &keepalive, sizeof(keepalive));

// 调整保活参数（需使用 IPPROTO_TCP）
setsockopt(sockfd, IPPROTO_TCP, TCP_KEEPIDLE, &keepidle, sizeof(keepidle));
setsockopt(sockfd, IPPROTO_TCP, TCP_KEEPINTVL, &keepintvl, sizeof(keepintvl));
setsockopt(sockfd, IPPROTO_TCP, TCP_KEEPCNT, &keepcnt, sizeof(keepcnt));
1. TCP 保活机制的作用
   发现失效连接：
   当连接长时间无数据交互时，通过发送保活探测包（Keepalive Probe），确认对端是否存活。

   自动清理僵尸连接：
   若探测失败，关闭无效连接，释放端口、内存等资源。

   应对中间设备超时：
   防止 NAT 路由器、防火墙等中间设备因超时断开空闲连接（如 5 分钟无数据则断连）。