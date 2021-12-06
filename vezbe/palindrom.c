#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#define MAX 100

void to_lower(char* s) {
    for(int i = 0; i < strlen(s); i++) {
        if(s[i] >= 65 && s[i] <= 90) {
            s[i] += 32;
        }
    }
}

bool check_letter(char c) {
    bool a = false;
    if(c >= 97 && c <= 132) {
        a = true;
    }
    return a;
}

bool palindrom(char* s) {
    int j = strlen(s)-1;
    bool palindrom = true;
    int i = 0;

    while(i < strlen(s)/2 && j >= 0) {
        while(!check_letter(s[i])) {
            i++;
        }
        while(!check_letter(s[j])) {
            j--;
        }
        if(s[i++] != s[j--]){
            palindrom = false;
            break;
        }
    }

    return palindrom;
}

int main() {

    char s[MAX];
    printf("Unesite string: ");
    fgets(s, MAX, stdin);
    s[strlen(s)-1] = '\0';

    to_lower(s);

    if(palindrom(s)) {
        printf("\nString je palindrom\n");
    }
    else {
        printf("\nString nije palindom\n");
    }
    return 0;
}
