#include <stdio.h>

int sumDig(int n) {
    if (n==0) return 0;
    return n%10 + sumDig(n/10);
}

int main() {
    int n;
    scanf("%d", &n);
    printf("%d", sumDig(n));
}