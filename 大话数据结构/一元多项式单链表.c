// #include<stdio.h>

// #include<string.h>

// #include<stdlib.h>

// #define OK 1

// #define NO 0

// #define MAXSIZE 20

// typedef char Excelelem;

// typedef struct Node

// {

// 	int xishu;

// 	int mi;

// 	struct Node *next;

// } LNode,*LinkList;



// typedef struct

// {

// 	Excelelem name[100];

// 	int length;

// 	LinkList next;

// } HeadList,*HeadLinkList;



// LinkList Init(int *n); //函数声明

// HeadLinkList HeadInit(char a[]);

// LinkList FIND(LinkList Head,int s);

// void ADD(HeadLinkList A,HeadLinkList B,HeadLinkList C);

// void SUB(HeadLinkList A,HeadLinkList B,HeadLinkList C);

// void Free(HeadLinkList Head);

// void cout(HeadLinkList Head);

// void MUL(HeadLinkList A,HeadLinkList B,HeadLinkList C);



// int main()

// {

// 	HeadLinkList A,B,C;

// 	int n;

// 	A=HeadInit("A多项式");

// 	printf("请输入%s:\n",A->name);

// 	A->next=Init(&A->length);

// 	B=HeadInit("B多项式");

// 	printf("请输入%s:\n",B->name);

// 	B->next=Init(&B->length);

// 	C=HeadInit("C多项式");

// 	C->next=NULL;

// 	printf("%s+%s:\n",A->name,B->name);

// 	ADD(A,B,C);

// 	cout(C);

// 	printf("%s-%s:\n",A->name,B->name);

// 	SUB(A,B,C);

// 	cout(C);

// 	printf("%s*%s:\n",A->name,B->name);

// 	MUL(A,B,C);

// 	cout(C);

// 	Free(A);

// 	Free(B);

// 	Free(C);

// 	free(A),free(B),free(C);

// 	return 0;

// }



// LinkList FIND(LinkList Head,int s)//查找链表中第一个系数大于ans的结点的前驱

// {

// 	if(Head->next == NULL || Head->next->mi > s)

// 		return Head;

// 	return FIND(Head->next,s);

// }



// LinkList Init(int *n)//初始化链表体

// {

// 	LinkList Head,p,q;

// 	int i=0;

// 	int a,b;

// 	Head=NULL;

// 	while(~scanf("%d",&a) && a!=0)

// 	{

// 		scanf("%d",&b);

// 		q=(LinkList)malloc(sizeof(LNode));

// 		q->xishu=a;

// 		q->mi=b;

// 		if(*n==0 || Head->mi>b) q->next=Head,Head=q;

// 		else

// 		{

// 			p=FIND(Head,b);

// 			q->next=p->next;

// 			p->next=q;

// 		}

// 		*n++;

// 	}

// 	return Head;

// }



// HeadLinkList HeadInit(char *a)//初始化链表头

// {

// 	HeadLinkList Head;

// 	Head=(HeadLinkList)malloc(sizeof(HeadList));

// 	strcpy(Head->name,a);

// 	Head->length=0;

// 	return Head;

// }



// void ADD(HeadLinkList A,HeadLinkList B,HeadLinkList C)//多项式加法 O(n)

// {

// 	LinkList qa=A->next,qb=B->next,p,q=NULL;

// 	Free(C);

// 	while(qa || qb)

// 	{

// 		p=(LinkList)malloc(sizeof(LNode));

// 		if(qb==NULL || qa && qa->mi<qb->mi)

// 		{

// 			*p=*qa;

// 			qa=qa->next;

// 		}

// 		else if(qa==NULL || qb && qa->mi>qb->mi)

// 		{

// 			*p=*qb;

// 			qb=qb->next;

// 		}

// 		else

// 		{

// 			p->xishu=qb->xishu+qa->xishu;

// 			p->mi=qb->mi;

// 			qa=qa->next;

// 			qb=qb->next;

// 		}

// 		if(q==NULL) p->next=q,C->next=q=p;

// 		else

// 			p->next=q->next,q->next=p,q=p;

// 		C->length++;

// 	}

// }



// void SUB(HeadLinkList A,HeadLinkList B,HeadLinkList C)//多项式减法 O(n)

// {

// 	LinkList qa=A->next,qb=B->next,p,q=NULL;

