#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int Login();      // 注册登陆模块
void Directory(); // 打印影院功能目录
int Choose();     // 选择功能函数
void Search();    // 电影查询

typedef struct movie
{
    char name[100];          // 电影名
    double grade;            // 豆瓣评分
    int number;              // 一天场次
    double time;             // 时长
    int hall;                // 展厅
    char publish[100];       // 出版公司
    double price;            // 票价
    char timeline[100][100]; // 时间段
    struct movie *next;
}Link,*Linklist;

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
            printf("请输入密码(建议8位):");
            scanf("%s", password);

            fprintf(fp1, "%s %s", username, password);
            fclose(fp1);

            printf("注册成功！\n");

            system("pause"); // 防闪退
            return 0;
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
                system("stty -echo"); // getch平替
                if (c != '\n')
                {
                    password[i] = c;
                    i++;
                    printf("*"); // 密码保护
                }
                else
                {
                    break;
                }
            }
            printf("\n");
            password[i] = '\0';

            fscanf(fp2, "%s %s", username, password);

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
    printf("*\t\t1.录入电影信息\t\t\t        *\n");
    printf("*\t\t2.查询电影信息\t\t\t        *\n");
    printf("*\t\t3.修改电影信息\t\t\t        *\n");
    printf("*\t\t4.删除电影信息\t\t\t        *\n");
    printf("*\t\t5.电影信息排序\t\t\t        *\n");
    printf("*\t\t6.显示所有电影信息\t\t        *\n");
    printf("*\t\t7.添加电影信息\t\t\t        *\n");
    printf("*\t\t8.保存\t\t\t                *\n");
    printf("*\t\t9.退出\t\t\t                *\n");
    printf("*********************************************************\n");
    printf("请选择您需要的功能：");
}

int Choose()
{
    int n;
    printf("请输入您想选择的功能序号：");
    while (scanf("%d", &n) != 1 || n < 0 || n > 9)
    {
        printf("\n输入错误,请重新输入:");
        scanf("%d", &n);
    }

    return n;
}

int main()
{
    Login();
    Directory();

    return 0;
}

// 1.录入电影信息
Link *input()
{
    int i, n;
    Link *head = NULL, *node, *end;
    head = (Link *)malloc(sizeof(Link));
    end = head; // 尾插法
    do
    {
        system("cls");
        node = (Link *)malloc(sizeof(Link));

        printf("*********************************************************\n");
        printf("*\t\t欢迎进入电影信息录入界面\t\t*\n");
        printf("*********************************************************\n");

        printf("*\t\t请输入电影名称\t\t*\n");
        scanf("%s", node->name);

        printf("*\t\t请录入电影评分\t\t*\n");
        scanf("%lf", &node->grade);

        printf("*\t\t请录入电影场次\t\t*\n");
        scanf("%d", &node->number);

        printf("*\t\t请录入电影时长\t\t*\n");
        scanf("%lf", &node->time);

        printf("*\t\t请录入电影展厅\t\t*\n");
        scanf("%d", &node->hall);

        printf("*\t\t请录入电影出版公司\t\t*\n");
        scanf("%s", node->publish);

        printf("*\t\t请录入电影票价\t\t*\n");
        scanf("%lf", &node->price);

        printf("*\t\t请录入电影时段(xx:xx)\t\t*\n");
        for (i = 0; i < node->number; i++)
        {
            scanf("%s", node->timeline[i]);
        }

        printf("\t\t******************录入信息完成******************\t\t");
        printf("*********************************************************\n");
        end->next = node; // 尾插新结点
        end = node;       // 指向尾结点
        printf("\t\t1.是\t2.否\t\t\n");
        printf("确定要录入此电影信息吗");
        scanf("%d", &n);

    } while (n == 1);
    end->next = NULL;

    return (head);
}

// 电影查询
void Search()
{
    Linklist p, q,head;
    int flag = 1;
    char name[100];

    head=(Linklist)malloc(sizeof(Linklist));

    p = q = head->next;

    printf("请输入要查询的电影名：");
    scanf("%s", name);
    printf("\n");

    while (strcmp(p->name, name))
    {
        q = p;
        p = q->next;
        if (p == NULL)
        {
            printf("查询失败\n");
            flag = 0;
            break;
        }
    }

    if (flag)
    {
        printf("电影名\t\t评分\t\t场次\t\t时长\t\t展厅号\t\t票价\t\t上映时间段\n");
        printf("-----------------------------------------------------------------\n");
        printf("-----------------------------------------------------------------\n");
        printf("%*s\t%.2lf\t\t%d\t\t%.2lf\t\t%d\t\t%.2lf\t\t[1]%s\t\t", -10, p->name, p->grade, p->number, p->time, p->hall, p->price, p->timeline[0]);

        int i;
        for (i = 1; i < p->number; i++)
        {
            printf("\t\t\t\t\t\t\t\t\t\t\t\t[%d]%s\n", i + 1, p->timeline[i]);
            printf("\n");
        }

        printf("\n");
        getchar();
        system("cls");
    }
}

