#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_GRUPA 31
#define MAX_TIP 7
#define MAX_PESMA 51
#define MAX_NIZ 31

struct SONG {
    char naziv_grupe[MAX_GRUPA];
    char naziv_tipa[MAX_TIP];
    char naziv_pesme[MAX_PESMA];
};

void Ucitaj(FILE* file, struct SONG pesme[], int* n) {
    while(fscanf(file, "%s %s %s",
        pesme[*n].naziv_grupe,
        pesme[*n].naziv_tipa,
        pesme[*n].naziv_pesme) != EOF) {
        
        (*n)++;
    }
}

void Ispisi(FILE* file, struct SONG pesme[], char* tip_filtera, char* naziv_filtera, int n) {

    for(int i = 0; i < n; i++) {
        
        if(strcmp(tip_filtera, "izvodjac") == 0 && strcmp(naziv_filtera, pesme[i].naziv_grupe) == 0
            || strcmp(tip_filtera, "tip") == 0 && strcmp(naziv_filtera, pesme[i].naziv_tipa) == 0) {

            fprintf(file, "%s %s %s\n",
                pesme[i].naziv_grupe,
                pesme[i].naziv_tipa,
                pesme[i].naziv_pesme);
        }      
    }

}

int main(int argc, char* args[]) {
    
    struct SONG pesme[MAX_NIZ];
    int n = 0;

    FILE* file = fopen("ulaz.txt", "r");
    Ucitaj(file, pesme, &n);
    fclose(file);

    file = fopen("izlaz.txt", "w");
    Ispisi(file, pesme, args[1], args[2], n);
    fclose(file);

    return 0;
}