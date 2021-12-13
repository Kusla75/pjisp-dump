#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAZIV 21

typedef struct vatromet_st
{
    char naziv[MAX_NAZIV];
    unsigned int glasnoca;
    unsigned int cena;

    struct vatromet_st* levi;
    struct vatromet_st* desni;

} VATROMET;

FILE* safe_open(char* f_name, char* mode) {

    FILE* f = fopen(f_name, mode);
    if(f == NULL) {
        printf("Nije moguće otvoriti datoteku %s\n", f_name);
        exit(EXIT_FAILURE);
    }

    return f;
}

VATROMET* napravi_elem(char* n, unsigned int g, unsigned int c) {
    VATROMET* novi = malloc(sizeof(VATROMET));

    strcpy(novi->naziv, n);
    novi->glasnoca = g;
    novi->cena = c;

    novi->levi = NULL;
    novi->desni = NULL;

    return novi;
}

void dodaj_elem(VATROMET** pkoren, VATROMET* novi) {
    if(*pkoren == NULL) {
        *pkoren = novi;
        return;
    }

    if((*pkoren)->cena > novi->cena) {
        dodaj_elem(&(*pkoren)->levi, novi);
    }
    else if((*pkoren)->cena <= novi->cena) {
        dodaj_elem(&(*pkoren)->desni, novi);
    }
}

void ucitaj(FILE* fin, VATROMET** pkoren) {

    char n[MAX_NAZIV];
    unsigned int g, c;

    while(fscanf(fin, "%s %u %u", n, &g, &c) != EOF) {
        VATROMET* novi = napravi_elem(n, g, c);

        dodaj_elem(pkoren, novi);
    }
}

void ispisi(FILE* fout, VATROMET* pkoren, unsigned int max_glasnoca) {
    if(pkoren == NULL) {
        return;
    }

    ispisi(fout, pkoren->levi, max_glasnoca);

    if(pkoren->glasnoca <= max_glasnoca) {
        fprintf(fout, "%u %s %u\n", pkoren->cena, pkoren->naziv, pkoren->glasnoca);
    }

    ispisi(fout, pkoren->desni, max_glasnoca);
}

void pronadji(VATROMET* pkoren, VATROMET** najbolji, double* odnos, unsigned int* max_glasnoca) {
    if(pkoren == NULL) {
        return;
    }

    double temp = (double) pkoren->glasnoca / (double) pkoren->cena;
    if(temp > *odnos && pkoren->glasnoca <= *max_glasnoca) {
        *odnos = temp;
        *najbolji = pkoren;
    }

    pronadji(pkoren->levi, najbolji, odnos, max_glasnoca);
    pronadji(pkoren->desni, najbolji, odnos, max_glasnoca);
}

void obrisi_stablo(VATROMET** pkoren) {
    if(*pkoren == NULL) {
        return;
    }

    obrisi_stablo(&(*pkoren)->levi);
    obrisi_stablo(&(*pkoren)->desni);
    free(*pkoren);
    *pkoren = NULL;
}

int main(int argc, char* argv[]) {
    VATROMET* pkoren = NULL;
    
    if(argc != 4) {
        printf("Loš unos sa komandne linije!\n");
        exit(EXIT_FAILURE);
    }
    unsigned int max_glasnoca = atoi(argv[1]);

    FILE* fin = safe_open(argv[2], "r");
    ucitaj(fin, &pkoren);
    fclose(fin);

    FILE* fout = safe_open(argv[3], "w");
    ispisi(fout, pkoren, max_glasnoca);

    VATROMET* najbolji = NULL;
    double odnos = 0.0;
    pronadji(pkoren, &najbolji, &odnos, &max_glasnoca);
    fprintf(fout, "\nNajbolji vatromet sa odnosom glasnoce prema ceni od %.2lf je:\n", odnos);
    fprintf(fout, "%u %s %u\n", najbolji->cena, najbolji->naziv, najbolji->glasnoca);

    fclose(fout);

    obrisi_stablo(&pkoren);
    return 0;
}