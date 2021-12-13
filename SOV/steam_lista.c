#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAZIV 21

typedef struct igrica_st {
    char naziv_igre[MAX_NAZIV];
    unsigned int pozicija;
    char Windows;
    char MacOS;
    char Linux;
    struct igrica_st* next;
} IGRICA;

IGRICA* novi_elem(char* naziv, unsigned int poz, char w, char m, char l) {
    IGRICA* novi = (IGRICA*) malloc(sizeof(IGRICA));

    strcpy(novi->naziv_igre, naziv);
    novi->pozicija = poz;
    novi->Windows = w;
    novi->MacOS = m;
    novi->Linux = l;
    novi->next = NULL;

    return novi;
}

void dodaj_elem(IGRICA** pglava, IGRICA* novi) {
    if(*pglava == NULL) {
        *pglava = novi;
    }
    else if (novi->pozicija < (*pglava)->pozicija) {
        novi->next = *pglava;
        *pglava = novi;
    } 
    else {
        IGRICA* tek = *pglava;
        while(tek != NULL) {
            if (tek->next == NULL) {
                tek->next = novi;
                novi->next = NULL;
            }
            else if(novi->pozicija < tek->next->pozicija) {
                novi->next = tek->next;
                tek->next = novi;
                break;
            }
            
            tek = tek->next;
        }
    }
}

void ucitaj(IGRICA** pglava, char f_name[]) {

    char naziv[MAX_NAZIV];
    unsigned int poz;
    char w, m, l;

    FILE* fin = fopen(f_name, "r");
    while(fscanf(fin, "%s %u %c %c %c", naziv, &poz, &w, &m, &l) != EOF) {
        IGRICA* novi = novi_elem(naziv, poz, w, m, l);

        dodaj_elem(pglava, novi);
    }
    fclose(fin);
}

void ispisi(IGRICA* pglava) {
    IGRICA* tek = pglava;
    while(tek != NULL) {
        printf("%-2u %s\n", tek->pozicija, tek->naziv_igre);
        tek = tek->next;
    }

    printf("\nNajbolje rangirana igra je %s i podrzana je na sledecim operativnim sistemima:\n", pglava->naziv_igre);

    if(pglava->Windows == '+') { printf("Windows\n"); }
    if(pglava->MacOS == '+') { printf("MacOS\n"); }
    if(pglava->Linux == '+') { printf("Linux\n"); }
}

void unisti_listu(IGRICA** pglava) {
    IGRICA* tek;
    while(*pglava != NULL) {
        tek = *pglava;
        *pglava = (*pglava)->next;
        free(tek);
    }
}

int main(int argc, char** argv) {
    IGRICA* pglava = NULL;

    if(argc > 2) {
        printf("Loš unos sa komandne linije!\n");
        exit(EXIT_FAILURE);
    }

    ucitaj(&pglava, argv[1]);
    ispisi(pglava);
    unisti_listu(&pglava);

    return 0;
}