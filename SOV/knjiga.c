#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIFRA 10
#define MAX_ZANR 16
#define MAX_NAZIV 51
#define MAX_AUTOR 31
#define MAX_IZDAVAC 51
#define MAX_GODINA 5
#define PDV 0.18

typedef struct knjiga_st {

    char sifra_knjige[MAX_SIFRA];
    char zanr_knjige[MAX_ZANR];
    char naziv_knjige[MAX_NAZIV];
    char ime_autora[MAX_AUTOR];
    char izdavac[MAX_IZDAVAC];
    float cena_bez_pdv;
    char godina_izdanja[MAX_GODINA];

    struct knjiga_st* sledeci;

} KNJIGA;

void init(KNJIGA** pglava) {
    *pglava = NULL;
}

KNJIGA* napravi_elem(char* sifra, char* zanr, char* naziv, char* autor, char* izdavac, float cena, char* godina) {
    KNJIGA* novi = (KNJIGA*) malloc(sizeof(KNJIGA));

    if(novi == NULL) {
        printf("Neusmešno alociranje memorije!\n");
        exit(EXIT_FAILURE);
    }

    strcpy(novi->sifra_knjige, sifra);
    strcpy(novi->zanr_knjige, zanr);
    strcpy(novi->naziv_knjige, naziv);
    strcpy(novi->ime_autora, autor);
    strcpy(novi->izdavac, izdavac);
    novi->cena_bez_pdv = cena;
    strcpy(novi->godina_izdanja, godina);

    novi->sledeci = NULL;

    return novi;
}

void dodaj_elem(KNJIGA** pglava, KNJIGA* novi) {
    if(*pglava == NULL) {
        *pglava = novi;
    }
    else {
        KNJIGA* tek = *pglava;
        while(tek->sledeci != NULL) {
            tek = tek->sledeci;
        }
        tek->sledeci = novi;
    }
}

void ucitaj(FILE* fin, KNJIGA** pglava) {
    char sifra[MAX_SIFRA], zanr[MAX_ZANR], naziv[MAX_NAZIV], autor[MAX_AUTOR], izdavac[MAX_IZDAVAC];
    float cena;
    char godina[MAX_GODINA];

    while(fscanf(fin, "%s %s %s %s %s %f %s", sifra, zanr, naziv, autor, izdavac, &cena, godina) != EOF) {
        KNJIGA* novi = napravi_elem(sifra, zanr, naziv, autor, izdavac, cena, godina);

        dodaj_elem(pglava, novi);
    }
}

float izracunaj_maloprod_cenu(KNJIGA* elem) {
    return elem->cena_bez_pdv * (1 + PDV); 
}

void ispisi(FILE* fout, KNJIGA* pglava, char* zadati_zanr, float zadata_maloprod_cena) {
    float prosek = 0.0;
    int num = 0;

    while(pglava != NULL) {
        float maloprod_cena = izracunaj_maloprod_cenu(pglava);
        
        if(strcmp(pglava->zanr_knjige, zadati_zanr) == 0) {
            prosek += maloprod_cena;
            num++;

            if(maloprod_cena < zadata_maloprod_cena) {
                fprintf(fout, "%s %s %6.2f\n", pglava->naziv_knjige, pglava->ime_autora, maloprod_cena); 
            }  
        }
        pglava = pglava->sledeci;
    }

    prosek /= (double) num;
    fprintf(fout, "\nProsecna maloprodajna cena knjige %s zanra je: %6.2f\n", zadati_zanr, prosek);
}

void obrisi_listu(KNJIGA** pglava) {
    while(*pglava != NULL) {
        KNJIGA* tek = *pglava;
        *pglava = (*pglava)->sledeci;
        tek->sledeci = NULL;
        free(tek);
    }
}

FILE* safe_open(char* f_name, char* mode) {

    FILE* f = fopen(f_name, mode);
    if(f == NULL) {
        printf("Neuspešno otvaranje datoteke %s", f_name);
        exit(EXIT_FAILURE);
    }

    return f;
}

int main(int argc, char* argv[]) {
    if(argc != 4) {
        printf("Loš unos sa komandne linije!\n");
        exit(255);
    }

    KNJIGA* pglava;
    init(&pglava);
    FILE* fin = safe_open(argv[1], "r");
    ucitaj(fin, &pglava);
    fclose(fin);

    float maloprod_cena = atof(argv[3]);
    char* zadati_zanr = argv[2];

    char fout_name[MAX_ZANR + 14];
    strcpy(fout_name, "preporuka_");
    strcat(fout_name, zadati_zanr);
    strcat(fout_name, ".txt");

    FILE* fout = safe_open(fout_name, "w");
    ispisi(fout, pglava, zadati_zanr, maloprod_cena);

    fclose(fout);
    obrisi_listu(&pglava);
    return 0;
}