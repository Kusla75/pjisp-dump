#include <stdio.h>
#include <stdlib.h>
#define MAX 30

int main() {
    int n;
    int A[MAX];
    int pom;

    do {
        printf("Unesite broj elemenata niza: ");
        scanf("%d", &n);
    } while(n <= 0 || n > MAX);

    for(int i = 0; i < n; ++i) {
        printf("A[%d] = ", i);
        scanf("%d", &A[i]);
    }

    int j = n;
    for(int i = 0; i < n/2; ++i) {
        pom = A[i];
        A[i] = A[j-1];
        A[j-1] =  pom;
        j--;
    }
    
    printf("\nObrnuti niz izgleda: \n");
    for(int i = 0; i < n; ++i) {
        printf("A[%d] = %d\n", i, A[i]);
    }

    return 0;
}