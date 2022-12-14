#include<stdio.h>
int main(void) 
{	
    int n, i, a;
	scanf("%d", &n);	
	for (i=0; i<(n+1)/2; i++) 
	{    		
		for (a=0; a<n/2-i; a++)			
			printf("  ");		
		for (a=0; a<2*i+1; a++)			
			printf("* ");		
		printf("\n");	
	}	
	for (i=1; i<=(n-1)/2; i++) 
	{  		
		for (a=0; a<i; a++)			
        	printf("  ");		
	    for (a=0; a<n-2*i; a++)			
	    	printf("* ");		
	    printf("\n");	
	} 	
	return 0;
}