// 	Free(C);

// 	while(qa!=NULL || qb!=NULL)

// 	{

// 		p=(LinkList)malloc(sizeof(LNode));

// 		if(qb==NULL || qa && qa->mi<qb->mi)

// 		{

// 			*p=*qa;

// 			qa=qa->next;

// 		}

// 		else if(qa==NULL || qb && qa->mi>qb->mi)

// 		{

// 			*p=*qb;

// 			p->xishu*=-1;

// 			qb=qb->next;

// 		}

// 		else

// 		{

// 			*p=*qa;

// 			p->xishu-=qb->xishu;

// 			qa=qa->next;

// 			qb=qb->next;

// 			if(p->xishu==0)

// 			{

// 				free(p);

// 				continue;

// 			}

// 		}

// 		if(q==NULL) p->next=q,C->next=q=p;

// 		else

// 			q->next=p->next,q->next=p,q=p;

// 		C->length++;

// 	}

// }



// void MUL(HeadLinkList A,HeadLinkList B,HeadLinkList C)//多项式乘法 O(n^3)

// {

// 	LinkList qa,qb,p,q;

// 	int a,b;

// 	Free(C);

// 	for(qa=A->next; qa; qa=qa->next)

// 	{

// 		for(qb=B->next; qb; qb=qb->next)

// 		{

// 			a=qa->xishu*qb->xishu;

// 			b=qa->mi+qb->mi;

// 			if(C->length)

// 			{

// 				p=FIND(C->next,b);

// 				if(p->mi == b)

// 					p->xishu+=a;

// 				else

// 				{

// 					q=(LinkList)malloc(sizeof(LNode));

// 					q->xishu=a;

// 					q->mi=b;

// 					q->next=p->next;

// 					p->next=q;

// 					C->length++;

// 				}

// 			}

// 			else

// 			{

// 				p=(LinkList)malloc(sizeof(LNode));

// 				p->xishu=a;

// 				p->mi=b;

// 				p->next=C->next;

// 				C->next=p;

// 				C->length++;

// 			}

// 		}

// 	}

// }



// void Free(HeadLinkList Head)//释放链表体内存

// {

// 	LinkList q=Head->next,p;

// 	while (q)

// 	{

// 		p=q;

// 		q=q->next;

// 		free(p);

// 	}

// 	Head->length=0;

// 	Head->next=NULL;

// 	return ;

// }



// void cout(HeadLinkList Head)//将链表数据域以多项式形势输出

// {

// 	LinkList q=Head->next;

// 	while(q)

// 	{

// 		if(q->xishu>0 && q!=Head->next)

// 			printf("+");

// 		printf("%.1dx^(%.1d)",q->xishu,q->mi);

// 		q=q->next;

// 	}

// 	printf("\n");

// 	return ;

// }

#include <stdio.h>
#include <stdlib.h>

// 定义多项式项的结构体
typedef struct Term {
    int coefficient; // 系数
    int exponent;    // 指数
    struct Term* next;
} Term;

// 创建一个新的多项式项
Term* createTerm(int coefficient, int exponent) {
    Term* term = (Term*)malloc(sizeof(Term));
    term->coefficient = coefficient;
    term->exponent = exponent;
    term->next = NULL;
    return term;
}

// 向多项式中添加一项
void insertTerm(Term** poly, int coefficient, int exponent) {
    Term* newTerm = createTerm(coefficient, exponent);
    if (*poly == NULL) {
        *poly = newTerm;
    } else {
        Term* current = *poly;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newTerm;
    }
}

// 打印多项式
void printPolynomial(Term* poly) {
    if (poly == NULL) {
        printf("0\n");
        return;
    }

    Term* current = poly;
    while (current != NULL) {
        printf("%dX^%d", current->coefficient, current->exponent);
        current = current->next;
        if (current != NULL) {
            printf(" + ");
        }
    }
    printf("\n");
}

