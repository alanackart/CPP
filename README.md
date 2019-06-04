# CPP
c/cpp code snippets and programs

- posix mmap() 共享内存：[mmap_normalfile1.c](https://github.com/alanackart/CPP/blob/master/mmap_normalfile1.c)     [mmap_normalfile2.c](https://github.com/alanackart/CPP/blob/master/mmap_normalfile2.c) [阅读链接](https://www.ibm.com/developerworks/cn/linux/l-ipc/part5/index1.html)
- thread functions demo: [thread_helloworld.c](https://github.com/alanackart/CPP/blob/master/thread_helloworld.c)  [further reading](http://zhangxiaoya.github.io/2015/05/15/multi-thread-of-c-program-language-on-linux/)
- 多线程访问写同一数据（无锁）， 注意， 单个线程所处理的事情越多， 特别是IO及SLEEP的情形都会使得同一时刻访问数据的线程数减少， 从而使得执行结果更接近顺序执行。[thread_no_mutex.c](https://github.com/alanackart/CPP/blob/master/thread_no_mutex.c)
- 多线程使用**mutex** 锁机制来保证同一时刻仅有一个线程处于**竞争区域(critical region)**， [thread_with_mutex.c](https://github.com/alanackart/CPP/blob/master/thread_with_mutex.c)

