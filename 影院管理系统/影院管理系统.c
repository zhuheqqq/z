#include<stdio.h>
#include<stdlib.h>
#include<string.h>
          

int Login();                            //注册登陆模块             
void Directory();                       //打印影院功能目录
int Choose();                           //选择功能函数


typedef struct movie{
    char name[100];   //电影名
    double grade;     //豆瓣评分
    int number;      //一天场次
    double time;     //时长
    int hall;       //展厅
    char publish[100];    //出版公司
    double price;      //票价
    char timeline[100][100];    //时间段
    struct movie*next;
}Cinema,*List;


//用户注册登陆
int Login()
{
    int choice;
    char fusername[100],fpassword[100];
    char username[100],password[100];

    while(1)
    {
            printf("*********************************************************\n");
            printf("*\t\t1.用户注册\t\t\t        *\n");
            printf("*\t\t2.用户登录\t\t\t        *\n");
            printf("*********************************************************\n");
    

            printf("请输入您的选项:");
            scanf("%d",&choice);

            if(choice==1)
            {
                FILE*fp1=fopen("user.txt","w");
                printf("请输入用户名:");
                scanf("%s",username);
                printf("请输入密码(建议8位):");
                scanf("%s",password);

                fprintf(fp1,"%s %s",username,password);
                fclose(fp1);

                printf("注册成功！\n");

                system("pause");            //防闪退
                return 0;
            }else if(choice==2){
                FILE *fp2=fopen("user.txt","r");
                printf("请输入用户名:");
                scanf("%s",username);
                printf("请输入您的密码:");
                getchar();         //吸收回车防止对c造成影响

                char c;
                int i=0;
                while(1){
                    system("stty -echo");    //密码不回显
                    c=getchar();
                    system("stty -echo");     //getch平替
                    if(c!='\n'){
                        password[i]=c;
                        i++;
                        printf("*");//密码保护
                    }else{
                        break;
                    }
                }
                printf("\n");
                password[i]='\0';

                fscanf(fp2,"%s %s",username,password);

                if((strcmp(fusername,username)==0)&&(strcmp(fpassword,password)==0)){    //验证用户名及密码
                    printf("登陆成功！\n");
                    system("pause");              //防止闪退
                    return 1;
                }else{
                    printf("用户名或密码错误！\n");
                    system("pause");
                    return 0;
                }

            }
    }
    printf("\n");
}



//影院功能目录
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
    while(scanf("%d",&n)!=1||n<0||n>9){
        printf("\n输入错误,请重新输入:");
        scanf("%d",&n);
    }

    return n;
}

int main()
{
    Login();
    Directory();

    return 0;
}