// 相加两个多项式
Term* addPolynomials(Term* poly1, Term* poly2) {
    Term* result = NULL;
    Term* current1 = poly1;
    Term* current2 = poly2;

    while (current1 != NULL || current2 != NULL) {
        int coeff1 = (current1 != NULL) ? current1->coefficient : 0;
        int coeff2 = (current2 != NULL) ? current2->coefficient : 0;
        int exp1 = (current1 != NULL) ? current1->exponent : 0;
        int exp2 = (current2 != NULL) ? current2->exponent : 0;

        if (exp1 == exp2) {
            insertTerm(&result, coeff1 + coeff2, exp1);
            current1 = current1->next;
            current2 = current2->next;
        } else if (exp1 > exp2) {
            insertTerm(&result, coeff1, exp1);
            current1 = current1->next;
        } else {
            insertTerm(&result, coeff2, exp2);
            current2 = current2->next;
        }
    }

    return result;
}

// 相减两个多项式
Term* subtractPolynomials(Term* poly1, Term* poly2) {
    Term* result = NULL;
    Term* current1 = poly1;
    Term* current2 = poly2;

    while (current1 != NULL || current2 != NULL) {
        int coeff1 = (current1 != NULL) ? current1->coefficient : 0;
        int coeff2 = (current2 != NULL) ? current2->coefficient : 0;
        int exp1 = (current1 != NULL) ? current1->exponent : 0;
        int exp2 = (current2 != NULL) ? current2->exponent : 0;

        if (exp1 == exp2) {
            insertTerm(&result, coeff1 - coeff2, exp1);
            current1 = current1->next;
            current2 = current2->next;
        } else if (exp1 > exp2) {
            insertTerm(&result, coeff1, exp1);
            current1 = current1->next;
        } else {
            insertTerm(&result, -coeff2, exp2);
            current2 = current2->next;
        }
    }

    return result;
}

// 求多项式的导数
Term* differentiatePolynomial(Term* poly) {
    Term* result = NULL;
    Term* current = poly;

    while (current != NULL) {
        int coeff = current->coefficient;
        int exp = current->exponent;

        if (exp > 0) {
            insertTerm(&result, coeff * exp, exp - 1);
        }

        current = current->next;
    }

    return result;
}

// 相乘两个多项式
Term* multiplyPolynomials(Term* poly1, Term* poly2) {
    Term* result = NULL;
    Term* current1 = poly1;

    while (current1 != NULL) {
        Term* current2 = poly2;
        while (current2 != NULL) {
            int coeff1 = current1->coefficient;
            int exp1 = current1->exponent;
            int coeff2 = current2->coefficient;
            int exp2 = current2->exponent;

            insertTerm(&result, coeff1 * coeff2, exp1 + exp2);

            current2 = current2->next;
        }

        current1 = current1->next;
    }

    return result;
}

// 释放多项式的内存
void freePolynomial(Term* poly) {
    while (poly != NULL) {
        Term* temp = poly;
        poly = poly->next;
        free(temp);
    }
}

int main() {
    Term* poly1 = NULL;
    Term* poly2 = NULL;

    int numTerms1, numTerms2;

    printf("输入多项式1的项数: ");
    scanf("%d", &numTerms1);
    printf("输入多项式1的每一项（系数 指数）：\n");
    for (int i = 0; i < numTerms1; i++) {
        int coefficient, exponent;
        scanf("%d%d", &coefficient, &exponent);
        insertTerm(&poly1, coefficient, exponent);
    }

    printf("输入多项式2的项数: ");
    scanf("%d", &numTerms2);
    printf("输入多项式2的每一项（系数 指数）：\n");
    for (int i = 0; i < numTerms2; i++) {
        int coefficient, exponent;
        scanf("%d%d", &coefficient, &exponent);
        insertTerm(&poly2, coefficient, exponent);
    }

    printf("多项式1: ");
    printPolynomial(poly1);

    printf("多项式2: ");
    printPolynomial(poly2);

    Term* result = addPolynomials(poly1, poly2);
    printf("多项式1 + 多项式2: ");
    printPolynomial(result);
    freePolynomial(result);

    result = subtractPolynomials(poly1, poly2);
    printf("多项式1 - 多项式2: ");
    printPolynomial(result);
    freePolynomial(result);

    result = differentiatePolynomial(poly1);
    printf("多项式1的导数: ");
    printPolynomial(result);
    freePolynomial(result);

    result = multiplyPolynomials(poly1, poly2);
    printf("多项式1 * 多项式2: ");
    printPolynomial(result);
    freePolynomial(result);

    freePolynomial(poly1);
    freePolynomial(poly2);

    return 0;
}
