#include<stdio.h>
#include<string.h>
#include<stdlib.h>
int main(void)
{
    int n,i;
    double sum=0;
    printf("*********************************************************************");
    printf("Enter the number corresponding to the desired pay rate or action:");
    printf("1) $8.75/hr\n");
    printf("2) $9.33/hr\n");
    printf("3) $10.00/hr\n");
    printf("4) $11.20/hr\n");
    printf("5) quit\n");
    printf("*********************************************************************\n");
    printf("Please input a number:");
    scanf("%d",&n);
    if(n<1||n>5){
        printf("Please iuput correct number:");
        printf("*********************************************************************");
    printf("Enter the number corresponding to the desired pay rate or action:");
    printf("1) $8.75/hr\n");
    printf("2) $9.33/hr\n");
    printf("3) $10.00/hr\n");
    printf("4) $11.20/hr\n");
    printf("5) quit\n");
    printf("*********************************************************************\n");
    }else{
        switch(n){
            case 1:{
                sum=n*8.75;
                break;
            }
            case 2:{
                sum=n*9.33;
                break;
            }case 3:{
                sum=n*10.00;
                break;
            }case 4:{
                sum=n*11.20;
                break;
            }
            case 5:{
                break;
            }
        }
    }
    printf("your salary is $%f",sum);
}