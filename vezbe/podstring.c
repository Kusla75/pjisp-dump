#include <stdio.h>
#include <string.h>

#define MAX 101

int main() {
    char veliki_str[MAX];
    char mali_str[MAX];

    printf("Unesite string: ");
    fgets(veliki_str, MAX, stdin);
    veliki_str[strlen(veliki_str)-1] = '\0';

    printf("Unesite trazeni podstring: ");
    fgets(mali_str, MAX, stdin);
    mali_str[strlen(mali_str)-1] = '\0';

    int i = 0, j = 0, count = 0;

    while(i < strlen(veliki_str)) {
        while(veliki_str[i] == mali_str[j] && i < strlen(veliki_str)) {
            i++;
            j++;
        }
        if(j == strlen(mali_str)) {
            count++;
        }
        else {
            i++;
        }
        j = 0;
    }

    printf("\nTraženi string se pojavljuje %d puta u stringu\n", count);

    return 0;
}