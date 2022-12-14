#include <stdio.h>
#include <stdlib.h>
int main()
{
	double h=0;
	double juli = 0;
	int n = 0;//落地次数
	scanf("%lf %d", &h, &n);
	juli = h;//默认n=1时
	//n=0时，即没坠球时距离和反弹高度均为0
	if (n == 0){
		juli = 0;
		h = 0;	
	}
	for (int i = 2; i <= n; i++){
		h /= 2;
		juli += 2*h;
	}
	h /= 2;
	printf("%.1f %.1f\n", juli, h);
	return 0;
}
