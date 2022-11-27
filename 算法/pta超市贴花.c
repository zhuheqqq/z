// #include<stdio.h>
// #include<stdlib.h>
// int main(void)
// {
//     int i,j,n,t,cnt=0;
//     scanf("%d",&n);
//     int *a=(int *)malloc(sizeof(int)*n);
//     for(i=0;i<n;i++){
//         scanf("%d",&a[i]);
//     }
//     for(i=0;i<n-1;i++){
//         for(j=0;j<n;j++){
//             if(a[j]>a[j+1]){
//                 t=a[j];
//                 a[j]=a[j+1];
//                 a[j+1]=t;
//             }
//         }
//     }
   
//    for(i=0;i<n;){
//        if((a[i+2]-a[i+1]==1)&&(a[i+1]-a[i]==1)){
//         cnt++;
//         i+=3;
//        }else{
//         i++;
//        }
//    }
//    printf("%d",cnt);
// }
// #include<stdio.h>
// #include<stdlib.h>
// int main(void)
// {
//     int n,m,i,j,k;
//     scanf("%d %d",&n,&m);
//     int *a=(int*)malloc(sizeof(int)*n);
//     int *b=(int*)malloc(sizeof(int)*n);
//     if(m>n){
//         m%=n;
//     }
//     for(i=1;i<=n;i++){
//         scanf("%d",&a[i]);
//     }
//     for(i=m+1,j=1;i<=n;i++,j++){
//         b[j]=a[i];
//     }
//     for(i=1,k=j;i<=m;i++,k++){
//         b[k]=a[i];
//     }
//     printf("%d",b[1]);
//     for(i=2;i<=n;i++){
//         printf(" %d",b[i]);
//     }
// }