#include <stdio.h>
#include <stdlib.h>

int main() {
    int* a = (int*)malloc(sizeof(int)*100);
    int i = 0;
    while(i < 100) {
        scanf("%d", a+i);
        if (*(a+i) == 0) break;
        i++;
    }
    for(int j = 0; j<i; j++) {
        printf("%d ", *(a+j));
    }
    free(a);
}