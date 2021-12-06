#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_NIZ 30
#define MAX_NAZIV 21

struct kafa_st {
    char naziv_kafe[MAX_NAZIV];
    float cena_kafe;
    unsigned int kolicina_kofeina;
};

struct kafa_pred_ispit_st {
    char naziv_kafe[MAX_NAZIV];
    unsigned int br_kafa;
    float cena;
    unsigned int kolicina_kofeina;
};

void Read(FILE* file, struct kafa_st kafe[], int* n) {
    *n = 0;
    
    while(fscanf(file, "%s %f %d",
        kafe[*n].naziv_kafe,
        &kafe[*n].cena_kafe,
        &kafe[*n].kolicina_kofeina
    ) != EOF) { ++(*n); }
}

float Average(struct kafa_st kafe[], int n) {
    float average = 0;

    for(int i = 0; i < n; ++i) {
        average += (float)kafe[i].kolicina_kofeina;
    }

    average = average / (float)n;
    return average;
}

void Calculate(struct kafa_st kafe[], struct kafa_pred_ispit_st kafe_ispit[], int dozvoljena_doza, int n) {

    for(int i = 0; i < n; ++i) {
        strcpy(kafe_ispit[i].naziv_kafe, kafe[i].naziv_kafe);
        kafe_ispit[i].br_kafa = dozvoljena_doza / kafe[i].kolicina_kofeina;
        kafe_ispit[i].cena = kafe_ispit[i].br_kafa * kafe[i].cena_kafe;
        kafe_ispit[i].kolicina_kofeina = kafe_ispit[i].br_kafa * kafe[i].kolicina_kofeina;
    }    
}

void Write(FILE* file, struct kafa_st kafe[], struct kafa_pred_ispit_st kafe_ispit[], int n) {
    char upozorenje[] = "UPOZORENJE, jaka kafa";
    float prosecan_kofein = Average(kafe, n);

    for(int i = 0; i < n; ++i) {
        fprintf(file, "%-21s %4d %8.2f %8d", 
            kafe_ispit[i].naziv_kafe,
            kafe_ispit[i].br_kafa,
            kafe_ispit[i].cena,
            kafe_ispit[i].kolicina_kofeina
        );

        if(kafe[i].kolicina_kofeina > prosecan_kofein) {
            fprintf(file, "    %s\n", upozorenje);
        }
        else {
            fprintf(file, "\n");
        }
    }
}

int main(int argc, char *argv[]) {

    int dozvoljena_doza = atoi(argv[3]);
    int n;

    struct kafa_st kafe[MAX_NIZ];
    struct kafa_pred_ispit_st kafe_ispit[MAX_NIZ];

    FILE* file = fopen(argv[1], "r");

    Read(file, kafe, &n);

    Calculate(kafe, kafe_ispit, dozvoljena_doza, n);
    fclose(file);
    
    file = fopen(argv[2], "w");
    Write(file, kafe, kafe_ispit, n);
    fclose(file);

    return 0;
}