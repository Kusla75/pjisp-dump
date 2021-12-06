#include <stdio.h>
#include <stdlib.h>
#define MAX 20

int main() {
    int A[MAX][MAX];
    int B[MAX] = {0};
    int n;

    printf("Unesite dimenziju kvadratne matrice: ");
    scanf("%d", &n);

    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            scanf("%d", &A[i][j]);
        }
    }

    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            B[i] += A[i][j];
        }
    }

    printf("\nSuma vrsta je: \n");
    for(int i = 0; i < n; i++) {
        printf("%d ", B[i]);
    }
    printf("\n");

    return 0;
}