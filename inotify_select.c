void monitor_redis_master()
{
  const char * filename = "redis_master.txt";
  unsigned char buf[1024] = {0};
  struct inotify_event *event = NULL;
  int fd = inotify_init();
  int wd = inotify_add_watch(fd, filename,  IN_MODIFY | IN_ATTRIB |IN_CLOSE_WRITE);

  while (1) {
       fd_set fds;
       FD_ZERO(&fds);
       FD_SET(fd, &fds);
       if (select(fd + 1, &fds, NULL, NULL, NULL) > 0){
                   int len, index = 0;
           while (((len = read(fd, &buf, sizeof(buf))) < 0) && (errno == EINTR));
           while (index < len) {
                  event = (struct inotify_event *)(buf + index);
                  read_redis_master();
                  index += sizeof(struct inotify_event) + event->len;
           }
       }
  }

  inotify_rm_watch(fd, wd);
  return 0;
}
