#include <stdio.h>
#include <string.h>
#include <math.h>
#define MAX 20

void convert(char hex[], int dec[], int i) {
    dec[i] = 0;
    int n = strlen(hex)-1;

    for(int j = 0; j <= n; ++j) {
        if(hex[j] >= 65 && hex[j] <= 70)
            hex[j] -= 55;
        else
            hex[j] -= 48;

        dec[i] += pow(16,n-j) * hex[j];
    }
}

int main() {
    int n;
    char hex[MAX];
    int dec[MAX];

    printf("Unesite broj elemenata niz: ");
    scanf("%d", &n);

    for(int i = 0; i < n; i++) {
        printf("%d. element = ", i+1);
        scanf("%s", hex);
        convert(hex, dec, i);
    }

    printf("\nKonverotvani niz izgleda: ");
    for(int i = 0; i < n; i++) {
        printf("%d ", dec[i]);
    }
    printf("\n");

    return 0;
}
