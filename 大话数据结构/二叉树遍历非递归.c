#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define STACK_INIT_SIZE 100
#define STACKINCREMENT 10
typedef char Datatype;
 
typedef struct BiNode {
	Datatype data;//数据内容
	struct BiNode  *Lchild;//指向左孩子结点
	struct BiNode  *rchild;//指向右孩子结点
} BiNode;
 
typedef BiNode *Elemtype;
typedef struct element {
	BiNode *ptr;
	int flag;
} element;
 
typedef element Elemtype_1;
typedef struct {
	Elemtype *data;//用于前序和中序遍历
	Elemtype_1 *data_1;//用于后序遍历
	int top;//栈顶指针，这里用int类型表示指针的下标
	int stacksize;
} SqStack;
Elemtype Pop(SqStack *s);
 
SqStack InitStack() {//空栈构造函数
	SqStack s;
	s.data = (Elemtype *)malloc(STACK_INIT_SIZE * sizeof(Elemtype));
	s.top = -1; //表示栈空
	s.stacksize = STACK_INIT_SIZE;
	if (s.data != NULL)
	{}else
    {
        printf("Init error!\n");
    }
		
	return s;
}
 
void DestroyStack(SqStack *s) {//销毁栈函数
	free(s->data);
}
 
int StackEmpty(SqStack *s) {//判断是否为空栈,是返回1，否 返回0
	if (s->top == -1)
		return 1;
	else
		return 0;
}
 
void Push(SqStack *s, Elemtype e) {//添加元素入栈
	if (s->top >= s->stacksize) {
		s->data = (Elemtype *)malloc((STACK_INIT_SIZE + STACKINCREMENT) * sizeof(Elemtype));
		s->stacksize += STACKINCREMENT;
		if (s->data != NULL) {}
		else
			printf("Push error!\n");
	} else {
		s->top++;
		s->data[s->top] = e;
	}
}
 
Elemtype Pop(SqStack *s) {
	if (StackEmpty(s) != 1 && s->top >= 0) {
		Elemtype e = s->data[s->top];
		s->top--;
		return e;
	}
	printf("Pop error!\n");
}
 
SqStack InitStack_1() {//空栈构造函数
	SqStack s;
	s.data_1 = (Elemtype_1 *)malloc(STACK_INIT_SIZE * sizeof(Elemtype_1));
	s.top = -1; //表示栈空
	s.stacksize = STACK_INIT_SIZE;
	if (s.data != NULL)
	{}
	else
		printf("Init error!\n");
	return s;
}
 
void DestroyStack_1(SqStack *s) {//销毁栈函数
	free(s->data_1);
}
 
int StackEmpty_1(SqStack *s) {//判断是否为空栈,是返回1，否 返回0
	if (s->top == -1)
		return 1;
	else
		return 0;
}
 
void Push_1(SqStack *s, Elemtype_1 e) {//添加元素入栈
	if (s->top >= s->stacksize) {
		s->data_1 = (Elemtype_1 *)malloc((STACK_INIT_SIZE + STACKINCREMENT) * sizeof(Elemtype_1));
		s->stacksize += STACKINCREMENT;
		if (s->data_1 != NULL) {}
		else
			printf("Push error!\n");
	} else {
		s->top++;
		s->data_1[s->top] = e;
	}
}
 
Elemtype_1 Pop_1(SqStack *s) {
	if (StackEmpty(s) != 1 && s->top >= 0) {
		Elemtype_1 e = s->data_1[s->top];
		s->top--;
		return e;
	}
	printf("Pop error!\n");
}


BiNode *Creat(char *str, int *i, int len) { //树的创建
	struct BiNode *bt = NULL;
	char ch = str[(*i)++];
	if (ch == '#' || *i >= len) {
		bt = NULL;
	} else {
		bt = (struct BiNode *)malloc(sizeof(BiNode));
		if (bt != NULL) {
			bt->data = ch;
			bt->Lchild = Creat(str, i, len); //这里的递归要赋值，这样才能建立不同域中的连接关系
			bt->rchild = Creat(str, i, len);
		}
	}
	return bt;//返回的一直是根结点
}
 
void visit(Datatype e) {
	printf("%c ", e);
}
 
void PreOrder(BiNode *bt) { //树的前序遍历
	SqStack s;
	s = InitStack();
	BiNode *p = bt;
	while (p != NULL || StackEmpty(&s) != 1) { //当p为空，栈也为空时退出循环
		while (p != NULL) {
			visit(p->data);//访问根结点
			Push(&s, p); //将指针p的节点压入栈中
			p = p->Lchild; //遍历左子树
		}
		if (StackEmpty(&s) != 1) { //栈不为空
			p = Pop(&s); //根结点出栈,相当于回退
			p = p->rchild; //遍历右子树
		}
	}
	DestroyStack(&s);
}
 
void MidOrder(BiNode *bt) { //树的中序遍历
	SqStack s;
	s = InitStack();
	BiNode *p = bt;
	while (p != NULL || StackEmpty(&s) != 1) { //当p为空，栈也为空时退出循环
		while (p != NULL) {
			Push(&s, p); //将指针p的节点压入栈中
			p = p->Lchild; //遍历左子树
		}
		if (StackEmpty(&s) != 1) { //栈不为空
			p = Pop(&s); //根结点出栈,相当于回退
			visit(p->data);//访问根结点
			p = p->rchild; //遍历右子树
		}
	}
	DestroyStack(&s);
}
 
void PostOrder(BiNode *bt) { //树的后序遍历
	SqStack s;
	s = InitStack_1();
	BiNode *p = bt;
	element elem;
	while (p != NULL || StackEmpty_1(&s) != 1) { //当p为空，栈也为空时退出循环
		if (p != NULL) {//第一次入栈，访问左子树
			elem.ptr = p;
			elem.flag = 1; //标记flag为1，表示即将第一次入栈
			Push_1(&s, elem); //将指针p的结点第一次压入栈中
			p = p->Lchild;
		} else {
			elem = Pop_1(&s); //出栈
			p = elem.ptr; //p指向当前要处理的结点
			if (elem.flag == 1) {
				//flag==1时，说明只访问过左子树，还要访问右子树
				elem.flag = 2;
				Push_1(&s, elem); //结点第二次压入栈中
				p = p->rchild;
			} else {
				//flag==2时，左右子树都已经访问过了
				visit(p->data);
				p = NULL; //访问后，p赋为空，确保下次循环时继续出栈（相当于回退）
			}
		}
	}
	DestroyStack_1(&s);
}


int main() {
	printf("测试二叉树遍历（非递归）算法\n");
	printf("建立一个二叉树-->");
	BiNode *bt;
	int i = 0, len;
	char str[50];
	printf("输入一个字符串用于建立二叉树:");
	scanf("%s", str);
	len = strlen(str);
	bt = Creat(str, &i, len);
	printf("测试遍历操作:\n");
	printf("测试树的前序遍历:");
	PreOrder(bt);
	printf("\n");
	printf("测试树的中序遍历:");
	MidOrder(bt);
	printf("\n");
	printf("测试树的后序遍历:");
	PostOrder(bt);
	printf("\n");
}

