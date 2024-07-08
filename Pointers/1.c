#include <stdio.h>
#include <stdlib.h>

int main() {
    int* ap = (int*)malloc(sizeof(int*));
    int* bp = (int*)malloc(sizeof(int*));
    scanf("%d %d", ap, bp);
    printf("%d + %d = %d", *ap, *bp, *ap + *bp);
}