#include<stdio.h>
#include<stdlib.h>
#include<string.h>
//#include<conio.h>
 
typedef struct a{
 
	char name[100]; //电影名
	double grade; //豆瓣评分
	int number;  //一天场次
	int time;  //电影时长
	int	hall; //展厅号
    double price;  //票价
	char timeline[100][100]; //时间段
    
	struct a* next;
}Cinema,*List;
 
List head=NULL;
 
int  Login();    // 登陆
void Directory();      //   主菜单
int Choose();    //  选择功能
void Creathead(); // 创建头结点
void Reload();     //  载入本地文件
 
void Search();      //  查找电影
void Creat();       //  新建电影数据
void Delete();     //  删除电影
void DeleteAll();   // 删除所有
void Modify();     //  修改电影数据
void Sort();      // 排序
void Changedata(List p);   // 排序中的数据交换
void DisplayAll();  //  显示所有电影
void Save();       //  保存
 
int main()
{
	if(Login()==0) return 0;
	Creathead();//创建链表并初始化
	Reload();//录入登录信息
	while (1)
	{
		Directory();
		switch (Choose())
		{
		case 1:
			Creat(); break;  //1.添加电影信息 
		case 2:
			Delete(); break;  //2.删除某个电影信息 
		case 3:
		    Search();break;   //3.查找某个电影信息 
		case 4:
			Modify(); break;  //4.修改电影信息 
		case 5:
			DeleteAll(); break;  //5.删除所有电影信息 
		case 6:
			DisplayAll(); break;  //6.显示所有电影信息 
		case 7:
			Sort(); break;  //7.排序 
		case 8:
			Save(); break;  //8.保存 
		case 0:
			 return 0;   //0.退出 
		}
	}
	free(head);
}
 
