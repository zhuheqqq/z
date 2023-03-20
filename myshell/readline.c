	#include<stdio.h>
    #include <stdlib.h>
	 #include<readline/history.h>
	 #include<readline/readline.h>
	 int main(void)
	 {
			char *result = NULL;
			result = readline("promopt");
			 printf("%s\n",result);
			 free(result);
			 return 0;
   }
