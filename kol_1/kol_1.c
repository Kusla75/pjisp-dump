#include <stdio.h>
#include <string.h>

#define MAX 24

void convert(char str[]) {
    int i;
    for(i = 0; i < strlen(str); ++i) {
        if(str[i] >= 'a' && str[i] <= 'z') {
            str[i] -= 32;
        }
    }
}

int checkLetter(char c) {
    int a = 0;
    if(c >= 'A' && c <= 'Z') {
        a = 1;
    }

    return a;
}

int main() {
    char A[MAX];
    char B[MAX] = {'\0'};
    char temp[MAX] = {'\0'};
    int found = 0;
    int i, j, k = 0;

    do {
        printf("Unesite string (max duzina 23): ");
        gets(A);

    }while(strlen(A) > MAX);

    convert(A);

    for(i = 0; i <= strlen(A); ++i) {
        if(A[i] >= 'A' && A[i] <= 'Z') {
            for(j = i; j <= strlen(A); ++j) {
                if(!checkLetter(A[j])) {
                    B[k++] = ' ';
                    break;
                }
                B[k++] = A[j];
            }
            found = 1;
        }
        if(found) {
            break;
        }
    }

    found = 0;
    int t = 0;
    for(i = strlen(A); i >= 0; --i) {
        if(A[i] >= 'A' && A[i] <= 'Z') {
            for(j = i; j >= 0; --j) {
                if(!checkLetter(A[j])) {
                    break;
                }
                temp[t++] = A[j];
            }
            found = 1;
        }
        if(found) {
            break;
        }
    }

    for(i = strlen(temp)-1; i >= 0; --i) {
        B[k++] = temp[i];
    }

    printf("\n%s\n", B);

    return 0;
}