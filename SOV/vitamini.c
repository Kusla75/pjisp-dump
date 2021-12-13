#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NAZIV_MAX 14
#define VRSTA_MAX 10

typedef struct namirnica_st {

    char naziv[NAZIV_MAX];
    unsigned int kolicina_vit;
    char vrsta[VRSTA_MAX];

    struct namirnica_st* levi;
    struct namirnica_st* desni;

} NAMIRNICA;

FILE* safe_open(char* f_name, char* mode) {

    FILE* f = fopen(f_name, mode);
    if(f == NULL) {
        printf("Greška pri otvaranju datoteke %s\n", f_name);
        exit(EXIT_FAILURE);
    }

    return f;
}

NAMIRNICA* napravi_elem(char* n, unsigned int k, char* v) {
    NAMIRNICA* novi = malloc(sizeof(NAMIRNICA));
    
    strcpy(novi->naziv, n);
    novi->kolicina_vit = k;
    strcpy(novi->vrsta, v);
    novi->levi = NULL;
    novi->desni = NULL;

    return novi;
}

void dodaj_elem(NAMIRNICA** pkoren, NAMIRNICA* novi) {
    if(*pkoren == NULL) {
        *pkoren = novi;
        return;
    }

    if((*pkoren)->kolicina_vit > novi->kolicina_vit) {
        dodaj_elem(&(*pkoren)->levi, novi);
    }
    else if((*pkoren)->kolicina_vit <= novi->kolicina_vit) {
        dodaj_elem(&(*pkoren)->desni, novi);
    }
}

void ucitaj(FILE* fin, NAMIRNICA** pkoren) {
    char n[NAZIV_MAX], v[VRSTA_MAX];
    unsigned int k;

    while(fscanf(fin, "%s %u %s", n, &k, v) != EOF) {
        NAMIRNICA* novi = napravi_elem(n, k, v);

        dodaj_elem(pkoren, novi);
    }

}

void ispisi(FILE* fout, NAMIRNICA* pkoren) {
    if(pkoren == NULL) {
        return;
    }

    // Reverse In-order

    ispisi(fout, pkoren->desni);
    fprintf(fout, "%3u %-13s %s\n", pkoren->kolicina_vit, pkoren->naziv, pkoren->vrsta);
    ispisi(fout, pkoren->levi);
}

void pronadji(FILE* fout, NAMIRNICA* pkoren) {
    if(pkoren->desni == NULL) {
        fprintf(fout, "\nNamirnica sa najviše vitamina C je: \n");
        fprintf(fout, "%3u %-13s %s\n", pkoren->kolicina_vit, pkoren->naziv, pkoren->vrsta);
        return;
    }

    pronadji(fout, pkoren->desni);
}

void obrisi_stablo(NAMIRNICA** pkoren) {
    if(*pkoren == NULL) {
        return;
    }

    obrisi_stablo(&(*pkoren)->levi);
    obrisi_stablo(&(*pkoren)->desni);
    free(*pkoren);
    *pkoren = NULL;
}

int main(int argc, char* argv[]) {
    NAMIRNICA* pkoren = NULL;

    if(argc != 3) {
        printf("Greška pri unosu sa komandne linije!\n");
        exit(EXIT_FAILURE);
    }

    FILE* fin = fopen(argv[1], "r");
    ucitaj(fin, &pkoren);
    fclose(fin);

    FILE* fout = fopen(argv[2], "w");
    ispisi(fout, pkoren);
    pronadji(fout, pkoren);

    fclose(fout);
    obrisi_stablo(&pkoren);
    return 0;
}
