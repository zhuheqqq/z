// strbuf_test2.c
// #include <stdio.h>
// #include <string.h>
// #include <stdlib.h>

// int main() {
//   int len = 5;
//   char *str = malloc(sizeof(char) * len);
//   memcpy(str, "xiyou", 5);
//   str = realloc(str, len + strlen("linux") + 1);
//   strcpy(str + 5, "linux");
//   printf("%s\n", str);
// }
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
struct strbuf {
  int len;     //当前缓冲区（字符串）长度
  int alloc;   //当前缓冲区（字符串）容量
  char *buf;   //缓冲区（字符串）
};
void strbuf_init(struct strbuf *sb, size_t alloc);
void strbuf_attach(struct strbuf *sb, void *str, size_t len, size_t alloc);
void strbuf_release(struct strbuf *sb);
int main() {
  struct strbuf sb;
  strbuf_init(&sb, 10);
  strbuf_attach(&sb, "xiyou", 5, 10);
  assert(strcmp(sb.buf, "xiyou") == 0);
  strbuf_addstr(&sb, "linux");
  assert(strcmp(sb.buf, "xiyoulinux") == 0);
  strbuf_release(&sb);
}

//初始化 sb 结构体，容量为 alloc
void strbuf_init(struct strbuf *sb, size_t alloc)
{
  sb->buf=(char *)malloc(sizeof(char)*(alloc+1));//不能用. sb并非结构名称
  sb->len=0;
  sb->alloc=alloc;
}

//将字符串填充到 sb 中，长度为 len, 容量为 alloc
void strbuf_attach(struct strbuf *sb, void *str, size_t len, size_t alloc)
{
  sb->len=len;
  sb->alloc=alloc;
  strcpy(sb->buf,str);//加头文件string.h

}

//释放 sb 结构体的内存
void strbuf_release(struct strbuf *sb)
{
  free(sb->buf);
  free(sb);
}