#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>

#define MAX_STUDENTI 20

struct student {
    char br_indeksa[11];
    char ime[21];
    char prezime[21];
    unsigned int br_poena;
};

void swap(struct student* s1, struct student* s2) {
    struct student temp;

    temp = *s1;
    *s1 = *s2;
    *s2 = temp;
}

int convert_indeks(char br_indeksa[]) {
    char temp[4] = {'\0', '\0', '\0', '\0'};
    for(int i = 2; i < strlen(br_indeksa); i++) {
        if(br_indeksa[i] == '/') {
            break;
        }
        temp[i-2] = br_indeksa[i];
    }

    return atoi(temp);
}

void sort(struct student studenti[], int n) {

    for(int i = 0; i < n-1; i++) {
        for(int j = 0; j < n-i-1; j++) {
            if(convert_indeks(studenti[j].br_indeksa) > convert_indeks(studenti[j+1].br_indeksa)) {
                swap(&studenti[j], &studenti[j+1]);
            }
        }
    }

    FILE* file = fopen("sortirani_studenti.txt", "w");
    for(int i = 0; i < n; i++) {
        fprintf(file, "%s %s %s %d\n",
        studenti[i].br_indeksa,
        studenti[i].ime,
        studenti[i].prezime,
        studenti[i].br_poena);
    }
    fclose(file);
}

void read(struct student studenti[], char f_name[], int* n) {

    FILE* file = fopen(f_name, "r");

    while(fscanf(file, "%s %s %s %d",
        studenti[*n].br_indeksa,
        studenti[*n].ime,
        studenti[*n].prezime,
        &studenti[*n].br_poena
        ) != EOF) {
        (*n)++;
    }
}

void prezime(struct student studenti[], int n) {

    int max = 0;
    int min = 30;
    int max_index, min_index;
    for(int i = 0; i < n; i++) {
        if(max <= strlen(studenti[i].prezime)) {
            max = strlen(studenti[i].prezime);
            max_index = i;
        }
        if(min >= strlen(studenti[i].prezime)) {
            min = strlen(studenti[i].prezime);
            min_index = i;
        }
    }

    printf("Student sa najdužim prezimenom je:\n");
    printf("%s %s %s",
    studenti[max_index].br_indeksa,
    studenti[max_index].ime,
    studenti[max_index].prezime);

    printf("\nStudent sa najkraćim prezimenom je:\n");
    printf("%s %s %s",
    studenti[min_index].br_indeksa,
    studenti[min_index].ime,
    studenti[min_index].prezime);
    printf("\n");
}

void bodovi(struct student studenti[], int n, char* bodovi) {
    int b = atoi(bodovi);

    char f_name[30] = "preko_";
    strcat(f_name, bodovi);
    strcat(f_name, "_poena.txt");
    FILE* file = fopen(f_name, "w");

    for(int i = 0; i < n; i++) {
        if(studenti[i].br_poena > b) {
            fprintf(file, "%s %s %s %d\n",
            studenti[i].br_indeksa,
            studenti[i].ime,
            studenti[i].prezime,
            studenti[i].br_poena);
        }
    }

    fclose(file);
}

void prosek(struct student studenti[], int n) {
    int sum = 0;

    for(int i = 0; i < n; i++) {
        sum += (int)strlen(studenti[i].ime);
    }

    double p = sum/(float)n;

    FILE* file = fopen("izlaz.txt", "w");
    fprintf(file, "Prosečna dužina imena studenata iznosi %.2f karaktera.\n", p);
    fclose(file);
}

int main(int argc, char* argv[]) {

    int n = 0;
    struct student studenti[MAX_STUDENTI];

    read(studenti, argv[1], &n);
    sort(studenti, n);
    prezime(studenti, n);
    bodovi(studenti, n, argv[2]);
    prosek(studenti, n);

    return 0;
}