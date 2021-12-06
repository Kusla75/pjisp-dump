#include <stdio.h>
#include <math.h>

double faktorijel(int n) {
    double fakt = 1.0;
    for(int i = 1; i <= n; ++i) {
        fakt *= i;
    }
    return fakt;
}

int main() {
    int n;
    double sum = 0.0;
    double a = 0.0;

    printf("Unesite broj clanova reda: ");
    scanf("%d", &n);
    while(n <= 0) {
        printf("Unesite broj clanova red ponovo: ");
        scanf("%d", &n);
    }

    printf("\n");
    for(int i = 0; i < n; ++i) {
        double a = pow(-1.0, (double)i) / faktorijel(i);
        printf("clan[i=%d] = %f\n", i, a);
        sum += a;
    }

    printf("\nsum = %f\n", sum);
    printf("\ne = %f\n", 1/sum);

    return 0;
}