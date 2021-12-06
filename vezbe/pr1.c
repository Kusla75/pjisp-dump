#include <stdio.h>


int main() {
    int a = 5;
    int b = 3;
    printf("Zbir a + b je : %d\n", a + b);
    printf("Razlika a - b je : %d\n", a - b);
    printf("Proizvod a * b je : %d\n", a * b);
    printf("Celobrojni kolicnik a / b je : %d\n", a / b);
    printf("Lose racunanje realnog kolicnika a / b je : %f\n",
    a / b);
    printf("Realni kolicnik a / b je : %f\n",
    (float)a / (float)b);
    printf("Ostatak pri deljenju a / b je : %d\n", a % b);
    return 0;
}
