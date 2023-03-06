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


//统计信息
void Count()
{
	int cnt=0,choose,price,cnt1=0;
	double grade;
	List a=head->next;
	List b=head->next;
	printf("-----------------------------------------------------------------");
	printf("\t请选择按1.评分统计\t2.按评分和票价统计\n");
	scanf("\t请输入您的选项:%d",&choose);
	if(choose==1){
		printf("您想统计评分为多少以上的电影:");
		scanf("%lf",&grade);
		printf("电影名\t\t评分\t\t场次\t\t时长\t\t展厅号\t\t票价\t\t上映时间段\n");
		printf("----------------------------------------------------------------");
		printf("---------------------------------------------------\n");
		while(a!=NULL){
			if(a->grade>=grade){
				cnt++;
				printf("%-18s\t%.1lf\t\t%d\t\t%d\t\t%d\t\t%.2lf\t\t[1]%s\n",a->name,a->grade,a->number,a->time,a->hall,a->price,a->timeline[0]);
				b=a;
				a=a->next;
			}
			printf("------------------------共有%d部电影评分在%f及以上-------------------------",cnt,grade);
		}

	}else if(choose==2){
		printf("您想统计评分为多少以上以及票价在多少以下的电影（输入格式为评分 票价）:");
		scanf("%lf %d",&grade,&price);
		printf("电影名\t\t评分\t\t场次\t\t时长\t\t展厅号\t\t票价\t\t上映时间段\n");
		printf("----------------------------------------------------------------");
		printf("---------------------------------------------------\n");
		while(a!=NULL){
			if(a->grade>=grade&&a->price<=price){
				cnt++;
				printf("%-18s\t%.1lf\t\t%d\t\t%d\t\t%d\t\t%.2lf\t\t[1]%s\n",a->name,a->grade,a->number,a->time,a->hall,a->price,a->timeline[0]);
				b=a;
				a=a->next;
			}
			printf("---------------------共有%d部电影评分在%f及以上且票价在%d以下------------------------",cnt,grade,price);
		}
	}

}

int main()
{
	Count();
	return 0;
}