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
#include<assert.h>
struct strbuf {
  int len;     //当前缓冲区（字符串）长度
  int alloc;   //当前缓冲区（字符串）容量
  char *buf;   //缓冲区（字符串）
};
void strbuf_init(struct strbuf *sb, size_t alloc);
void strbuf_attach(struct strbuf *sb, void *str, size_t len, size_t alloc);
void strbuf_release(struct strbuf *sb);
void strbuf_swap(struct strbuf *a, struct strbuf *b);
char *strbuf_detach(struct strbuf *sb, size_t *sz);
int strbuf_cmp(const struct strbuf *first, const struct strbuf *second);
void strbuf_reset(struct strbuf *sb);
void strbuf_grow(struct strbuf *sb, size_t extra);
void strbuf_add(struct strbuf *sb, const void *data, size_t len);
void strbuf_addch(struct strbuf *sb, int c);
void strbuf_addstr(struct strbuf *sb, const char *s);
void strbuf_addbuf(struct strbuf *sb, const struct strbuf *sb2);
void strbuf_setlen(struct strbuf *sb, size_t len);
size_t strbuf_avail(const struct strbuf *sb);
void strbuf_insert(struct strbuf *sb, size_t pos, const void *data, size_t len);
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
  //free(sb);
}

//交换两个 strbuf
void strbuf_swap(struct strbuf *a, struct strbuf *b)
{
  int num1;
  char *num2;
  
  num1=a->len;
  a->len=b->len;
  b->len=num1;

  num1=a->alloc;
  a->alloc=b->alloc;
  b->alloc=num1;

  num2=a->buf;
  a->buf=b->buf;
  b->buf=num2;
}

//将 sb 中的原始内存取出，并将 sz 设置为其 alloc 大小
char *strbuf_detach(struct strbuf *sb, size_t *sz)
{
  *sz=sb->alloc;
  return sb->buf;
//返回字符串
}

//比较两个 strbuf 的内存是否相同
int strbuf_cmp(const struct strbuf *first, const struct strbuf *second)
{
  if(first->len>second->len){
    return 1;
  }else if(first->len<second->len){
    return -1;
  }else{
    return 0;
  }

}

//清空sb
void strbuf_reset(struct strbuf *sb)
{
  if(sb==NULL)
  {
    return;
  }
  strbuf_init(sb,sb->alloc);

}

//确保在 len 之后 strbuf 中至少有 extra 个字节的空闲空间可用
void strbuf_grow(struct strbuf *sb, size_t extra)
{
  sb->buf=(char *)realloc(sb->buf,sb->len+extra);
  if(sb->alloc<sb->len+extra){
    sb->alloc=sb->len+extra;
  }

}

//向 sb 追加长度为 len 的数据 data
void strbuf_add(struct strbuf *sb, const void *data, size_t len)
{
  if(len==0){
    return;
  }else{
    sb->len+=len;
    while(sb->alloc<len+sb->len)
    {
      sb->alloc*=2;
    }
    sb->buf=(char *)realloc(sb->buf,sb->len);
    strcat(sb->buf,(const char*)data);
    sb->buf[sb->len]='\0';
  }

}

//向 sb 追加一个字符 c
void strbuf_addch(struct strbuf *sb, int c)
{
  sb->len+=1;
  if(sb->alloc<sb->len)
  {
    sb->alloc=sb->alloc*2;
  }
  sb->buf=(char*)realloc(sb->buf,sb->len);
  sb->buf[sb->len-1]=c;
  sb->buf[sb->len]='\0';

}

//向 sb 追加一个字符串 s
void strbuf_addstr(struct strbuf *sb, const char *s)
{
  while(sb->alloc<=sb->len+strlen(s))
  {
    sb->alloc*=2;
  }
  sb->buf=(char *)realloc(sb->buf,sb->len+strlen(s)+1);
  strcat(sb->buf,s);

}

//向一个 sb 追加另一个 strbuf的数据
void strbuf_addbuf(struct strbuf *sb, const struct strbuf *sb2)
{
  strbuf_addstr(sb,sb2->buf);
}

//设置 sb 的长度 len
void strbuf_setlen(struct strbuf *sb, size_t len)
{
  if(sb->alloc<len+1){
    sb->alloc=len+1;
  }
  sb->len=len;
  sb->buf=(char *)realloc(sb->buf,sb->len);
  sb->buf[sb->len]='\0';

}

//计算 sb 目前仍可以向后追加的字符串长度
size_t strbuf_avail(const struct strbuf *sb)
{
  return sb->alloc-sb->len;

}

//向 sb 内存坐标为 pos 位置插入长度为 len 的数据 data
void strbuf_insert(struct strbuf *sb, size_t pos, const void *data, size_t len)
{
  sb->len+=len;
  if(sb->alloc<sb->len+1){
    sb->alloc=sb->len+1;
  }
  sb->buf=(char *)realloc(sb->buf,sb->len+1);
  char *p=(char *)malloc(sizeof(char)*(sb->len));
  
}