#include <unistd.h>
#include <errno.h>

ssize_t readn(int fd, void *buf, size_t n) {
    size_t nleft = n;
    ssize_t nread;
    char *ptr = buf;
    
    while (nleft > 0) {
        nread = read(fd, ptr, nleft);
        if (nread == -1) {
            if (errno == EINTR)
                continue;  // 若读取被中断，则继续读取
            else
                return -1; // 发生其他错误
        } else if (nread == 0) {
            break;  // 读取结束，遇到文件结束符
        }
        
        nleft -= nread;
        ptr += nread;
    }
    
    return (n - nleft);  // 返回实际读取的字节数
}
