#include <stdio.h>
#include <stdlib.h>

int strlength(char* s) {
    int i = 0;
    while(*(s+i) != '\0') i++;
    return i;
}

char *strcat(char *first, char *second) {
    int lenf = strlength(first);
    int lens = strlength(second);
    int len = lenf + lens;
    for(int i = 0; i < lens; i++) {
        first[lenf+i] = second[i];
    }
    first[len] = '\0';
    return first;
}

int main() {
    char* a = (char*)malloc(50);
    char* b = (char*)malloc(50);
    scanf("%s", a);
    scanf("%s", b);
    strcat(a, b);
    printf("%s", a);
    free(a);
    free(b);
}