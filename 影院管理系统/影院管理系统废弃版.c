#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<unistd.h>

int Login();      // 注册登陆模块
void Directory(); // 打印影院功能目录
int Choose();     // 选择功能函数
void Search();    // 电影查询

typedef struct a
{
    char name[100];          // 电影名
    double grade;            // 豆瓣评分
    int number;              // 一天场次
    int time;             // 时长
    int hall;                // 展厅
    char publish[100];       // 出版公司
    int price;            // 票价
    //char timeline[100][100]; // 时间段
    struct a *next;
}Linklist;

Linklist *head=NULL;

// 用户注册登陆
int Login()
{
    int choice;
    char fusername[100], fpassword[100];
    char username[100], password[100];

    while (1)
    {
        printf("*********************************************************\n");
        printf("*\t\t1.用户注册\t\t\t        *\n");
        printf("*\t\t2.用户登录\t\t\t        *\n");
        printf("*********************************************************\n");

        printf("请输入您的选项:");
        scanf("%d", &choice);

        if (choice == 1)
        {
            FILE *fp1 = fopen("user.txt", "w");
            printf("请输入用户名:");
            scanf("%s", username);
            printf("请输入数字密码(建议8位):");
            scanf("%s", password);

            fprintf(fp1, "%s %s", username, password);
            fclose(fp1);

            printf("注册成功！\n");

           system("cls"); // 防闪退
            return 1;
        }
        else if (choice == 2)
        {
            FILE *fp2 = fopen("user.txt", "r");
            printf("请输入用户名:");
            scanf("%s", username);
            printf("请输入您的密码:");
            getchar(); // 吸收回车防止对c造成影响

            /*char c[100];
            c=getpass("Password:");*/
            char c;
            int i = 0;
            while (1)
            {
                system("stty -echo"); // 密码不回显
                c = getchar();
                system("stty echo"); // getch平替
                if (c != '\n')
                {
                    password[i] = c;
                    i++;
                    printf("*"); // 密码保护
                }else
                {
                    break;
                }
            }
            // password=getpass("Input your passwords:");
            // printf("%s/r/n",password);
            printf("\n");
            password[i] = '\0';

            fscanf(fp2, "%s %s", fusername, fpassword);//此步正确
           // printf("%s %s",username,password);

            if ((strcmp(fusername, username) == 0) && (strcmp(fpassword, password) == 0))
            { // 验证用户名及密码
                printf("登陆成功！\n");
                system("cls"); // 防止闪退
                return 1;
            }
            else
            {
                printf("用户名或密码错误！\n");
                system("cls");
                return 0;
            }
        }
    }
    printf("\n");
}

// 影院功能目录
void Directory()
{
    printf("*********************************************************\n");
    printf("*\t\t欢迎使用影院管理系统\t\t\t*\n");
    printf("*********************************************************\n");
    printf("*\t\t   功能展示如下\t\t\t        *\n");
    printf("---------------------------------------------------------\n");
    printf("*\t\t1.添加电影信息\t\t\t        *\n");
    printf("*\t\t2.删除电影信息\t\t\t        *\n");
    printf("*\t\t3.修改电影信息\t\t\t        *\n");
    printf("*\t\t4.修改电影信息\t\t\t        *\n");
    printf("*\t\t5.删除所有电影信息\t\t\t        *\n");
    printf("*\t\t6.显示所有电影信息\t\t        *\n");
    printf("*\t\t7.排序\t\t\t                *\n");
    printf("*\t\t8.保存\t\t\t                *\n");
    printf("*\t\t0.退出\t\t\t                *\n");
    printf("*********************************************************\n");
    printf("请选择您需要的功能：");
}

// int Choose()
// {
//     int n;
//     printf("请输入您想选择的功能序号：");
//     while (scanf("%d", &n) != 1 || n < 0 || n > 6)
//     {
//         printf("\n输入错误,请重新输入:");
//         scanf("%d", &n);
//     }

//     return n;
// }


