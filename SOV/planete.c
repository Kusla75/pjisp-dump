#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAX_NAZIV 17

typedef struct planeta_st {
    char naziv[MAX_NAZIV];
    int x;
    int y;
    int z;
    struct planeta_st* sledeci;

} PLANETA;

PLANETA* novi_elem(char* naziv, int x, int y, int z) {
    PLANETA* novi = (PLANETA*) malloc(sizeof(PLANETA));

    strcpy(novi->naziv, naziv);
    novi->x = x;
    novi->y = y;
    novi->z = z;
    novi->sledeci = NULL;

    return novi;
}

void ucitaj(PLANETA** glava, char* f_name) {

    PLANETA* trenutni = *glava;
    char naziv[MAX_NAZIV];
    int x, y, z;

    FILE* f = fopen(f_name, "r");
    while(fscanf(f, "%s %d %d %d", naziv, &x, &y, &z) != EOF) {

        PLANETA* novi = novi_elem(naziv, x, y, z);
        if(*glava == NULL) {
            *glava = novi; 
            trenutni = novi;
        }
        else {
            trenutni->sledeci = novi;
            trenutni = novi;
        }
    }
    fclose(f);
}

double udaljenost(PLANETA p1, PLANETA p2) {
    double d;
    d = sqrt(pow(p1.x-p2.x, 2.0) + pow(p1.y-p2.y, 2.0) + pow(p1.z-p2.z, 2.0));
    return d;
}

void pronadji_i_ispisi(PLANETA* glava, char* f_name) {
    PLANETA* p = glava;

    double max_razdaljina = 0.0;
    PLANETA* p1 = NULL;
    PLANETA* p2 = NULL;

    while(p != NULL) {
        PLANETA* q = p->sledeci;

        while(q != NULL) {
            double r = udaljenost(*p, *q);
            if(max_razdaljina < r) {
                max_razdaljina = r;
                p1 = p;
                p2 = q;
            }
            q = q->sledeci;
        }
        p = p->sledeci;
    }

    FILE* f = fopen(f_name, "w");
    fprintf(f, "%s %d %d %d\n", p1->naziv, p1->x, p1->y, p1->z);
    fprintf(f, "%s %d %d %d\n", p2->naziv, p2->x, p2->y, p2->z);
    fprintf(f, "%.2f\n", max_razdaljina);
    fclose(f);
}

void brisanje_liste(PLANETA** glava) {
    PLANETA* temp;
    while(*glava != NULL) {
        temp = *glava;
        *glava = (*glava)->sledeci;
        free(temp);
    }
}

int main(int argc, char* argv[]) {
    PLANETA* glava = NULL;

    ucitaj(&glava, argv[1]);
    pronadji_i_ispisi(glava, argv[2]);
    brisanje_liste(&glava);

    return 0;
}