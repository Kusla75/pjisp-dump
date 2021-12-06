#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAX 100

void convert(char* bin, int* dec) {
    *dec = 0;
    int temp = 0;

    for(int i = 0; i < strlen(bin); i++) {
        *dec += pow(2, strlen(bin)-i-1) * (bin[i]-48); 
    }
}

int main() {
    char* bin[MAX];
    char temp[MAX];
    int dec[MAX];
    int n;

    do {
        printf("Unesite broj binarnih brojeva: ");
        scanf("%d", &n);
    } while(n < 0 || n > MAX);

    for(int i = 0; i < n; i++) {
        printf("%d. binarni broj: ", i+1);
        scanf("%s", temp);
        bin[i] = malloc(sizeof(char)*MAX);
        strcpy(bin[i], temp);
    }

    for(int i = 0; i < n; i++) {
        convert(bin[i], dec+i);
    }

    printf("\nDekadne vrednosti su: \n");
    for(int i = 0; i < n; i++) {
        printf("%d ", dec[i]);
    }
    printf("\n");

    return 0;
}