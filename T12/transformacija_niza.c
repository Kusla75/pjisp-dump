#include <stdlib.h>
#include <stdio.h>
#define MAX 30

int cmpfunc (const void * a, const void * b) {
   return ( *(int*)a > *(int*)b );
}

int main() {
    int n;
    int count = 0;
    unsigned int A[MAX];
    
    printf("Unesite broj elemenata niza: ");
    scanf("%d", &n);

    for(int i = 0; i < n; ++i) {
        printf("Uneiste %d. član niza: ", i);
        scanf("%u", &A[i]);
    }

    printf("\nBroj elemenata niza je %d\n", n);
    for(int i = 0; i < n; ++i) {
        printf("A[%d] = %d\n", i, A[i]);
    }

    qsort(A, n, sizeof(int), cmpfunc);
    printf("\nElementi transformisanog niza: \n");
    int i = 0;
    while(i < n) {
        printf("A[%d] = %d\n", i, A[i]);
        count++;
        while(A[i] == A[i+1] && i+1 < n) {
            i++;
        }
        i++;
    }
    printf("\nBroj elemenata transformisanog niza je %d\n", count);
    
    return 0;
}