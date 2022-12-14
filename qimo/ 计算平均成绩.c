#include <stdio.h>

struct stdent
{
    int id[5];
    char name[10];
    int grade;
}stu[10];

int main()
{
    int i, j, temp, N, sum;
    double average;
    
    scanf("%d", &N);
    for (sum = i = 0; i < N; i++)
    {
        scanf("%s %s %d", stu[i].id, stu[i].name, &stu[i].grade);
        sum += stu[i].grade;
    }
    average = sum/N;
    printf("%.2lf\n", average);
    for (i = 0; i < N; i++)
    {
        if (stu[i].grade < average)
            printf("%s %s\n", stu[i].name, stu[i].id);
    }
    
    return 0;
}
