int DeleteWord(WHString del,WHString *head)
{
    int pos=1,line=1,count=0,len,i,back,next[MAXLEN],nextval[MAXLEN];
    int delrow[MAXLEN]={0},delline[MAXLEN]={0};
    int delnum=0;//记录删除的串编号
    WHString *CurrentLine,End;
    HStrInit(&End);
    HStrAssign(&End,"#");
    printf("\n\n\t 您需要删除的字符或字符串是：");
    HStrOutput(del);
    CurrentLine=head;
    len=del.len;
    HGet_NextVal(del,next,nextval);//计算模式串的nextval函数值
    while(O!=HStrCompare(*CurrentLine,End))
    {
        pos=1;
        do{
            pos=HStrKMP(*CurrentLine,del,pos,next);
            if(O!=pos)
            {
                delline[count]=line;//将可删除的位置逐一存入数组中
                delrow[count]=pos;
                count++;
                pos=pos+len;
            }
        }while(O!=pos);
        CureentLine=CurrentLine->next;//指向文本下一行
        line++;
    }
    if(O==count)
    {
        printf("\n\t\t 没有找到您需要删除的字符或字符串\n");
        return 0;
    }else{
        printf("\n\t\t 您需要删除的串：\n");
        for(i=0;i<count;i++)
        {
            printf("\n第%d个存在于:行:%d 列:%d",i+1,delline[i],delrow[i]);
        }
        printf("\n\n\t\t 请输入您要删除的串编号:\n");
        scanf("%d",&delnum);//输入要删除的串的编号
        if(delnum>count)//输入的串编号大于可删除的串的总个数
        {
            printf("\n\t\t 输入有误！\n\t\t");
            return 0;
        }
        CurrentLine=head;
        i=1;line=1;
        while(1)
        {
            if(delline[delnum-1]==line)
            {
                printf("\n已删除第%d哥，位于行：%d列：%d\n",
                    delnum,delline[delnum-1],delrow[delnum-1]);
                HStrDelete(CurrentLine,delrow[delnum-1],len);
                break;
            }else{
                CurrentLine=CurrentLine->next;//指向文本下一行
                line++;//文本行号累加
            }
        }
    }
    return 1;
}