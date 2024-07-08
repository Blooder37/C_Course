#include <stdio.h>

int maxAr(int a[], int n) {
    int max = -99999;
    for(int i = 0; i<n; i++) {
        if(a[i]>max) max = a[i];
    }
    return max;
}

int main() {
    int n;
    int a[10];
    scanf("%d", &n);
    for(int i = 0; i<n; i++) {
        scanf("%d", a+i);
    }
    printf("%d", maxAr(a, n));  
}