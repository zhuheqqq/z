#include <stdio.h>
#define MAXN 6

int main(void) {
    int n, matrix[MAXN][MAXN], i, j, k, i_max, j_min;

    scanf("%d", &n);  //输入阶数
    for (i = 0; i < n; i++) {  //输入数据
        for (j = 0; j < n; j++) {
            scanf("%d", &matrix[i][j]);
        }
    }
    for (i = 0; i < n; i++) {
        i_max = matrix[i][0];
        for (j = 0; j < n; j++) {  //找到该行最大数
            if (matrix[i][j] > i_max) {
                i_max = matrix[i][j];
            }
        }
        for (j = 0; j < n; j++) {
            j_min = matrix[0][j];
            for (k = 0; k < n; k++) {  //找到该列最小数
                if (matrix[k][j] < j_min) {
                    j_min = matrix[k][j];
                }
            }
            if (matrix[i][j] == i_max) {
                if (matrix[i][j] == j_min) {
                    printf("%d %d\n", i, j);

                    return 0;
                }
            }
        }
    }
    printf("NONE\n");

    return 0;
}