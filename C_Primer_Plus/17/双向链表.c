#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TSIZE 45
struct film {
    char title[TSIZE];
    int rating;
    struct film * next;
    struct film * pre;
};
int main(void)
{
    struct film * head = NULL;
    struct film * prev,* current,* next;
    char input[TSIZE];
    puts("Enter first movie title:");
    while(gets(input) != NULL && input[0] != '\0')
    {
        current = (struct film *)malloc(sizeof(struct film));
        if(head == NULL)
        {
            head = current;
            head->pre = NULL;
        }
        else
        {
            prev->next = current;
            current->pre = prev;
        }
        current->next = NULL;
        strcpy(current->title,input);
        puts("Enter your rating <0-10>:");
        scanf("%d",&current->rating);
        while(getchar() != '\n');
        puts("Enter next movie title (empty line to stop):");
        prev = current;
    }

    if(head == NULL)
        printf("No data entered.");
    else
        printf("Here is the movie list(by sequence):\n");
    current = head;
    while(current != NULL)
    {
        printf("Movie:%s Rating:%d\n",current->title,current->rating);
        current = current->next;
    }

    puts("Here is the movie list(by inverted sequence):");
    current = prev;
    while(current != NULL)
    {
        printf("Movie:%s Rating:%d\n",current->title,current->rating);
        current = current->pre;
    }

    current = head;
    while(current != NULL)
    {
        next = current->next;
        free(current);
        current = next;
    }
    printf("Bye!\n");

    return 0;
}
//
                                      
