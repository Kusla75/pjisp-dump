#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SADRZAJ_MAX 31
#define LOMLJIVO_MAX 3
#define CENA_1 200.0
#define CENA_2 400.0
#define GRANICA_1 5.0
#define GRANICA_2 10.0

typedef struct paket_st {
    char sadrzaj[SADRZAJ_MAX];
    double masa;
    char lomljivo[LOMLJIVO_MAX];
    struct paket_st* sledeci;
} PAKET;

FILE* safe_open(char* f_name, char* mode) {

    FILE* f = fopen(f_name, mode);
    if(f == NULL) {
        printf("Neuspešno otvaranje datoteke %s\n", f_name);
        exit(EXIT_FAILURE);
    }

    return f;
}

PAKET* napravi_elem(char* s, double m, char* l) {
    PAKET* novi = malloc(sizeof(PAKET));

    strcpy(novi->sadrzaj, s);
    novi->masa = m;
    strcpy(novi->lomljivo, l);
    novi->sledeci = NULL;

    return novi;
}

void dodaj_elem(PAKET** pglava, PAKET* novi) {

    if(*pglava == NULL) {
        *pglava = novi;
        return;
    }
    else if((*pglava)->masa > novi->masa) {
        novi->sledeci = *pglava;
        *pglava = novi;
        return;
    }
      
    PAKET* tek = *pglava;
    while(tek->sledeci != NULL) {
        if(tek->sledeci->masa > novi->masa) {
            novi->sledeci = tek->sledeci;
            tek->sledeci = novi;
            return;
        }
        tek = tek->sledeci;
    }

    tek->sledeci = novi;
}

void ucitaj(FILE* fin, PAKET** pglava) {
    PAKET* tek = NULL;

    char s[SADRZAJ_MAX];
    double m;
    char l[LOMLJIVO_MAX];

    while(fscanf(fin, "%s %lf %s", s, &m, l) != EOF) {
        PAKET* novi = napravi_elem(s, m, l);

        dodaj_elem(pglava, novi);
    }
}

double izracunaj(double m, double cena_po_kg) {
    if(m <= GRANICA_1) {
        return CENA_1;
    }
    else if(m >= GRANICA_1 && m <= GRANICA_2) {
        return CENA_2;
    }
    else if(m > GRANICA_2) {
        return CENA_2 + (m-GRANICA_2)*cena_po_kg;
    }
}

void ispisi(PAKET* pglava, double cena_po_kg) {

    while(pglava != NULL) {
        printf("%-10s %2s %6.2lf %6.2lf\n", 
            pglava->sadrzaj, 
            pglava->lomljivo, 
            izracunaj(pglava->masa, cena_po_kg),
            pglava->masa);

        pglava = pglava->sledeci;
    }
}

void unisti_listu(PAKET** pglava) {
    while(*pglava != NULL) {
        PAKET* tek = *pglava;
        *pglava = (*pglava)->sledeci;
        free(tek);
    }
}

int main(int argc, char* argv[]) {
    PAKET* pglava = NULL;

    if(argc != 3) {
        printf("Greška sa argumentima komandne linije!\n");
        exit(EXIT_FAILURE);
    }
    double cena_po_kg = atof(argv[2]);

    FILE* fin = safe_open(argv[1], "r");
    ucitaj(fin, &pglava);
    fclose(fin);

    ispisi(pglava, cena_po_kg);

    unisti_listu(&pglava);
    return 0;
}