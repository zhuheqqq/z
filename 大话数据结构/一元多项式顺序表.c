#include<stdio.h>

#include<stdlib.h>

#define maxsize 100

typedef struct node {

	int a[maxsize];

	int length;

} list;

//初始化顺序表

list* creat_list()

{

	struct node* L;

	L = (list*)malloc(sizeof(struct node));

	L->length = 0;

	return L;

}

void input(list* L)//一元多项式的输入

{

	int i;

	printf("请输入此多项式的项数：");

	scanf("%d", &L->length);

	for (i = 0; i < L->length; i++)

	{

		printf("请输入此多项式X^%d项的系数： ", i);

		scanf("%d", &L->a[i]);

	}

	printf("\n");

}

void output(struct node* L) //一元多项式的输出

{

	int i, t = 0;

	for (i = L->length - 1; i >= 0; i--)

	{

		if (L->a[i] == 0)

		{

			t++;

			continue;

		}

		else

		{

			if (i == 0)

			{

				if (L->a[i] < 0)

					printf("%d", L->a[i]);

				else

					printf("+%d", L->a[i]);

			}

			else if (0 < i && i < L->length - 1)

			{

				if (i == 1)

				{

					if (L->a[i] < 0)

						printf("%d*X", L->a[i]);

					else

						printf("+%d*X", L->a[i]);

				}

				else

				{

					if (L->a[i] < 0)

						printf("%d*X^%d", L->a[i], i);

					else

						printf("+%d*X^%d", L->a[i], i);

				}

			}

			else if (i == L->length - 1)

			{

				if (i == 1)

				{

					printf("%d*X", L->a[i]);

				}

				else

					printf("%d*X^%d", L->a[i], i);

			}

		}

	}

	if (t == L->length)

	{

		printf("0\n");

	}

	printf("\n");

}

list* sum(list* L1, list* L2) //实现两个一元多项式的相加操作

{

	int i, h;

	struct node* p;

	list* L3;

	L3 = creat_list();

	if (L1->length <= L2->length)

	{

		p = L1;

		h = L2->length - L1->length;

	}

	else

	{

		p = L2;

		h = L1->length - L2->length;

	}

	for (i = 0; i < p->length; i++)

	{

		L3->a[i] = L1->a[i] + L2->a[i];

		L3->length++;

	}

	if (h != 0)

	{

		if (p == L1)

		{

			for (i = L1->length; i <= L2->length - 1; i++)

			{

				L3->a[i] = L2->a[i];

				L3->length++;

			}

		}

		else

			for (i = L2->length; i <= L1->length - 1; i++)

			{

				L3->a[i] = L1->a[i];

				L3->length++;

			}

	}

	return L3;

}

list* poor(list* L1, list* L2)//实现两个一元多项式的相减操作

{

	int i, h;

	struct node* p;

	list* L;

	L = creat_list();

	h = L1->length - L2->length;

	if (h <= 0)

	{

		p = L1;

	}

	else

	{

		p = L2;

	}

	for (i = 0; i < p->length; i++)

	{

		L->a[i] = L1->a[i] - L2->a[i];

		L->length++;

	}

	if (h != 0)

	{



		if (p == L2)

		{

			for (i = L2->length; i <= L1->length - 1; i++)

			{

				L->a[i] = L1->a[i];

				L->length++;

			}

		}

		if (p == L1)

		{

			for (i = L1->length; i <= L2->length - 1; i++)

			{

				L->a[i] = -1 * (L2->a[i]);

				L->length++;

			}

		}

	}

	return L;

}

list* multiply(list* L1, list* L2)  //实现两个多项式的相乘

{

	int i, j, k;

	list* L;

	L = creat_list();

	for (i = 0; i <= L1->length - 1; i++)

	{

		list* p = creat_list();

		p->length = i + L2->length;

		for (k = 0; k <= p->length - 1; k++)

		{

			p->a[k] = 0;

		}

		for (j = 0; j <= L2->length - 1; j++)

		{

			p->a[i + j] = L1->a[i] * L2->a[j];

		}

		L = sum(L, p);

	}

	return L;

}

void show()

{

	printf("\t\t    指令集合\n");

	printf("\n\t1 《《《《《 一元多项式的加法运算\n");

	printf("\n\t2 《《《《《 一元多项式的减法运算\n");

	printf("\n\t3 《《《《《 一元多项式的乘法运算\n");

}

void main()

{

	int i, h;

	list* P;

	list* L[2];

	for (i = 0; i < 2; i++)

	{

		L[i] = creat_list();

		printf("\t请输入第%d个一元多项式\n", i + 1);

		input(L[i]);

		printf("第%d个一元多项式的表达式为：\n", i + 1);

		printf("\tF%d(X)=", i + 1);

		output(L[i]);

		printf("\n\n");

	}

	show();

	printf("请对两个多项式选择相关运算指令：\n");

	scanf("%d", &h);

	switch (h)

	{

		case 1:

			P = sum(L[0], L[1]);

			printf("两个一元多项式的和为：\n\tF3(X)=");

			output(P);
			break;

		case 2:

			printf("两个一元多项式的差为：\n\tF3(X)=");

			P = poor(L[0], L[1]);

			output(P);
			break;

		case 3:

			printf("两个一元多项式的乘积为：\n\tF3(X)=");

			P = multiply(L[0], L[1]);

			output(P);
			break;

		default:

			printf("指令错误！\n");

	}

}
