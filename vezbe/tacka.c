#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>

#define MAX_SIZE 30

struct tacka_st {
    double x;
    double y;
};

void ucitaj_tacke(FILE *fin, struct tacka_st* t, int *n) {
    while(fscanf(fin, "%lf %lf", 
    &t[*n].x, 
    &t[*n].y) != EOF) { 
        (*n)++;
    }
}

struct tacka_st najbliza_pocetku(struct tacka_st* t, int n) {
    int min = INT_MAX, index = 0;
    double duzina;

    for(int i = 0; i < n; i++) {
        duzina = sqrt(t[i].x * t[i].x + t[i].y * t[i].y);
        if (duzina < min) {
            min = duzina;
            index = i;
        }
    }

    return t[index];
}

int main(int argc, char **argv) {
    struct tacka_st tacke[MAX_SIZE];
    int n = 0;

    FILE* fin = fopen(argv[1], "r");
    puts(argv[1]);
    ucitaj_tacke(fin, tacke, &n);
    fclose(fin);

    struct tacka_st najbliza = najbliza_pocetku(tacke, n);
    printf("Najbliza tacka pocetku je: (%5.3lf, %5.3lf)\n", najbliza.x, najbliza.y);

    return 0;
}




