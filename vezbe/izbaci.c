#include <stdio.h>
#include <string.h>
#define MAX 100

int main() {
    char str1[MAX], str2[MAX], new_str[MAX];
    int i = 0, j = 0, k = 0;

    printf("Unesite string: ");
    scanf("%s", str1);
    printf("Unesite podstring: ");
    scanf("%s", str2);

    while(i != strlen(str1)) {
        if(str1[i++] == str2[0]) {
            k = i-1;
            j = 0;
            while(j < strlen(str2)) {
                if(str1[k++] != str2[j++]) {
                    break;
                }
            }
            if(j != strlen(str2)) {
                strncat(new_str, str1+i, k-i);
            }
        }
        else {
            strncat(new_str, str1+i-1, 1);
        }
    }

    printf("\nNovi string je: %s\n", new_str);

    return 0;
}