//1.录入电影信息
Linklist *input()
{
    int i, n;
    Linklist *head , *node, *end;
    head = (Linklist *)malloc(sizeof(Linklist));
    end = head; // 尾插法
    do
    {
        system("clear");
        node = (Linklist *)malloc(sizeof(Linklist));

        printf("*********************************************************\n");
        printf("*\t\t欢迎进入电影信息录入界面\t\t*\n");
        printf("*********************************************************\n");

        printf("*\t\t请输入电影名称                \t\t*\n");
        //printf("\t\t\t");
        scanf("%s", node->name);

        printf("*\t\t请录入电影评分(可为小数）\t\t*\n");
        printf("\t\t      ");
        scanf("%lf", &node->grade);

        printf("*\t\t请录入电影场次\t\t*\n");
        printf("\t\t      ");
        scanf("%d", &node->number);

        printf("*\t\t请录入电影时长(整数）\t\t*\n");
        printf("\t\t      ");
        scanf("%d", &node->time);

        printf("*\t\t请录入电影展厅\t\t*\n");
        printf("\t\t      ");
        scanf("%d", &node->hall);

        printf("*\t\t请录入电影出版公司\t\t*\n");
        printf("\t\t      ");
        scanf("%s", node->publish);

        printf("*\t\t请录入电影票价(整数）\t\t*\n");
        printf("\t\t      ");
        scanf("%d", &node->price);

        // printf("*\t\t请录入电影时段(xx:xx)\t\t*\n");
        // for (i = 0; i < node->number; i++)
        // {
        //     scanf("%s", node->timeline[i]);
        // }

        printf("\t\t******************录入信息完成******************\n");
        printf("*********************************************************\n");
        end->next = node; // 尾插新结点
        end = node;       // 指向尾结点
        printf("\t\t1.是\t2.否\t\t\n");
        printf("要继续录入此电影信息吗");
        scanf("%d", &n);

    } while (n == 1);
    end->next = NULL;

    return (head);
}




// // 电影查询
void Search(Linklist *list)
{
    int n,i,flag=1;
    char con[100];
    Linklist *p=list;
    
    printf("1.名称\t2.评分\t3.出版公司\t4.展厅号\t5.时长\t");
    printf("请输入你要查询的选项:");
    scanf("%d",&n);

    switch(n)
    {
        case 1:
        printf("请输入名称:");
        scanf("%s",&con);
        printf("名称\t\t票价\t\t评分\t\t场次\t\t出版公司\t\t展厅号\t\t时长\n");
        while(p!=NULL){
            if(strcmp(p->name,con)==0)
            {
                printf("%s\t\t%d\t\t%.2f\t\t%d\t\t%s\t\t%d\t\t%d\n",p->name,p->price,p->grade,p->number,p->publish,p->hall,p->time);
                // int j;
                // for(j=1;j<p->number;j++){
                //     printf("\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t[%d]%s",j,p->timeline[j]);
                //     printf("\n");
                // }
                getchar();
                flag=0;
            }
            p=p->next;
        }
        if(flag==1){
            printf("不存在该电影\n");
        }
        break;

        case 2:
        printf("请输入评分:");
        scanf("%d",&i);
        while(p!=NULL){
            if(p->grade==i){
                printf("名称\t\t票价\t\t评分\t\t场次\t\t出版公司\t\t展厅号\t\t时长\n");
                printf("%s\t\t%d\t\t%.2f\t\t%d\t\t%s\t\t%d\t\t%d\t\t[1]%s\n",p->name,p->price,p->grade,p->number,p->publish,p->hall,p->time);
                // int j;
                // for(j=1;j<p->number;j++){
                //     printf("\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t[%d]%s",j,p->timeline[j]);
                //     printf("\n");
                // }
                //getchar();
                flag=0;

            }
            getchar();
            p=p->next;
        }
        if(flag==1){
            printf("不存在该评分的电影\n");
        }
        break;

        case 3:
        printf("请输入出版公司:");
        scanf("%s",con);
        while(p!=NULL){
            if(p->publish==con){
                printf("名称\t\t票价\t\t评分\t\t场次\t\t出版公司\t\t展厅号\t\t时长\n");
                printf("%*s\t%d\t\t%.2f\t\t%d\t\t%s\t\t%d\t\t%d\t\t[1]%s\n",-10,p->name,p->price,p->grade,p->number,p->publish,p->hall,p->time);
                // int j;
                // for(j=1;j<p->number;j++){
                //     printf("\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t[%d]%s",j,p->timeline[j]);
                //     printf("\n");
                // }
                getchar();
                flag=0;

            }
            //getchar();
            p=p->next;
        }
        if(flag==1){
             printf("不存在公司出版的电影\n");
        }
        break;

        case 4:
        printf("请输入展厅号:");
        scanf("%d",&i);
        while(p!=NULL){
            if(p->hall==i){
                printf("名称\t\t票价\t\t评分\t\t场次\t\t出版公司\t\t展厅号\t\t时长\n");
                printf("%*s\t%d\t\t%.2f\t\t%d\t\t%s\t\t%d\t\t%d\t\t[1]%s\n",-10,p->name,p->price,p->grade,p->number,p->publish,p->hall,p->time);
                // int j;
                // for(j=1;j<p->number;j++){
                //     printf("\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t[%d]%s",j,p->timeline[j]);
                //     printf("\n");
                // }
                getchar();
                flag=0;

            }
           // getchar();
            p=p->next;
        }
        if(flag==1){
            printf("该展厅没有电影待播放\n");
        }
        break;

        case 5:
        printf("请输入时长:");
        scanf("%d",&i);
        while(p!=NULL){
            if(p->time==i){
                printf("名称\t\t票价\t\t评分\t\t场次\t\t出版公司\t\t展厅号\t\t时长\n");
                printf("%*s\t%d\t\t%.2f\t\t%d\t\t%s\t\t%d\t\t%d\t\t[1]%s\n",-10,p->name,p->price,p->grade,p->number,p->publish,p->hall,p->time);
                getchar();
                flag=0;

            }
           // getchar();
            p=p->next;
        }
        if(flag==1){
            printf("不存在该时长的电影\n");
        }
        break;
    }
    
}

