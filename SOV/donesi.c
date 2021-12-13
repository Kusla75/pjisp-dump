#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAZIV 11
#define MAX_VRSTA 21

typedef struct restoran_st
{
    char naziv[MAX_NAZIV];
    char vrsta[MAX_VRSTA];
    float ocena;
    struct restoran_st *levi;
    struct restoran_st *desni;
} RESTORAN;

FILE *safe_open(char *name, char *mode)
{
    FILE *fp = fopen(name, mode);
    if(fp == NULL)
    {
        printf("Fajl %s nije uspesno otvoren. \n", name);
        exit(EXIT_FAILURE);
    }

    return fp;
}

void inicijalizacija(RESTORAN **koren)
{
    *koren = NULL;
}

RESTORAN *napravi_cvor(char *naziv, char *vrsta, float ocena)
{
    RESTORAN *novi = (RESTORAN *) malloc(sizeof(RESTORAN));

    if(novi == NULL)
    {
        printf("Neuspesno zauzimanje memorije. \n");
        exit(EXIT_FAILURE);
    }

    strcpy(novi->naziv, naziv);
    strcpy(novi->vrsta, vrsta);    
    novi->ocena = ocena;
    novi->levi = NULL;
    novi->desni = NULL;

    return novi;
}

void dodaj_cvor(RESTORAN **koren, RESTORAN *novi)
{
    if(*koren == NULL) {
        *koren = novi;
    }
    else {
        if((*koren)->ocena > novi->ocena) {
            dodaj_cvor(&(*koren)->levi, novi);
        }
        else if((*koren)->ocena <= novi->ocena) {
            dodaj_cvor(&(*koren)->desni, novi);
        }
    }
}

void obrisi_stablo(RESTORAN **koren)
{
    if(*koren != NULL) {
        obrisi_stablo(&(*koren)->levi);
        obrisi_stablo(&(*koren)->desni);
        free(*koren);
        *koren = NULL;
    }
}

void upis_u_stablo(FILE *in, RESTORAN **koren)
{
    char naziv[MAX_NAZIV];
    char vrsta[MAX_VRSTA];
    float ocena;

    while(fscanf(in, "%s %s %f", naziv, vrsta, &ocena) != EOF)
    {
        RESTORAN *novi = napravi_cvor(naziv, vrsta, ocena);
        dodaj_cvor(koren, novi);
    }
}

void ispis_iz_stabla(FILE *out, RESTORAN *koren)
{
    if(koren != NULL)
    {
        ispis_iz_stabla(out, koren->desni);
        fprintf(out, "%3.1f %-10s %s\n", koren->ocena, koren->naziv, koren->vrsta);
        ispis_iz_stabla(out, koren->levi);
    }
}

void pronadji_najgori(FILE* out, RESTORAN *koren) {

    if(koren->levi == NULL) {
        fprintf(out, "\nNajgore ocenjen restoran u gradu je:\n");
        fprintf(out, "%f %s %s\n", koren->ocena, koren->naziv, koren->vrsta);
    }
    else {
        pronadji_najgori(out, koren->levi);
    }
    
}
 
int main(int argbr, char *args[])
{
    if(argbr != 3)
    {
        printf("Niste dobro uneli argumente (Izlazna i ulazna datoteka). \n");
        exit(EXIT_FAILURE);
    }
    FILE *in = safe_open(args[1], "r"), *out = safe_open(args[2], "w");
    RESTORAN *koren;

    inicijalizacija(&koren);

    upis_u_stablo(in, &koren);
    fclose(in);

    ispis_iz_stabla(out, koren);
    pronadji_najgori(out, koren);
    fclose(out);


    obrisi_stablo(&koren);
    return EXIT_SUCCESS;
}