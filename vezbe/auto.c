#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAX_IME 21
#define MAX_SIZE 30

typedef struct auto_st {
    char marka[MAX_IME];
    float kubikaza;
    unsigned int godiste;
} AUTO;

FILE* safe_open(char* f_name, char* mode) {

    FILE* f = fopen(f_name, mode);
    if(f == NULL) {
        printf("Datoteka nije uspešno učitan\n");
        exit(EXIT_FAILURE);
    }
    return f;
}

void read(FILE* fin, AUTO* a, int* n) {
    while(fscanf(fin, "%s %f %ui", 
        a[*n].marka,
        &a[*n].kubikaza,
        &a[*n].godiste) != EOF) {
        (*n)++;
    }   
}

int find(AUTO auti[MAX_SIZE], int n, float k) {
    unsigned int max_godina = 0;
    int index = 0;

    for(int i = 0; i < n; i++) {
        if(auti[i].kubikaza <= k && auti[i].godiste >= max_godina) {
            index = i;
            max_godina = auti[i].godiste;
        }
    }

    return index;
}

int main(int argc, char** argv) {
    int n = 0;
    AUTO auti[MAX_SIZE];

    if(argc != 3) {
        printf("Los unos sa komande linije\n");
        exit(EXIT_FAILURE);
    }

    float kubikaza = atof(argv[2]);
    FILE* fin = safe_open(argv[1], "r");
    read(fin, auti, &n);
    fclose(fin);

    int index = find(auti, n, kubikaza);
    char f_name[MAX_SIZE + 4];
    stpcpy(f_name, auti[index].marka);
    FILE* fout = fopen(strcat(f_name, ".txt"), "w");
    fprintf(fout, "%s %f %u\n", auti[index].marka, auti[index].kubikaza, auti[index].godiste);

    return 0;
}
