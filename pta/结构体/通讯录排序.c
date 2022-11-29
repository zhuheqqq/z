#include <stdio.h>

struct student
{
    char name[10];
    int birth;
    char phone[17];
}stu[10], stu1;
int main()
{
    int i, j, n;

    scanf("%d", &n);
    for (i = 0; i < n; i++)
        scanf("%s %d %s", stu[i].name, &stu[i].birth, stu[i].phone);
    for (i = 0; i < n - 1; i++)
    {
        for (j = 0; j < n - i - 1; j++)
        {
            if (stu[j].birth > stu[j+1].birth)
            {
                stu1 = stu[j];
                stu[j] = stu[j+1];
                stu[j+1] = stu1;
            }
        }
    }
    for (i = 0; i < n; i++)
        printf("%s %d %s\n", stu[i].name, stu[i].birth, stu[i].phone);

    return 0;
}
