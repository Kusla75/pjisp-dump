#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_NAZIV 16
#define MAX_NIZ 30

struct kredit {
    char ime[MAX_NAZIV];
    char prezime[MAX_NAZIV];
    char vrsta_kredita[9];
    char odobren[3];
    unsigned int iznos_kredita; 
    unsigned int ucesce;
    double kamata;
    unsigned int br_godina;
};

void Ucitaj(FILE* file, struct kredit* krediti, int* n) {
    while(fscanf(file, "%s %s %s %s %u %u %lf %u",
        krediti[*n].ime,
        krediti[*n].prezime,
        krediti[*n].vrsta_kredita,
        krediti[*n].odobren,
        &krediti[*n].iznos_kredita,
        &krediti[*n].ucesce,
        &krediti[*n].kamata,
        &krediti[*n].br_godina
    ) != EOF) {
        (*n)++;
    }
}

double Racunaj(struct kredit k) {
    double zarada = (double)(k.iznos_kredita - k.ucesce) / 100 * k.kamata * (double)k.br_godina;
    return zarada;
}

void Ispisi(FILE* file, struct kredit krediti[], int* n, char vrsta_kredita[]) {
    double ukupna_zarada = 0;

    for(int i = 0; i < *n; ++i) {
        if(strcmp(krediti[i].odobren, "da") == 0 && strcmp(krediti[i].vrsta_kredita, vrsta_kredita) == 0) {
            ukupna_zarada += Racunaj(krediti[i]);
            fprintf(file, "%-15s %-15s %-15s %-15s %-15.u %-15.u %-15.lf %-15.u\n", 
            krediti[i].ime,
            krediti[i].prezime,
            krediti[i].vrsta_kredita,
            krediti[i].odobren,
            krediti[i].iznos_kredita,
            krediti[i].ucesce,
            krediti[i].kamata,
            krediti[i].br_godina);
        }
    }

    if(ukupna_zarada == 0) {
        fprintf(file, "Nema odobrenih kredita.\n");
    }
    else {
        fprintf(file, "\nUkupna zarada banke je %.2lf\n", ukupna_zarada);
    }
}

int main(int argc, char* args[]) {

    int n = 0;
    char vrsta_kredita[9];
    strcpy(vrsta_kredita, args[1]);
    struct kredit krediti[MAX_NIZ];
    
    FILE* file = fopen(args[2], "r");
    Ucitaj(file, krediti, &n);
    fclose(file);

    char* file_out = args[1];
    strcat(file_out, ".txt");

    file = fopen(file_out, "w");
    Ispisi(file, krediti, &n, vrsta_kredita);
    fclose(file);
    
    return 0;
}