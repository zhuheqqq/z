#include <stdio.h>
#include <math.h>
int main(){
    int a,b=1;
    scanf("%d",&a);
    int c=a,d,e=0,f,g=0,h=0,i=0;
    if(a==13){
        i++;
    }
    while(i!=2){
        while(a>9){
            a=a/10;
            b++;
        }
        f=b;
        while(c>9){
            d=pow(10,b-1);
            b--;
            e=c/d;
            c=c%d;
            g+=e;
        }
        g+=c;
        a=g*3+1;
        b=1;
        c=a;
        h++;
        printf("%d:%d\n",h,g*3+1);
        if(g*3+1==13){
            i++;
        }
        g=0;
    }
    return 0;
}

