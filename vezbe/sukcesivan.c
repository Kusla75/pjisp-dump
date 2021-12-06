#include <stdio.h>
#include <limits.h>
#define MAX 20

int sum(int niz[], int i, int j) {
    int s = 0;
    for(int k = i; k <= j; k++){
        s += niz[k];
    }
    return s;
}

int main() {
    int n;
    int niz[MAX];
    int s = INT_MIN;
    int p, q;

    printf("Unesite broj n: ");
    scanf("%d", &n);

    for(int i = 0; i < n; i++) {
        scanf("%d", &niz[i]);
    }

    printf("\n");
    for(int i = 0; i < n; i++) {
        for(int j = i; j < n; j++) {
            if(sum(niz, i, j) >= s) {
                s = sum(niz, i, j);
                p = i;
                q = j;
            }
        }
    }

    printf("\nSuma je: %d", s);
    printf("\nIndeks prvog elementa: %d", p);
    printf("\nIndeks poslednjeg elementa: %d\n", q);

    return 0;
}