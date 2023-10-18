#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

char* build(char* str) {
    int n = strlen(str), len = 0;
    char* ret = malloc(sizeof(char) * (n + 1));
    for (int i = 0; i < n; i++) {
        if (str[i] != '#') {
            ret[len++] = str[i];
        } else if (len > 0) {
            len--;
        }
    }
    ret[len] = '\0';
    return ret;
}

bool backspaceCompare(char* S, char* T) {
    return strcmp(build(S), build(T)) == 0;
}

int main() {
    char S[201], T[201];

    printf("Enter the first string (S): ");
    scanf("%s", S);

    printf("Enter the second string (T): ");
    scanf("%s", T);

    if(backspaceCompare(S, T))
    {
        printf("true");
    }else{
        printf("false");
    }
    

    free(build(S));
    free(build(T));

    return 0;
}
