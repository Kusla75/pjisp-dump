#include <stdio.h>
#include <limits.h>
#define MAX 20


int main() {
	int A[MAX];
    int n, temp;

    printf("Broj elem niza: ");
    scanf("%d", &n);

	printf("\n");
    for(int i=0; i<n; ++i) {
        scanf("%d", &A[i]);
    }

	for(int i=0; i<n; ++i) {
		int min = i;
		for(int j=i; j<n; ++j) {
			if(A[j] <= A[min]) {
				min = j;
			}
		}
		temp = A[min];
		A[min] = A[i];
		A[i] = temp;
	}

	printf("\n");
    for(int i=0; i<n; ++i) {
	printf("%d ", A[i]);

	}
	printf("\n");

	return 0;
}

