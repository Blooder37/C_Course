#include <stdio.h>
#include <stdlib.h>

int strlength(char* s) {
    int i = 0;
    while(*(s+i) != '\0') i++;
    return i;
}

int main() {
    char a[50] = "Hello";
    printf("%d", strlength(a));
}