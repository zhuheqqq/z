# project1:设计一个 C 语言的动态扩容缓冲区

[TOC]

![](/home/zhuheqin/图片/截图/截图 2023-01-04 17-15-13.png)

![](/home/zhuheqin/图片/截图/截图 2023-01-04 17-15-45.png)

![](/home/zhuheqin/图片/截图/截图 2023-01-04 17-16-16.png)

------

事实上，在很多优秀项目都会去封装一种接口，如 [redis](https://github.com/redis/redis/blob/unstable/src/sds.c),[git](https://github.com/git/git/blob/master/strbuf.c)。现在你的目标是重新造一遍在轮子（belong to you!）：

这个缓冲区类的定义就免费送给你们啦：

```c
struct strbuf {
  int len;     //当前缓冲区（字符串）长度
  int alloc;   //当前缓冲区（字符串）容量
  char *buf;   //缓冲区（字符串）
};
```

![](/home/zhuheqin/图片/截图/截图 2023-01-04 17-16-57.png)

------

## 任务正式开始！

### partA

![](/home/zhuheqin/图片/截图/截图 2023-01-04 17-13-44.png)

```c
//初始化 sb 结构体，容量为 alloc
void strbuf_init(struct strbuf *sb, size_t alloc) {
    sb->buf = (char *) malloc(sizeof(char) * (alloc + 1));//不能用. sb并非结构名称
    sb->len = 0;
    sb->alloc = alloc;
}

//将字符串填充到 sb 中，长度为 len, 容量为 alloc
void strbuf_attach(struct strbuf *sb, void *str, size_t len, size_t alloc) {
    sb->len = len;
    sb->alloc = alloc;
    //   int i,slen;
    //   slen=strlen(str);
    //   for(i=0;i<slen;i++){
    //     sb->buf[i]=str[i];
    //   }
    //   sb->buf[sb->len]='\0';
    sb->buf = (char *) str;
}

//释放 sb 结构体的内存
void strbuf_release(struct strbuf *sb) {
    free(sb->buf);
    //free(sb);
}

//交换两个 strbuf
void strbuf_swap(struct strbuf *a, struct strbuf *b) {
    int num1;
    char *num2;

    num1 = a->len;
    a->len = b->len;
    b->len = num1;

    num1 = a->alloc;
    a->alloc = b->alloc;
    b->alloc = num1;

    num2 = a->buf;
    a->buf = b->buf;
    b->buf = num2;
}

//将 sb 中的原始内存取出，并将 sz 设置为其 alloc 大小
char *strbuf_detach(struct strbuf *sb, size_t *sz) {
    *sz = sb->alloc;
    return sb->buf;
    //返回字符串
}

//比较两个 strbuf 的内存是否相同
int strbuf_cmp(const struct strbuf *first, const struct strbuf *second) {
    if (first->len > second->len) {
        return 1;
    } else if (first->len < second->len) {
        return -1;
    } else {
        return 0;
    }
}

//清空sb
void strbuf_reset(struct strbuf *sb) {
    for(int i=0;i<sb->len;i++)
    {
    sb->buf[i]='\0';
    }
    sb->len=0;
}
```

### partB

![](/home/zhuheqin/图片/截图/截图 2023-01-04 17-18-52.png)

```c
//确保在 len 之后 strbuf 中至少有 extra 个字节的空闲空间可用
void strbuf_grow(struct strbuf *sb, size_t extra) {
    sb->buf = (char *) realloc(sb->buf, sb->len + extra + 1);
    if (sb->alloc < sb->len + extra + 1) {
        sb->alloc = sb->len + extra + 1;
    }
}

//向 sb 追加长度为 len 的数据 data
void strbuf_add(struct strbuf *sb, const void *data, size_t len) {
    if(len==0)
    {
	    return;
    }
    if(sb->len+len>=sb->alloc)
    {
        sb->buf=(char *)realloc(sb->buf,sb->len+len+1);
        sb->alloc=sb->len+len+1;
    }
    memcpy(sb->buf+sb->len,data,len);
    sb->len+=len;
    sb->buf[sb->len]='\0';
}

//向 sb 追加一个字符 c
void strbuf_addch(struct strbuf *sb, int c) {
  // if(sb->alloc==0){
  //   sb->alloc=2;
  // }else{
  //   if (sb->alloc < sb->len+1) {
  //       sb->alloc = sb->alloc * 2;
  //   }
  // }
  //   sb->len += 1;
  //   sb->buf = (char *) realloc(sb->buf, sb->alloc);
  //   sb->buf[sb->len-1] = c;
  //   sb->buf[sb->len] = '\0';
  if(sb->alloc==0){
        sb->alloc=2;
    }
    else{
        if(sb->alloc<=sb->len+2)
        {
            sb->alloc*=2;
        }
    }
  sb->buf=(char*)realloc(sb->buf,(sb->alloc));
  sb->len+=1;
  sb->buf[sb->len-1]=c;
  sb->buf[sb->len]='\0';
}

//向 sb 追加一个字符串 s
void strbuf_addstr(struct strbuf *sb, const char *s) {
    // while (sb->alloc < sb->len + strlen(s)+1) {
    //     sb->alloc *= 2;
    // }
    // sb->buf = (char *) realloc(sb->buf, sb->len + strlen(s) + 1);
    // int len=strlen(s);
    // sb->len+=len;
    // memcpy(sb->buf,s,len);
    strbuf_add(sb,s,strlen(s));
    //sb->buf[sb->len]='\0';
}

//向一个 sb 追加另一个 strbuf的数据
void strbuf_addbuf(struct strbuf *sb, const struct strbuf *sb2) {
    strbuf_addstr(sb, sb2->buf);
}

//设置 sb 的长度 len
void strbuf_setlen(struct strbuf *sb, size_t len) {
    // if (sb->alloc < len + 1) {
    //     sb->alloc = len + 1;
    // }
    sb->len = len;
    //sb->buf = (char *) realloc(sb->buf, sb->len);
    sb->buf[sb->len] = '\0';
}

//计算 sb 目前仍可以向后追加的字符串长度
size_t strbuf_avail(const struct strbuf *sb) {
    return sb->alloc - sb->len - 1;
}

//向 sb 内存坐标为 pos 位置插入长度为 len 的数据 data
void strbuf_insert(struct strbuf *sb, size_t pos, const void *data, size_t len) {
    sb->len += len;
    if (sb->alloc < sb->len + 1) {
        sb->alloc = sb->len + 1;
    }
    sb->buf = (char *) realloc(sb->buf, sb->alloc + 1);
    char *p = (char *) malloc(sizeof(char) * (sb->len));
    // char *t = (char *) malloc(sizeof(char) * (sb->len));
    // char *s = (char *) malloc(sizeof(char) * (sb->len));
    // int cnt=0;
    // t = sb->buf;
    // while (t <= sb->buf + pos) {
    //     *s = *t;
    //     t++;
    //     s++;
    // }
    // s[pos+1]='\0';
    // while (*t != '\0') {
    //     *p = *t;
    //     t++;
    //     p++;
    //     cnt++;
    // }
    // p[cnt+1]='\0';
    // strcat(s, (const char *) data);
    // strcat(s, p);
    // sb->buf=s;
    strcpy(p,sb->buf+pos);
    strcpy(sb->buf+pos,(const char*)data);
    strcat(sb->buf,p);
    free(p);
}
```

### partC

![](/home/zhuheqin/图片/截图/截图 2023-01-04 17-20-28.png)

```c
//去除 sb 缓冲区左端的所有 空格，tab, '\t'
void strbuf_ltrim(struct strbuf *sb) {
    char *s = sb->buf;//, *p = sb->buf;
    while (*s != '\0' && (*s == ' ' || *s == '\t')) {
        s++;
        sb->len--;
    }
    memmove(sb->buf,s,sb->len);
    // while (*s != '\0') {
    //     *p++ = *s++;
    // }
    // p[sb->len] = '\0';
    // sb->buf = p;
}

//去除 sb 缓冲区右端的所有 空格，tab, '\t'
void strbuf_rtrim(struct strbuf *sb) {
    while (sb->buf[sb->len-1] == ' ' || sb->buf[sb->len-1] == '\t') {
        sb->len--;
    }
    sb->buf[sb->len] = '\0';
}

// 删除 sb 缓冲区从 pos 坐标长度为 len 的内容
void strbuf_remove(struct strbuf *sb, size_t pos, size_t len) {
    // char *p = (char *) malloc(sizeof(char) * (sb->len));
    // char *t = (char *) malloc(sizeof(char) * (sb->len));
    // t = sb->buf + pos + len;
    // strcpy(p, sb->buf + pos + len);
    // sb->len = pos + len;
    // while (t != sb->buf + pos - 1) {
    //     sb->len--;
    //     t--;
    // }
    // sb->buf[sb->len] = '\0';
    // strcat(sb->buf, p);
    // sb->len -= len;
    memmove(sb->buf+pos,sb->buf+pos+len,sb->len-len-pos);
    sb->len=sb->len-len;
}
```

### partD

![](/home/zhuheqin/图片/截图/截图 2023-01-04 17-51-01.png)

```c
//sb 增长 hint ? hint : 8192 大小， 然后将文件描述符为 fd 的所有文件内容追加到 sb 中
ssize_t strbuf_read(struct strbuf *sb, int fd, size_t hint) {
    sb->buf = (char *) realloc(sb->buf, (sb->alloc += hint ? hint : 8192));
    sb->alloc += hint ? hint : 8192;
    FILE *fp = fdopen(fd, "r");
    if (fp != NULL) {
        char ch;
        while ((ch = fgetc(fp)) != EOF) {
            sb->buf[sb->len++] = ch;
        }
        sb->buf[sb->len] = '\0';
    }
    return sb->len;
}

//将 将文件句柄为 fp 的一行内容（抛弃换行符）读取到 sb   检查长度是否超过缓冲区
int strbuf_getline(struct strbuf *sb, FILE *fp) {
        int ch;
        //int count=0;
        while ((ch = fgetc(fp)) != EOF) {
          if( (ch == '\n')||(feof(fp)!=0)){
            break;
          }
          if((strbuf_avail(sb)>=1)){
            strbuf_addch(sb,ch);
            
          }else if((strbuf_avail(sb)<1)){
            sb->buf = (char *) realloc(sb->buf, sb->alloc+1);
            strbuf_addch(sb,ch);
            // sb->alloc+=1;
            // sb->buf[sb->len++] = ch;
          }
            // sb->buf = (char *) realloc(sb->buf, sb->alloc);
            // sb->buf[sb->len++] = ch;
        }
        //sb->buf[sb->len] = '\0';
    return sb->len;
}
```

### 无信用挑战

![](/home/zhuheqin/图片/截图/截图 2023-01-04 17-53-11.png)

```c
//将长度为 len 的字符串 str 根据切割字符 terminator 切成多个 strbuf,并从结果返回，max 可以用来限定最大切割数量。
//返回 struct strbuf 的指针数组，数组的最后元素为 NULL
struct strbuf **strbuf_split_buf(const char *str, size_t len, int terminator, int max) {
    struct strbuf **buf_link = (struct strbuf **) malloc(sizeof(struct strbuf *) * (max+1));
    const char *end=str+len;
    const char *head=str;
    const char *p;
    int count=0;
    while(*head==terminator){
      head++;
    }
    for (p=head;p<=end;p++) {
        if (*p==terminator||p==end) {
            int len_tmp;
            len_tmp=p-head;
            buf_link[count]=(strbuf*)malloc(sizeof(strbuf));//!
            buf_link[count]->len=len_tmp;
            buf_link[count]->alloc=len_tmp+1;
            buf_link[count]->buf=(char *)malloc(sizeof(char)*(len_tmp+1));//for '\0'
            memcpy(buf_link[count]->buf,head,len_tmp);
            buf_link[count]->buf[len_tmp]='\0';
            count++;
            //buf_link[count++]->buf[len_tmp]='\0';
            while (*p==terminator&&p<=end){
              p++;
            }
            head=p;
        }
        if (count==max)
            break;
    }
    buf_link[count]=NULL;
    return buf_link;
}


//target_str : 目标字符串，str : 前缀字符串，strlen : target_str 长度 ，前缀相同返回 true 失败返回 false
bool strbuf_begin_judge(char *target_str, const char *str, int len) {
    int i;
    // for (i = 0; i < strlen(str); i++) {
    //   if(len==0){
    //     return true;
    //   }
    //   if(strlen(str)>len){
    //     return false;
    //   }
    //     if (target_str[i] != str[i]) {
    //         //flag=1;
    //         return false;
    //     }
    // }
    // // if(flag==0){
    // //   return true;
    // // }
    // return true;
    if (len == 0)
        return true;
    if (strlen(str) > len)
        return false;
    for (int i = 0; i < strlen(str); i++) {
        if (str[i] != target_str[i]) {
            return false;
        }
    }
    return true;
}


//target_str : 目标字符串，begin : 开始下标，end 结束下标。
//len : target_buf的长度，参数不合法返回 NULL. 下标从0开始，[begin, end)区间。
char *strbuf_get_mid_buf(char *target_buf, int begin, int end, int len) {
    if (begin < 0 || end < 0 || end > len || len < 0) {
        return NULL;
    } else {
        char *p = (char *) malloc(sizeof(char *) * (end - begin + 1));
        int i = begin, j = 0;
        for (i = begin, j = 0; i < end; i++, j++) {
            *(p + j) = *(target_buf + i);
        }
        //memcpy(p, target_buf + begin, end - begin);
        p[end - begin] = '\0';
        return p;
    }
}
```