// 修改电影信息
void Modify()
{
    int flag = 0;
    char name[100], c;
    Linklist head=(Linklist)malloc(sizeof(Linklist));

    Linklist a = head->next, b = head;
    getchar(); // 吸收回车
    printf("请输入要修改的电影名：");
    scanf("%s", name);
    getchar();

    while (a != NULL)
    {
        if (strcmp(a->name, name) == 0)
        {
            flag = 1;
            break;
        }
        b = a;
        a = b->next;
    }
    if (flag)
    {
        printf("%s是否修改(y/n)", a->name);
        scanf("%c", &c);
        getchar();
        if (c == 'y')
        {
            printf("修改为:");
            scanf("%s", a->name);
        }
        printf("电影评分为 %.2f 是否修改 (y/n)", a->grade);
        scanf("%c", &c);
        getchar();
        if (c == 'y')
        {
            printf("修改为：");
            scanf("%.2f", &a->grade);
        }

        printf("电影一天场数为 %d 是否修改(y/n)", a->number);
        scanf("%c", &c);
        getchar();
        if (c == 'y')
        {
            printf("修改为：");
            scanf("%d", &a->number);
        }

        printf("电影时长为 %.2fmin 是否修改(y/n)", a->time);
        scanf("%c", &c);
        getchar();
        if (c == 'y')
        {
            printf("修改为：");
            scanf("%lf", &a->time);
        }

        printf("展厅号为 %d 是否修改(y/n)", a->hall);
        scanf("%c", &c);
        getchar();
        if (c == 'y')
        {
            printf("修改为：");
            scanf("%d", &a->hall);
        }

        printf("票价为 %.2f 是否修改(y/n)", a->price);
        scanf("%c", &c);
        getchar();
        if (c == 'y')
        {
            printf("修改为：");
            scanf("%lf", &a->price);
        }

        printf("修改完成");
    }
    else
    {
        printf("发生错误\n");
    }
    getchar();
    system("cls"); // 清屏
}

// 删除信息
void Delete()
{
    char c;
    char name[100];
    Linklist head;

    head=(Linklist)malloc(sizeof(Linklist));

    Linklist a = head, b = head;
    printf("请输入要删除的电影名：");
    scanf("%s", name);

    while (strcmp(a->name, name))
    {
        b = a;
        a = b->next;
    }
    printf("确认删除电影%s(y/n)", a->name);
    getchar();
    scanf("%c", &c);
    if (c == 'y')
    {
        b->next = a->next;
        free(a);
    }
}

// 显示所有电影信息
void Display_all()
{
    system("cls");
    Linklist a, b,head;

    head=(Linklist)malloc(sizeof(Linklist));

    a = head->next;
    b = head->next;

    if (head->next = NULL)
    {
        printf("无数据");
        getchar();
        getchar();
        system("cls");
        return;
    }

    printf("电影名\t\t评分\t\t场次\t\t时长\t\t展厅号\t\t票价\t\t上映时间段\n");
    printf("---------------------------------------------------------");
    printf("---------------------------------------------------\n");

    while (a != NULL)
    {
        printf("%*s\t%.2f\t\t%d\t\t%.2f\t\t%d\t\t%.2f\t\t[1]%s\n", -10, a->name, a->grade, a->number, a->time, a->hall, a->price, a->timeline[0]);
        int i;
        for (i = 1; i < a->number; i++)
            printf("\t\t\t\t\t\t\t\t\t\t\t\t[%d]%s\n", i + 1, a->timeline[i]);
        printf("\n");
        b = a;
        a = b->next;
    }
    getchar();
    getchar();
    system("cls");
}

// 排序
void Sort()
{
    int a,b;
    printf("请选择按 1.评分 2.场次 排序:");
    scanf("%d",&a);

    printf("请选择按 1.降序 2.升序排序：");
    scanf("%d",&b);

    Linklist head=(Linklist)malloc(sizeof(Linklist));

    Linklist p=head->next;
    Linklist q=NULL;

    while(p!=q){
        while(p->next!=q){
            if(a==1&&b==1){
                if(p->grade<p->next->grade){
                    Chagedata(p);
                }
            }else if(a==1&&b==2){
                if(p->grade>p->next->grade){
                    Changedata(p);
                }
            }else if(a==2&&b==1){
                if(p->number<p->next->number){
                    Changedata(p);
                }
            }else if(a==2&b==2){
                if(p->number>p->next->number){
                    Changedata(p);
                }
            }
            p=p->next;
        }
        q=p;
        p=head->next;
    }

    printf("排序成功\n");
    getchar();
    system("cls");
}

void Changedata(Linklist p)
{
    double ex1 = p->price;
	p->price = p->next->price;
	p->next->price = ex1;
 
	double ex2 = p->grade;
	p->grade = p->next->grade;
	p->next->grade = ex2;
 
	double ex4 = p->time;
	p->time = p->next->time;
	p->next->time = ex4;	
 
	double ex5 = p->hall;
	p->hall = p->next->hall;
	p->next->hall = ex5;
 
	char temp[100];
	strcpy(temp, p->name);
	strcpy(p->name, p->next->name);
	strcpy(p->next->name, temp);
 
	char temp2[100][100];
	int i;
	for(i=0;i<p->number;i++)
		strcpy(temp2[i], p->timeline[i]);
	for(i=0;i<p->next->number;i++)
		strcpy(p->timeline[i], p->next->timeline[i]);
	for(i=0;i<p->number;i++)
		strcpy(p->next->timeline[i], temp2[i]);
 
	int ex3 = p->number;
	p->number = p->next->number;
	p->next->number = ex3;

}

//保存
void Save()
{
    Linklist head=(Linklist)malloc(sizeof(Linklist));

	if (head->next == NULL)
	{
		printf("未录入信息\n\n");
		return;
	}
	Linklist a=head->next,b=head;
 
	FILE *p=fopen("data.txt","w");
	while(a!=NULL)
	{
		fprintf(p, "%s %.2f %d %.2f %d %.2f ", a->name,a->grade, a->number, a->time, a->hall, a->price);
		int i;
		for(i=0;i< a->number;i++)
			fprintf(p,"%s ",a->timeline[i]);
		fprintf(p, "\n");
		b=a;
		a=a->next;
	}
	fclose(p);
 
	printf("保存成功");
	getchar();
	system("cls");
}

