#include <stdio.h>

int main() {
    int n;

    printf("Unestie broj n: ");
    scanf("%d", &n);

    printf("\n");
    for(int i = 0; i <= 23; i++) {
        for(int j = 0; j <= 59; j++) {
            for(int k = 0; k <= 59; k++) {
                if(i + j + k == n) {
                    printf("%d sat %d min %d sek\n", i, j, k);
                }
            }
        }
    }
    printf("\n");

    return 0;
}