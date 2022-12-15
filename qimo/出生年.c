

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
int main(){   
    int bir[4];
    int year, n;   scanf("%d%d",&year, &n);
    int i, count = 0;   
    for(i=year; i<3020; i++){//考虑到输入的是出生年份，作为界限的目标年份未知，取i<3020（其实经过检测上界限为3012）       
        count = 1;       
        bir[0] = i/1000;      
        bir[1] = i/100%10;       
        bir[2] = i/10%10;       
        bir[3] = i%10;//转化成数字
        if(bir[0] != bir[1] && bir[0] != bir[2] && bir[0] != bir[3]) count++;      
        if(bir[1] != bir[2] && bir[1] != bir[3]) count++;        
        if(bir[2] != bir[3]) count++;//要求各项比较为异时记录数递加
        if(count == n) break;  
}   
        printf("%d %04d", i-year, i);      
        system("pause");    
        return 0;
}//出生年

