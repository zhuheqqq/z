#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#define max 100
struct stack
{
    char *data;
    int size;
    int top;
    /* data */
};
typedef struct stack Stack;
void initStack(Stack *s);
void destroyStack(Stack *s);
void push(Stack s, char ch);
char pop(Stack s);
bool isEmpty(Stack s);
bool isFull(Stack s);
void setNull(Stack s);

void initStack(Stack *s)
{
    s->data = (char *)malloc(max * sizeof(char));
    if (!s->data)
    {
        exit(0);
    }
    s->size = max;
    s->top = -1;
}

void destroyStack(Stack *s)
{
    free(s->data);
}

void setNull(Stack s)
{
    s.top = -1;
}

void push(Stack s, char ch)
{
    if (!isFull(s))
    {
        s.data[++s.top] = ch;
    }
}

bool isFull(Stack s)
{
    if (s.top == s.size - 1)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool isEmpty(Stack s)
{
    if (s.top == -1)
    {
        return true;
    }
    else
    {
        return false;
    }
}

char pop(Stack s)
{
    if (!isEmpty(s))
    {
        return s.data[s.top--];
    }
}

int main(void)
{
    Stack s;
    Stack *p=&s;
    initStack(p);
    s.size = 2;
    push(s, 'a');
    push(s, 'b');
    printf("%d\n", isFull(s));
    printf("%c\n",(char)pop(s));
    printf("%c\n", (char)pop(s));
    printf("%d\n", isEmpty(s));
    destroyStack(p);
    return 0;
}
