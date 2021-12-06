#include <stdio.h>

int fibonacii_iterativno(int n) {
    int a = 1, b = 1, sledeci;
    printf("%d %d ", a, b);

    for(int i = 0; i < n; ++i) {
        sledeci = a + b;
        a = b;
        b = sledeci;
        printf("%d ", sledeci);
    }
}

void fibonacci_rekurzivno(int* n) {
    int* a;
    int* b;
    *a = 1;
    *b = 1;
    
    printf("%d %d ", *a, *b);

    rekurzija(a, b, n);
}

void rekurzija(int* a, int* b, int* n) {
     if((*n)-- == 0) {
        return;
    }
    int sledeci;
    sledeci = *b + *a;
    *a = *b;
    *b = sledeci;

    printf("%d ", sledeci);

    rekurzija(a, b, n);
}

int main() {
    int n = 15;

    printf("Interativno: \n");
    fibonacii_iterativno(n);

    printf("\nRekurzivno: \n");
    fibonacci_rekurzivno(&n);
}