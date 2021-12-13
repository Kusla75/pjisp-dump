#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAZIV 21
#define MAX_PROIZVODJAC 13

typedef struct brownie_st
{
    char naziv[MAX_NAZIV];
    unsigned int potrebna_kolicina;
    double cena;
    char proizvodjac[MAX_PROIZVODJAC];
    
    struct brownie_st* levi;
    struct brownie_st* desni;
    
} BROWNIE;

FILE* safe_open(char* f_name, char* mode) {

    FILE* f = fopen(f_name, mode);
    if(f == NULL) {
        printf("Greška pri otvaranju datoteke %s\n", f_name);
        exit(EXIT_FAILURE);
    }

    return f;
}

BROWNIE* napravi_elem(char* n, unsigned int pk, double c, char* p) {
    BROWNIE* novi = malloc(sizeof(BROWNIE));
    if(novi == NULL) {
        printf("Neuspešno alociranje memorije!\n");
        exit(EXIT_FAILURE);
    }

    strcpy(novi->naziv, n);
    novi->potrebna_kolicina = pk;
    novi->cena = c;
    strcpy(novi->proizvodjac, p);

    novi->levi = NULL;
    novi->desni = NULL;

    return novi;
}

void dodaj_elem(BROWNIE** pkoren, BROWNIE* novi) {
    if(*pkoren == NULL) {
        *pkoren = novi;
        return;
    }

    if(strcmp((*pkoren)->naziv, novi->naziv) > 0) {
        dodaj_elem(&(*pkoren)->levi, novi);
    }
    else if(strcmp((*pkoren)->naziv, novi->naziv) <= 0) {
        dodaj_elem(&(*pkoren)->desni, novi);
    }
}

void ucitaj(FILE* fin, BROWNIE** pkoren) {

    char n[MAX_NAZIV];
    char p[MAX_PROIZVODJAC];
    unsigned int pk;
    double c;

    while(fscanf(fin, "%s %u %lf %s", n, &pk, &c, p) != EOF) {
        BROWNIE* novi = napravi_elem(n, pk, c, p);

        dodaj_elem(pkoren, novi);
    } 

}

double izracunaj_ukupno(BROWNIE* pkoren) {
    double ukupno = (pkoren->cena / 100.0) * (double) pkoren->potrebna_kolicina;
    return ukupno;
}

void ispisi(FILE* fout, BROWNIE* pkoren, double* ukupna_cena) {
    if(pkoren == NULL) {
        return;
    }

    ispisi(fout, pkoren->levi, ukupna_cena);
    *ukupna_cena += izracunaj_ukupno(pkoren);
    fprintf(fout, "%-15s %-5u %-10.3lf\n", pkoren->naziv, pkoren->potrebna_kolicina, izracunaj_ukupno(pkoren));
    ispisi(fout, pkoren->desni, ukupna_cena);
}

void pronadji(BROWNIE* pkoren, BROWNIE** najveci, unsigned int* max_gramaza, char* proizvodjac) {
    if(pkoren == NULL) {
        return;
    }

    if(strcmp(pkoren->proizvodjac, proizvodjac) == 0 && pkoren->potrebna_kolicina > *max_gramaza) {
        *najveci = pkoren;
        *max_gramaza = pkoren->potrebna_kolicina;
        return;
    }

    pronadji(pkoren->levi, najveci, max_gramaza, proizvodjac);
    pronadji(pkoren->desni, najveci, max_gramaza, proizvodjac);
}

void obrisi_stablo(BROWNIE** pkoren) {
    if(*pkoren == NULL) {
        return;
    }

    obrisi_stablo(&(*pkoren)->levi);
    obrisi_stablo(&(*pkoren)->desni);
    free(*pkoren);
    *pkoren = NULL;
}

int main(int argc, char* argv[]) {
    BROWNIE* pkoren = NULL;
    char proizvodjac[MAX_PROIZVODJAC];

    if(argc != 4) {
        printf("Loš unos argumenata sa komandne linije\n");
        exit(EXIT_FAILURE);
    }
    strcpy(proizvodjac, argv[3]);

    FILE* fin = safe_open(argv[1], "r");
    ucitaj(fin, &pkoren);
    fclose(fin);
    
    FILE* fout = safe_open(argv[2], "w");
    double ukupna_cena = 0.0;
    unsigned int max_gramaza = 0;
    BROWNIE* najveci = NULL;

    ispisi(fout, pkoren, &ukupna_cena);
    pronadji(pkoren, &najveci, &max_gramaza, proizvodjac);

    fprintf(fout, "\nUkupna cena namirnica je: %.3lf\n", ukupna_cena);
    if(najveci != NULL) {
        fprintf(fout, "Namirnica sa najvecom gramazom proizvodjaca %s je: %s\n", proizvodjac, najveci->naziv);
    }
    
    fclose(fout);
    obrisi_stablo(&pkoren);
    return 0;
}