#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAX_INDEX 12
#define MAX_IME 21
#define MAX_PREZIME 31

typedef struct student_st {
    char br_index[MAX_INDEX];
    char ime[MAX_IME];
    char prezime[MAX_PREZIME];
    unsigned int ocena1;
    unsigned int ocena2;
    unsigned int ocena3;
    unsigned int ocena4;
    double prosek;
    struct student_st* sledeci;
} STUDENT;

FILE* safe_open(char* f_name, char* mode) {

    FILE* f = fopen(f_name, mode);
    if(f == NULL) {
        puts("Neuspešno otvaranje datoteke");
        exit(EXIT_FAILURE);
    }

    return f;
}

void read(FILE* f, STUDENT** pglava) {
    *pglava = (STUDENT* ) malloc(sizeof(STUDENT));
    STUDENT* trenutni = *pglava;

    while(fscanf(f, "%s %s %s %i %i %i %i",
        trenutni->br_index,
        trenutni->ime,
        trenutni->prezime,
        &(trenutni->ocena1),
        &(trenutni->ocena2),
        &(trenutni->ocena3),
        &(trenutni->ocena4)
        ) != EOF) {

        trenutni->sledeci = (STUDENT* ) malloc(sizeof(STUDENT));
        trenutni = (STUDENT*) trenutni->sledeci;
    }
}

double prosek(STUDENT* s) {
    double p;
    unsigned int suma = s->ocena1 + s->ocena2 + s->ocena3 + s->ocena4;
    p = suma / 4.0;
    return p;
}

void pronadji(STUDENT* trenutni, char* indeks) {
    while(trenutni != NULL) {
        if(strcmp(trenutni->br_index, indeks) != 0) {
            printf("%s %s %s %i %i %i %i %.2lf\n",
            trenutni->br_index,
            trenutni->ime,
            trenutni->prezime,
            trenutni->ocena1,
            trenutni->ocena2,
            trenutni->ocena3,
            trenutni->ocena4,
            trenutni->prosek);

            return;
        }
    }
    
    printf("Ne postoji student sa zadatim brojem indeksa.");
}

void brisanje_liste(STUDENT** pglava) {
    STUDENT* trenutni;

    while(*pglava != NULL) {
        trenutni = *pglava;
        *pglava = (*pglava)->sledeci;
        trenutni->sledeci = NULL;
        free(trenutni);
    }
}

int main(int argc, char* argv[]) {
    STUDENT* pglava = NULL;

    if(argc != 4) {
        puts("Greška pri unosu sa komandne linije");
        exit(EXIT_FAILURE);
    }

    FILE* fin = safe_open(argv[1], "r");
    read(fin, &pglava);
    fclose(fin);

    FILE* fout = safe_open(argv[2], "w");

    STUDENT* trenutni = pglava;
    while(trenutni != NULL) {
        trenutni->prosek = prosek(trenutni);
        fprintf(fout, "%s %s %s %.2lf\n", trenutni->br_index, trenutni->ime, trenutni->prezime, trenutni->prosek);
        trenutni = trenutni->sledeci;
    }
    fclose(fout);

    pronadji(pglava, argv[3]);
    brisanje_liste(&pglava);

    return 0;
}