// 修改电影信息
void Modify(Linklist *list)
{
    int i,n;
    char ch[100];
    Linklist *p=list;
    printf("1.评分\t2.票价\n");
    printf("请输入你要修改的项目:");
    scanf("%d",&n);
    switch(n)
    {
        case 1:
            printf("请输入要修改评分的电影名称:");
            scanf("%s",ch);
            while(p!=NULL)
            {
                if(strcmp(p->name,ch)==0)
                {
                    printf("请输入想修改的评分为:");
                    scanf("%lf",&p->grade);
                    printf("---------------【修改完成】--------------\n");
                }
                p=p->next;
            }
            break;

        case 2:
            printf("请输入要修改的电影名称:");
			scanf("%s",ch);
			while(p!=NULL)
			{
				if(p->name==ch)
				{
					printf("输入想修改的票价:");
					scanf("%d",&p->price);
					printf("---------------【修改完成】--------------\n");
				}
				p=p->next;
			}
			break;

    }

}   

// 删除信息
void Delete(Linklist *list)
{
   int n;
   char ch[100];
   Linklist *p,*q=list;
   p=q->next;
   printf("请输入1进行删除操作:");
   scanf("%d",&n);
   switch(n)
   {
    case 1:
    printf("请输入要删除的电影名称:");
    scanf("%s",ch);
    while(p!=NULL)
    {
        if(strcmp(p->name,ch)==0)
        {
            printf("-----------------------------------------【以下是你要删除的电影信息】----------------------------------------\n");
            printf("%*s\t%d\t\t%.2f\t\t%d\t\t%s\t\t%d\t\t%d\n",-10,p->name,p->price,p->grade,p->number,p->publish,p->hall,p->time);
            //  int j;
            // for(j=1;j<p->number;j++){
            //     printf("\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t[%d]%s",j,p->timeline[j]);
            //     printf("\n");
            // }
            q->next=p->next;
            free(p);
            printf("-----------------------------------------【已经安全删除】--------------------------------------------------\n");
        }
        q=p;
        p=p->next;
    }
    break;

    default:
    printf("-------------------------【输入非法！请重新输入】-------------------------------\n");
    break;
   }
}

