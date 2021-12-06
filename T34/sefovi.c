#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAX_SIFRA 6
#define MAX_ZAUZETOST 9
#define MAX_NIZ 50
#define PROCENAT 115

struct sef_st {
    char sifra[MAX_SIFRA];
    char zauzetost[MAX_ZAUZETOST];
    unsigned int cena_zakupa;
    double tezina_robe;
};

FILE* file_open(char* file_name, char* mode) {
    FILE* file = fopen(file_name, mode);

    if(file == NULL) {
        printf("Greška pri otvaranju %s fajla!\n", file_name);
        exit(EXIT_FAILURE);
    }

    return file;
} 

void file_read(FILE* file, struct sef_st sefovi[], int* n) {
    while(fscanf(file, "%s %s %d %lf", 
        sefovi[*n].sifra,
        sefovi[*n].zauzetost,
        &sefovi[*n].cena_zakupa,
        &sefovi[*n].tezina_robe
    ) != EOF) {
        (*n)++;
    }
}

void file_write(FILE* file, struct sef_st sefovi[], double max_tezina, int n) {
    int br_slobodnih = 0;

    fprintf(file, "Cene sefova nakon oporezivanja:\n\n");
    for(int i = 0; i < n; ++i) {
        if(strcmp(sefovi[i].zauzetost, "zauzet") == 0) {
            if(sefovi[i].tezina_robe > max_tezina) {
                sefovi[i].cena_zakupa *= PROCENAT;
            }
        }
        else {
            br_slobodnih++;
        }

        fprintf(file, "%s %s %d %.1lf\n",
            sefovi[i].sifra,
            sefovi[i].zauzetost,
            sefovi[i].cena_zakupa,
            sefovi[i].tezina_robe
        );
    }
    fprintf(file, "\n\nBroj slobodnih sefova: %d\n", br_slobodnih);
}

int main(int argc, char* args[]) {

    struct sef_st sefovi[MAX_NIZ];
    int n = 0;

    if(argc != 4) {
        printf("Argumenti nisu dobro uneti!\n");
        exit(EXIT_FAILURE);
    }

    FILE* file = file_open(args[1], "r");
    file_read(file, sefovi, &n);
    fclose(file);

    file = file_open(args[3], "w");
    file_write(file, sefovi, strtod(args[2], NULL), n);
    fclose(file);

    return 0;
}