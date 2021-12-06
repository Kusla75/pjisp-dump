#include <stdio.h>
#include <math.h>

int main() {
    int a, b, c;

    printf("Unesite tri celobrojne vrednosti: \n");
    scanf("%d %d %d", &a, &b, &c);
    printf("\n");

    float ar = (a+b+c)/3.0;

    float har = 1.0/a + 1.0/b + 1.0/c;
    har = 1/har;

    float geo = pow(a*b*c,1/3.0);

    float kv = a*a + b*b + c*c;
    kv = sqrt(kv/3.0);

    printf("Aritmetička sredina: %f\n", ar);
    printf("Harmonijska sredina: %f\n", har);
    printf("Geometrijska sredina: %f\n", geo);
    printf("Kvadratna sredina: %f\n", kv);

    return 0;
}
