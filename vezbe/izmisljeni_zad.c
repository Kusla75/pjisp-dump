#include <stdio.h>
#include <string.h>

#define MAX 101

void BubbleSort(int n, int niz[]) {
	int temp;

	for(int i = 0; i < n-1; ++i) {
		for(int j = 0; j < n-i-1; ++j) {
			if(niz[j] < niz[j+1]) {
				temp = niz[j];
				niz[j] = niz[j+1];
				niz[j+1] = temp;
			}
		}
	}
}

int FindMax(int n, int niz[], int* m){

	int curr_index = 0, max_index = 0; 
	int curr_max = 1, max = 1;
	for(int i = 0; i < n-1; i++) {
		if(niz[curr_index] == niz[i+1]) {
			curr_max++;
		}
		else {
			if(curr_max > max) {
				max = curr_max;
				curr_max = 1;
				max_index = curr_index;
			}
			curr_index = i+1;
		}
	}

	*m = max;
	return max_index;
}


int main() {
	int n;
	int A[MAX];

	printf("Unesite broj elemenata niza: ");
	scanf("%d", &n);

	for(int i = 0; i < n; ++i) {
		printf("A[%d] = ", i);
		scanf("%d", &A[i]);
	}

	BubbleSort(n, A);

	printf("\nSortirani niz:\n");
	for(int i = 0; i < n; ++i) {
		printf("%d ", A[i]);
	}
	printf("\n");

	int max;
	int index = FindMax(n, A, &max);
	printf("Element sa najviše ponavljanja: %d\n", A[index]);
	printf("Pojavluje se %d puta\n", max);

	return 0;
}
