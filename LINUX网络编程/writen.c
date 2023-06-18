#include <unistd.h>
#include <errno.h>

ssize_t writen(int fd, const void *buf, size_t n) {
    size_t nleft = n;
    ssize_t nwritten;
    const char *ptr = buf;
    
    while (nleft > 0) {
        nwritten = write(fd, ptr, nleft);
        if (nwritten <= 0) {
            if (nwritten == -1 && errno == EINTR)
                continue;  // 若写入被中断，则继续写入
            else
                return -1; // 发生其他错误
        }
        
        nleft -= nwritten;
        ptr += nwritten;
    }
    
    return n;  // 返回实际写入的字节数
}
