/*不要使用if(time.second % 60  = 0){event} 这种去做timer, 因为很有可能在指定时间时并没有处理到这一段*/
#include <sys/time.h>
static struct  timeval tv;
  /* ping to db */
      gettimeofday(&(tv), NULL);
      if(tv.tv_sec-last_ping > 300)
      {
         last_ping=tv.tv_sec;
      }
