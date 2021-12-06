#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 101

void find(char c, char temp[], int count[]) {
    int a = 0;

    for(int i = 0; i < strlen(temp); i++) {
        if(temp[i] == c) {
            count[i] += 1;
            a = 1;
            break;
        }
    }

    if(!a) {
        int i = strlen(temp);
        temp[i] = c;
        count[i] += 1;
    }
}

int main() {
    int n, j = 0;
    char s[MAX];
    char temp[MAX];
    int count[MAX] = {0};

    printf("Unesite string: ");
    fgets(s, MAX, stdin);
    s[strlen(s)-1] = '\0';

    n = strlen(s);
    for(int i=0; i<n; i++) {
        find(s[i], temp, count);
    }

    printf("\n");
    for(int i = 0; i < strlen(temp); i++) {
        printf("'%c': %d\n", temp[i], count[i]);
    }

    return 0;
}