// #include<stdio.h>
// struct Book{
//     double price;
//     char name[40];
// }book[10],book1;
// int main(void)
// {
//     int i,max=0,min=0,n;
//     scanf("%d\n",&n);
//     for(i=0;i<n;i++){
//         gets(book[i].name);
//         scanf("%lf\n",&book[i].price);
//     }
//     for(i=0;i<n;i++){
//         if (book[i].price > book[max].price)
// 		{
// 			max = i;
// 		}
// 		if (book[i].price < book[min].price)
// 		{
// 			min = i;
// 		}
// 	}
// 	printf("%.2lf, %s\n", book[max].price, book[max].name);
// 	printf("%.2lf, %s\n", book[min].price, book[min].name);

   
// }
#include<stdio.h>
#include<string.h>//gets的头文件
struct Book
{
	//结构体成员为价格和书名
	double price;
	char name[31];
};//book是类型为struct Book的全局变量

int main()
{
	//给定n本书
	int n;
	scanf("%d", &n);
	//创建结构体数组
	struct Book book[100];
	
	int i = 0;
	int max = 0;
	int min = 0;
	for (i = 0; i < n; i++)
	{
		//读取缓冲区的换行
		getchar();
		//scanf无法读入空格和换行，所以我们用gets()读取书名
		gets(book[i].name);
		scanf("%lf", &book[i].price);
		if (book[i].price > book[max].price)
		{
			max = i;
		}
		if (book[i].price < book[min].price)
		{
			min = i;
		}
	}
	printf("%.2lf, %s\n", book[max].price, book[max].name);
	printf("%.2lf, %s\n", book[min].price, book[min].name);
	return 0;
}
