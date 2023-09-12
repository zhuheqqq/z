#include<stdio.h>

#include<string.h>

#include<stdlib.h>

#define OK 1

#define NO 0

#define MAXSIZE 20

typedef char Excelelem;

typedef struct Node

{

	int xishu;

	int mi;

	struct Node *next;

} LNode,*LinkList;



typedef struct

{

	Excelelem name[100];

	int length;

	LinkList next;

} HeadList,*HeadLinkList;



LinkList Init(int *n); //函数声明

HeadLinkList HeadInit(char a[]);

LinkList FIND(LinkList Head,int s);

void ADD(HeadLinkList A,HeadLinkList B,HeadLinkList C);

void SUB(HeadLinkList A,HeadLinkList B,HeadLinkList C);

void Free(HeadLinkList Head);

void cout(HeadLinkList Head);

void MUL(HeadLinkList A,HeadLinkList B,HeadLinkList C);



int main()

{

	HeadLinkList A,B,C;

	int n;

	A=HeadInit("A多项式");

	printf("请输入%s:\n",A->name);

	A->next=Init(&A->length);

	B=HeadInit("B多项式");

	printf("请输入%s:\n",B->name);

	B->next=Init(&B->length);

	C=HeadInit("C多项式");

	C->next=NULL;

	printf("%s+%s:\n",A->name,B->name);

	ADD(A,B,C);

	cout(C);

	printf("%s-%s:\n",A->name,B->name);

	SUB(A,B,C);

	cout(C);

	printf("%s*%s:\n",A->name,B->name);

	MUL(A,B,C);

	cout(C);

	Free(A);

	Free(B);

	Free(C);

	free(A),free(B),free(C);

	return 0;

}



LinkList FIND(LinkList Head,int s)//查找链表中第一个系数大于ans的结点的前驱

{

	if(Head->next == NULL || Head->next->mi > s)

		return Head;

	return FIND(Head->next,s);

}



LinkList Init(int *n)//初始化链表体

{

	LinkList Head,p,q;

	int i=0;

	int a,b;

	Head=NULL;

	while(~scanf("%d",&a) && a!=0)

	{

		scanf("%d",&b);

		q=(LinkList)malloc(sizeof(LNode));

		q->xishu=a;

		q->mi=b;

		if(*n==0 || Head->mi>b) q->next=Head,Head=q;

		else

		{

			p=FIND(Head,b);

			q->next=p->next;

			p->next=q;

		}

		*n++;

	}

	return Head;

}



HeadLinkList HeadInit(char *a)//初始化链表头

{

	HeadLinkList Head;

	Head=(HeadLinkList)malloc(sizeof(HeadList));

	strcpy(Head->name,a);

	Head->length=0;

	return Head;

}



void ADD(HeadLinkList A,HeadLinkList B,HeadLinkList C)//多项式加法 O(n)

{

	LinkList qa=A->next,qb=B->next,p,q=NULL;

	Free(C);

	while(qa || qb)

	{

		p=(LinkList)malloc(sizeof(LNode));

		if(qb==NULL || qa && qa->mi<qb->mi)

		{

			*p=*qa;

			qa=qa->next;

		}

		else if(qa==NULL || qb && qa->mi>qb->mi)

		{

			*p=*qb;

			qb=qb->next;

		}

		else

		{

			p->xishu=qb->xishu+qa->xishu;

			p->mi=qb->mi;

			qa=qa->next;

			qb=qb->next;

		}

		if(q==NULL) p->next=q,C->next=q=p;

		else

			p->next=q->next,q->next=p,q=p;

		C->length++;

	}

}



void SUB(HeadLinkList A,HeadLinkList B,HeadLinkList C)//多项式减法 O(n)

{

	LinkList qa=A->next,qb=B->next,p,q=NULL;

	Free(C);

	while(qa!=NULL || qb!=NULL)

	{

		p=(LinkList)malloc(sizeof(LNode));

		if(qb==NULL || qa && qa->mi<qb->mi)

		{

			*p=*qa;

			qa=qa->next;

		}

		else if(qa==NULL || qb && qa->mi>qb->mi)

		{

			*p=*qb;

			p->xishu*=-1;

			qb=qb->next;

		}

		else

		{

			*p=*qa;

			p->xishu-=qb->xishu;

			qa=qa->next;

			qb=qb->next;

			if(p->xishu==0)

			{

				free(p);

				continue;

			}

		}

		if(q==NULL) p->next=q,C->next=q=p;

		else

			q->next=p->next,q->next=p,q=p;

		C->length++;

	}

}



void MUL(HeadLinkList A,HeadLinkList B,HeadLinkList C)//多项式乘法 O(n^3)

{

	LinkList qa,qb,p,q;

	int a,b;

	Free(C);

	for(qa=A->next; qa; qa=qa->next)

	{

		for(qb=B->next; qb; qb=qb->next)

		{

			a=qa->xishu*qb->xishu;

			b=qa->mi+qb->mi;

			if(C->length)

			{

				p=FIND(C->next,b);

				if(p->mi == b)

					p->xishu+=a;

				else

				{

					q=(LinkList)malloc(sizeof(LNode));

					q->xishu=a;

					q->mi=b;

					q->next=p->next;

					p->next=q;

					C->length++;

				}

			}

			else

			{

				p=(LinkList)malloc(sizeof(LNode));

				p->xishu=a;

				p->mi=b;

				p->next=C->next;

				C->next=p;

				C->length++;

			}

		}

	}

}



void Free(HeadLinkList Head)//释放链表体内存

{

	LinkList q=Head->next,p;

	while (q)

	{

		p=q;

		q=q->next;

		free(p);

	}

	Head->length=0;

	Head->next=NULL;

	return ;

}



void cout(HeadLinkList Head)//将链表数据域以多项式形势输出

{

	LinkList q=Head->next;

	while(q)

	{

		if(q->xishu>0 && q!=Head->next)

			printf("+");

		printf("%.1dx^(%.1d)",q->xishu,q->mi);

		q=q->next;

	}

	printf("\n");

	return ;

}
