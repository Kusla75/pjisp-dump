#include <stdio.h>
#include <stdlib.h>
#define MAX 50

int main() {
    int n, a = 0, b = 0;
    float SRVA = 0;
    int X[50], A[50], B[50];

    do {
        printf("Unesite broj elemenata niza X: ");
        scanf("%d", &n);
    } while(n <= 0 || n > MAX);

    for(int i = 0; i < n; ++i) {
        printf("X[%d] = ", i);
        scanf("%d", &X[i]);
    }
    printf("\n");

    for(int i = 0; i < n; ++i) {
        if(X[i] % 2 == 0) {
            A[a++] = X[i];
        }
        if(i % 2 == 1){
            B[b++] = X[i];
        }
    }

    printf("Elementi skupa A: \n");
    for(int i = 0; i < a; ++i) {
        printf("A[%d] = %d\n", i, A[i]);
        SRVA += A[i];
    }

    printf("\nElementi skupa B: \n");
    for(int i = 0; i < b; ++i) {
        printf("B[%d] = %d\n", i, B[i]);
    }

    SRVA /= a;
    printf("\nSrednja vrednost niza A je: %10.4f\n", SRVA);

    return 0;
}