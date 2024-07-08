#include <stdio.h>

int big(int a, int b) {
    return a>b;
}

int small(int a, int b) {
    return a<b;
}

void swap(int* a, int* b) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

void sort(int a[], int n, int (*choice)(int, int)) {
    for(int i = 0; i<n; i++) {
        for(int j = i; j<n; j++) {
            if(choice(a[i], a[j])) {
                swap(a+i, a+j);
            }
        }
    }
}

int main() {
    int (*choice[]) (int, int) = {big, small};
    int n, opt;
    int a[10];
    scanf("%d", &n);
    for(int i = 0; i<n; i++) {
        scanf("%d", a+i);
    }

    scanf("%d", &opt);
    sort(a, n, choice[--opt]);

    for(int i = 0; i<n; i++) {
        printf("%d ", a[i]);
    }
}