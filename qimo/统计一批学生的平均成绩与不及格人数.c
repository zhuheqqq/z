#include <stdio.h>
#include <stdlib.h>
int main(int argc, char *argv[]) {	
	int n=0;
	int count=0;
	double cj;
	double sum=0;
	double average;
	
	scanf("%lf",&cj);
	if(cj<0)
		printf("Average = 0.00\n");
	else{
	while(1){
		if(cj>=0){
			if(cj<60) count++;
			n++;
			sum=sum+cj;							
		}
		else
			break;
			
		scanf("%lf",&cj);
					
	}	
		average=sum/n;			
	printf("Average = %.2lf\nCount = %d",average,count);		
	}
	
	return 0;

}