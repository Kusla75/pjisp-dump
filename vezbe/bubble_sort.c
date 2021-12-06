#include <stdio.h>
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

	for(int i=0; i<n-1; ++i) {
		for(int j=0; j<n-i-1; ++j) {
			if(A[j] >= A[j+1]) {
				temp = A[j];
				A[j] = A[j+1];
				A[j+1] = temp;
			}
		}
	}

	printf("\n");
	for(int i=0; i<n; ++i) {
        printf("%d ", A[i]);
    }
	printf("\n");

	return 0;
}
