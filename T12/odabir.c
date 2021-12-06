#include <stdio.h>
#include <stdlib.h>

#define MAX 10

int main() {
    int n, x, count = 0;
    int A[MAX];

    // Unos ---------

    do {
        printf("Unesite Unesite broj elemenata niza (max 10): ");
        scanf("%d", &n);
    } while (n <= 0 || n > 10);

    printf("Unesite trazenu vrednost: ");
    scanf("%d", &x);
    printf("\n");

    for(int i = 0; i < n; ++i) {
        printf("Unesite A[%d]: ", i);
        scanf("%d", &A[i]);
    }
    printf("\n");

    // Ispis --------

    for(int i = 0; i < n; ++i) {
        printf("A[%d]: %d\n", i, A[i]);
    }
    printf("\n");

    for(int i = 0; i < n; ++i) {
        if(A[i] == x) {
            printf("found(A[%d]) == %d\n", i, A[i]);
            count++;
        }
    }
    printf("\n");

    printf("chance = %lf\n", (double)count/(double)n);

    return 0;
}