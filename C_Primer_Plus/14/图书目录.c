#include<stdio.h>
struct Times{
    int year;
    int month;
    int day;
}ti;
struct Contents{
    char name[40];
    double price;
    char writer[40];
    struct Times ti;
}con;
int main(int argc,int argv[])
{
    struct Times ti;
    struct Contents con;
    gets(con.name);
    scanf("%lf\n",&con.price);
    gets(con.writer);
    scanf("%d-%d-%d",&con.ti.year,&con.ti.month,&con.ti.day);
    puts(con.name);
    puts(con.writer);
    printf("%f %d-%02d-%02d",con.price,con.ti.year,con.ti.month,con.ti.day);

}