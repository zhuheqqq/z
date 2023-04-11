1.pthread_mutex_t lock;创建锁
2.pthread_mutex_init;初始化
3.pthread_mutex_lock;加锁
4.访问共享数据(stdout)
5.pthread_mutex_unlock();解锁
6.pthread_mutex_destroy;销毁锁
restrict关键字:
    用来限定指针变量,被限定的的指针变量所指向的内存操作,必须有本指针完成