int Login()  //此模块儿是登录模块儿 
{
	while (1)
	{
		printf("----------------------------------------------------------\n");
		printf("*                                                        *\n");
		printf("*                       1：用户注册                      *\n");
		printf("*                       2：用户登录                      *\n");
		printf("*                                                        *\n");
		printf("----------------------------------------------------------\n");
		printf("请输入您的选项:");
		int choose;
		char fusername[100], fpassword[100];
		char username[100], password[100];
		scanf("%d", &choose);
 
		if (choose== 1)
        {
            FILE *fp1 = fopen("user.txt", "w");//以只写方式每次都会清空之前的信息 no！
			//换成a试试 no!加到文件尾，破坏原本密码
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
        else if (choose== 2)
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
				printf("*"); // 密码保护
                system("stty echo"); // getch平替
                if (c != '\n')
                {
                    password[i] = c;
                    i++;
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
}
 
void Directory() //进入系统之后的菜单 
{
	printf("*********************************************************\n");
    printf("*\t\t欢迎使用影院管理系统\t\t\t*\n");
    printf("*********************************************************\n");
    printf("*\t\t   功能展示如下\t\t\t        *\n");
    printf("---------------------------------------------------------\n");
    printf("*\t\t1.添加电影信息\t\t\t        *\n");
    printf("*\t\t2.删除电影信息\t\t\t        *\n");
    printf("*\t\t3.查询某个电影信息\t\t        *\n");
    printf("*\t\t4.修改电影信息\t\t\t        *\n");
    printf("*\t\t5.删除所有电影信息\t\t        *\n");
    printf("*\t\t6.显示所有电影信息\t\t        *\n");
    printf("*\t\t7.排序\t\t\t                *\n");
    printf("*\t\t8.保存\t\t\t                *\n");
    printf("*\t\t0.退出\t\t\t                *\n");
    printf("*********************************************************\n");
	// printf("\n\n");
	// printf("-----------------------------影院管理系统--------------------------------\n");

	// printf("\t1.添加电影信息    2.删除某个电影信息    3.查找某个电影信息\n");

	// printf("\t4.修改电影信息    5.删除所有电影信息    6.显示所有电影信息\n");

	// printf("\t7.排序            8.保存                0.退出\n");

	// printf("\n-------------------------------------------------------------------------\n");


 
}
 
int Choose(){  //选择1-8的菜单功能 
	int n;
	printf("请输入序号:");
	while (scanf("%d", &n) != 1 || n < 0 || n>8)
	{
		printf("请重新输入:");
		scanf("%d", &n);
	}
	return n;
}
 
void Reload()   //载入函数，登录成功时，自动把信息载入内存，同时成功显示载入的信息 
{
	int number;
	int time;
	int hall;
	int count=0;
	double grade;
	double price;
	char name[100];
	char timeline[100][100];
	List b=head;
	FILE* p = fopen("data.txt", "r");
	if(p==NULL)
	{
		printf("fail to open file.\n");
	}
 
	while(fscanf(p, "%s%lf%d%d%d%lf",name,&grade,&number,&time,&hall,&price)==6)//从p指向的文件中读数据并存在name等中
	{
		printf("成功！");
		List a = (List)malloc(sizeof(Cinema));
		b->next=a;		
 
		a->grade = grade;
		a->price = price;
		a->time = time;
		a->hall = hall;
		a->number = number;
		strcpy(a->name, name);
		 
		int i; 
		for(i=0;i<number;i++)
		{
			fscanf(p,"%s",timeline[i]);
			strcpy(a->timeline[i], timeline[i]);
		}
 
		b = b->next;
		count++;
	
	}
    if(count!=0)
	b->next = NULL;
	printf("成功载入%d条信息\n\n", count);
	fclose(p);
 
}
 
void Creathead()//初始化函数
{
	List a=(List)malloc(sizeof(Cinema));
 
	a->price = 0;
	a->time = 0;
	a->hall = 0;
	a->number = 0;
	a->grade = 0;
	strcpy(a->name, "0");
//	strcpy(a->timeline, "0");
	a->next=NULL;
	head=a;	
}
 
 
 
void Creat() //创建电影信息，菜单中的1功能 
{
	List a = (List)malloc(sizeof(Cinema));
 
	printf("请输入电影名：  ");
	scanf("%s", a->name);
	printf("请输入电影评分（可为小数）： ");
	scanf("%lf",&a->grade);
	printf("请输入电影时长：(单位min)（整数）  ");
	scanf("%d", &a->time);
	printf("请输展厅号：  ");
	scanf("%d", &a->hall);
	printf("请输入建议票价：  ");
	scanf("%lf", &a->price);
	
	printf("请输入一天共几场：  ");
	scanf("%d", &a->number);
	printf("请输入电影上映时间段：(xx:xx)（24进制）  ");
	int i;
	for(i=0;i< a->number;i++)
		scanf("%s", a->timeline[i]);
 
	a->next = NULL;
	List b = head;
	while (b->next != NULL)
		b = b->next;
	b->next = a;
	system("cls");
	printf("添加成功\n\n");
}
 
void Search()  //查询电影信息 
{
	int flag = 1;
	List a,b;
	a=b = head->next;
	char name[100];
    printf("输入要查找的电影名:");
    scanf("%s", name);
	printf("\n");
	while(strcmp(a->name,name))
	{
		b=a;
		a=b->next;
		if (a== NULL)
		{
			printf("---------------------------------查找失败-----------------------------------\n\n");
			printf("-----------------------------请按回车键回到主菜单-----------------------\n");
			flag = 0;
			break; 
		}
	} 
    if(flag)
	{
	printf("电影名\t\t评分\t\t场次\t\t时长\t\t展厅号\t\t票价\t\t上映时间段\n");
	printf("----------------------------------------------------------------");
	printf("---------------------------------------------------\n");
 
	printf("%-18s\t%.1lf\t\t%d\t\t%d\t\t%d\t\t%.2lf\t\t[1]%s\n",a->name,a->grade,a->number,a->time,a->hall,a->price,a->timeline[0]);
	int i;
	for(i=1;i<a->number;i++)
		printf("\t\t\t\t\t\t\t\t\t\t\t\t[%d]%s\n",i+1,a->timeline[i]);
	printf("\n");
    }
	printf("\n\n");
	getchar();
	getchar();
	system("cls");
}
 
void Delete()
{
	char choose;
	char name[100];
	List a=head,b=head;
	printf("输入要删除的电影名： ");
	scanf("%s",name);
	while(a!=NULL&&strcmp(a->name, name))//这步特别注意换位置不行！
	{
		b=a;
		a = b->next;
	}
	if(a==NULL){
		printf("不存在此电影！\n");
	}else if(strcmp(a->name,name)==0){
		printf("确认删除电影 %s (y/n)",a->name);
		getchar();
		scanf("%c",&choose);
		if(choose=='y')
		{
			b->next=a->next;
			free(a);
		}
		printf("------------按回车键返回主菜单保存即可删除成功------------\n");
	}

	
}
 
void DeleteAll()
{
	List a, b;
	a = b = head->next;
	while (a != NULL)
	{
		b = a->next;
		free(a);
		a = b;
	}
	head->next = NULL;
	remove("data");
	printf("--------------按回车键返回主菜单保存即可删除所有内容------------\n");
}
 
 
void Modify()
{
	int flag = 0;
	char name[100],choose;
	List a=head->next,b=head;
	getchar();
	printf("输入要修改的电影名： ");
	scanf("%s", name);
	getchar();
	while(a!=NULL)
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
		printf("电影名为 %s 是否修改(y/n)", a->name);
		scanf("%c", &choose);
		getchar();
		if (choose == 'y')
		{
			printf("修改为：");
			scanf("%s", a->name);
		}
 
 
		printf("电影评分为 %.1lf 是否修改 (y/n)", a->grade);
		scanf("%c", &choose);
		getchar();
		if (choose == 'y')
		{
			printf("修改为：");
			scanf("%lf", &a->grade);
		}
 
		printf("电影一天场数为 %d 是否修改(y/n)", a->number);
		scanf("%c", &choose);
		getchar();
		if (choose == 'y')
		{
			printf("修改为：");
			scanf("%d", &a->number);
		}
 
		printf("电影时长为 %dmin 是否修改(y/n)", a->time);
		scanf("%c", &choose);
		getchar();
		if (choose == 'y')
		{
			printf("修改为：");
			scanf("%d", &a->time);
		}
 
		printf("展厅号为 %d 是否修改(y/n)", a->hall);
		scanf("%c", &choose);
		getchar();
		if (choose == 'y')
		{
			printf("修改为：");
			scanf("%d", &a->hall);
		}
 
		printf("票价为 %.2f 是否修改(y/n)", a->price);
		scanf("%c", &choose);
		getchar();
		if (choose == 'y')
		{
			printf("修改为：");
			scanf("%lf", &a->price);
		}
 
		printf("-----------------------修改完成----------------------\n");
	}
	else
		printf("未找到\n\n");
	getchar();
	system("cls");
}
 
 
 
void DisplayAll()
{
	system("cls");
	List a, b;
	a = b = head->next;
 
	if (head->next == NULL)
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
	while (a!=NULL)
	{
		printf("%-18s\t%.1lf\t\t%d\t\t%d\t\t%d\t\t%.2lf\t\t[1]%s\n",a->name,a->grade,a->number,a->time,a->hall,a->price,a->timeline[0]);
		int i;
		for(i=1;i<a->number;i++)
			printf("\t\t\t\t\t\t\t\t\t\t\t\t[%d]%s\n",i+1,a->timeline[i]);
		printf("\n");
		b = a;
		a = b->next;
	}	
	printf("--------------------------------------------请按回车键回到主菜单---------------------------------------------\n");
	getchar();
	getchar();
	system("cls");
	system("clear");  //清屏
}
 
void Sort()
{
	int a,b;
	printf("请选择按 1.评分 2.场次 排序 :");
	scanf("%d",&a);
	printf("请选择 1.降序 2.升序 排序:");
	scanf("%d",&b);
 
	List p = head->next;
	List p1 = NULL;
	while (p != p1) 
	{
		while (p->next != p1) 
		{
			if (a == 1)
			{
				if (b == 1)
				{
					if (p->grade < p->next->grade)
					{
						Changedata(p);
					}
				}
				else if (b == 2)
				{
					if (p->grade > p->next->grade)
					{
						Changedata(p);
					}
				}
			}
			if (a == 2)
			{
				if (b == 1)
				{
					if (p->number < p->next->number)
					{
						Changedata(p);
					}
				}
				else if (b == 2)
				{
					if (p->number > p->next->number)
					{
						Changedata(p);
					}
				}
			}
			p = p->next;
		}
		p1 = p;
		p = head->next;
	}
 
	printf("排序成功\n\n");
	getchar();
	printf("----------请到显示信息栏(菜单6)查看排序结果-------------\n");
	printf("------------------按回车键回到主菜单------------------\n");
	getchar();
	system("cls");
	
}
 
void Changedata(List p)
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
 
void Save()
{
	if (head->next == NULL)
	{
		printf("未录入信息\n\n");
		return;
	}
	List a=head->next,b=head;
 
	FILE *p=fopen("data.txt","w");
	while(a!=NULL)
	{
		fprintf(p, "%s %.1lf %d %d %d %.2lf ", a->name,a->grade, a->number, a->time, a->hall, a->price);
		int i;
		for(i=0;i< a->number;i++)
			fprintf(p,"%s ",a->timeline[i]);
		fprintf(p, "\n");
		b=a;
		a=a->next;
	}
	fclose(p);
 
	printf("-------------------------保存成功-----------------------\n");
	getchar();
	system("cls");

}