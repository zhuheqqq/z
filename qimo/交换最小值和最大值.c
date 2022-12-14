#include<stdio.h>

int main()
{
    int n;
    scanf("%d",&n);
    int a[10],i,min,max;
    for(i=0;i<n;i++)scanf("%d",&a[i]);
    for(i=0,min=0;i<n;i++)//找出最大与最小值所在位置 
    {
        if(a[min]>a[i])
            min=i;
    }
    int b=a[0];a[0]=a[min];a[min]=b;        //数组b用于交换
    
    for(i=0,max=0;i<n;i++)
    	if(a[max]<a[i])
    		max=i;
            
    b=a[max];a[max]=a[n-1];a[n-1]=b;
    
    for(i=0;i<n;i++)
    	printf("%d ",a[i]);
}
