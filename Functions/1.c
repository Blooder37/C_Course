#include <stdio.h>

float calc(float price, float discount, int n) {
    for(int i = 0; i<n; i++) {
        price -= price*(discount*0.01); 
    }
    return price;
}

int main() {
    float discount, price;
    int n;
    scanf("%f %f %d", &price, &discount, &n);
    printf("%f", calc(price, discount, n));
}