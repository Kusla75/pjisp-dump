#include <stdio.h>
#include <stdlib.h>
#define MAX 10

int main() {

    int n;
    int A[10];

    double AS = 0.0;
    int count = 0;

    printf("Unesite broj elemenata niza (max 10): ");
    scanf("%d", &n);
    while(n <= 0 || n > MAX) {
        printf("Unesite ponovo broj elemenata niza: ");
        scanf("%d", &n);
    }

    for(int i = 0; i < n; ++i) {
        printf("Unesite A[%d]: ", i);
        scanf("%d", &A[i]);
    }
    printf("\n");
    for(int i = 0; i < n; ++i) {
        printf("A[%d] = %d\n", i, A[i]);
    }

    for(int i = 0; i < n; ++i) {
        if(i % 2 == 0) {
            AS += (double) A[i];
            count++;
        }
    }
    AS /= count;

    printf("\nAS = %.2f\n", AS);

    return 0;
}