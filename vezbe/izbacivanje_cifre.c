#include <stdio.h>

int izbaci(int num) {
    int res = 0;

    res += num % 10;
    num /= 100;
    res += 10*num;

    return res;
}

int main() {

    for(int i = 100; i <= 999; i++) {
        if(i % izbaci(i) == 0) {
            printf("%d je deljiv sa %d\n", i, izbaci(i));
        }
    }
    printf("\n");

    return 0;
}