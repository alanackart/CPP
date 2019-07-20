#ifndef __LOG_H__
#define __LOG_H__

#include <sys/time.h>
#include <time.h>
#include <pthread.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/syscall.h>



#define LogMessage(fmt, arg...) fprintf(stderr, "%s: " fmt, __FUNCTION__, ##arg)

#if 0
#define NameLogWithTime(fmt, fname, log_level, arg...)                                 \
  do                                                                                   \
  {                                                                                    \
    char sys_time[15];                                                                 \
    time_t t;                                                                          \
    struct tm *local;                                                                  \
    t = time(NULL);                                                                    \
    local = localtime(&t);                                                             \
    sprintf(sys_time, "%02d:%02d:%02d", local->tm_hour, local->tm_min, local->tm_sec); \
    fprintf(stderr, "%s: %s[%s]: " fmt, fname, log_level, sys_time, ##arg);            \
  } while (0)

#define LogWithTime(fmt, log_level, arg...) \
  NameLogWithTime(fmt, __FUNCTION__, log_level, ##arg)
#endif

#define NameLogWithTime(fmt, fname, file, line, log_level, arg...)                                                                                      \
  do                                                                                                                                                    \
  {                                                                                                                                                     \
    char sys_time[15];                                                                                                                                  \
    time_t t;                                                                                                                                           \
    struct tm *local;                                                                                                                                   \
    struct timeval tv;                                                                                                                                  \
    t = time(NULL);                                                                                                                                     \
    gettimeofday(&tv, NULL);                                                                                                                            \
    local = localtime(&t);                                                                                                                              \
    sprintf(sys_time, "%02d:%02d:%02d.%03ld", local->tm_hour, local->tm_min, local->tm_sec, tv.tv_usec / 1000);                                         \
    fprintf(stderr, "%s[%s:%d]: %s[%s] [pid:%ld, tid:%ld]: " fmt, fname, file, line, log_level, sys_time, (long)getpid(), (long)syscall(__NR_gettid), ##arg); \
  } while (0)

#define LogWithTime(fmt, log_level, arg...) \
  NameLogWithTime(fmt, __FUNCTION__, __FILE__, __LINE__, log_level, ##arg)

#define LogError(fmt, arg...) LogWithTime(fmt, "ERROR", ##arg)
#define LogInfo(fmt, arg...) LogWithTime(fmt, "INFO", ##arg)
#define LogWarn(fmt, arg...) LogWithTime(fmt, "WARN", ##arg)

#endif
