#include <stdio.h> 
 
int main(){
	char c;
    int num;        // num为星星总数，
	int row = 1;    // row为总行数
	scanf("%d %c", &num, &c); // 输入
	num --; // 减掉最中间一行的1颗星
	while(num >= 2*(row+2)){ // 2*(row+2)为每增加上下两行需要的星星数
		num -= 2*(row+2);   // 星星总数减去新增的上下两行的星星数
		row += 2;           // 行数+2
	}
    int star_num = row;
	// 开始画图
	for(int i = 1; i < row+1; i ++){
        // 如果是上半部分
        if(i <= row/2){
        	// 打印每一行开头的空格
            for(int n = 0; n < i-1; n++){
                printf(" ");
            }
            // 打印星星，发现规律：行数是多少，第一行和最后一行的星星就是多少个
            for(int m = 1;m < star_num+1;m ++){
				printf("%c",c);
			}
	        star_num -= 2;
	    // 如果是下半部分
        }else{
        	// 打印每一行开头的空格
            for(int n = 0; n < row-i; n++){
                printf(" ");
            }
            // 打印星星，发现规律：行数是多少，第一行和最后一行的星星就是多少个
            for(int m = 1;m < star_num+1;m ++){
				printf("%c",c);
			}
	        star_num += 2;
        }
		printf("\n");
		
	}
	printf("%d",num);
}