//浏览电影信息
void Display_all(Linklist *list)
{
    Linklist *p=list->next;
    system("clear");  //清屏
    printf("******************************************************************************\n");
    printf("*\t\t   影院影片列表     \t\t\t*\n");
    printf("******************************************************************************\n");
    printf("名称\t\t票价\t\t评分\t\t场次\t\t出版公司\t\t展厅号\t\t时长\n");
    while(p)
    {
        printf("%*s\t%d\t\t%.2f\t\t%d\t\t%s\t\t%d\t\t%d\n",-10,p->name,p->price,p->grade,p->number,p->publish,p->hall,p->time);
        //  int j;
        // for(j=1;j<p->number;j++){
        //     printf("\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t[%d]%s",j,p->timeline[j]);
        //     printf("\n");
        // }
        p=p->next;
    }
    printf("******************************************************************************\n");
}



//保存
void Save(Linklist *list)
{
    Linklist *p;
	FILE *fp;
	char name[40];
	printf("\n请输入要保存的文件名:");
	scanf("%s",name);
	if((fp=fopen(name,"wt"))==NULL)
	{
		printf("写文件出错，按任意键退出！");
		getchar();
		exit(1);
	}
	for(p=list->next;p!=NULL;p=p->next)
	{
		fprintf(fp,"%s\t%d\t\t%.2f\t\t%d\t\t%s\t\t%d\t\t%d\n",p->name,p->price,p->grade,p->number,p->publish,p->hall,p->time);
        //  int j;
        // for(j=1;j<p->number;j++){
        //     fprintf(fp,"\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t[%d]%s",j,p->timeline[j]);
        //     printf("\n");
        // }
	}
	printf("\n文件已成功保存,按任意键返回！\n");
	getchar();
	fclose(fp);
}

//文件读写
Linklist *Read()
{
    Linklist *ghead,*r,*p;
    FILE *fp;
    char name[100];
    printf("\n请输入要打开的文件:");
    //getchar();
   // system("clear");
    scanf("%s",name);//有错误
    //printf("%s",name);
    if((fp=fopen(name,"rt"))==NULL)
    {
        printf("\n文件读写出错,按任意键退出!\n");
        printf("请创建链表\n");
        system("read");
        return 0;
    }
    ghead=(Linklist *)malloc(sizeof(Linklist));
    ghead->next=NULL;
    r=ghead;
    while(!feof(fp))//->如果文件光标后有字符返回0
                   //feof检测文件是否结束
    {
        p=(Linklist *)malloc(sizeof(Linklist));
        fscanf(fp,"%s%d%lf%d%s%d%d",p->name,p->price,p->grade,p->number,p->publish,p->hall,p->time);//写入文件
        r->next=p;
        r=p;

    }
    r->next=NULL;
    fclose(fp);
    printf("\n文件信息正确读入,按任意键退出!\n");
	getchar();
	return ghead;

}

int main()
{
    int i;
    Linklist *p1=NULL;
    if(Login()==0)
    {
        return 0;
    }
        p1=Read();
        system("clear");

        
        
       while(1){
            Directory();
            scanf("%d",&i);
            switch(i)
            {
                case 1:
                printf("---【重新录入信息】---\n");
                p1=input();
                break;

                case 2:
                printf("---【电影信息排序】---\n");
                Search(p1);
                break;

                case 3:
                printf("---【修改电影信息】---\n");
                Modify(p1);
                break;

                case 4:
                printf("---【删除电影信息】---\n");
                Delete(p1);
                break;

                case 5:
                printf("---【浏览电影信息】---\n");
                Display_all(p1);
                break;

                case 6:
                printf("---【退出自动保存】---\n");
                break;

                case 0:
                printf("---【已经安全退出系统】---\n");
	            break;

                default:
                printf("---【输入异常！！！请重新输入】---\n");
                break; 
            }
            system("read");           //暂停
            system("clear");           //清屏
        }

        Save(p1);
        return 0;
    }

  


