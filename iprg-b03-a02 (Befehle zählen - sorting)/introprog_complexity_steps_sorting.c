#include <stdio.h>
#include <stdlib.h>
#include "introprog_complexity_steps_input.h"

const int MAX_VALUE = 5000000;

void count_sort_calculate_counts(int input_array[], int len, int count_array[], unsigned int* befehle) {
    (*befehle)++;                                                           // Initialisierung "j" => 1 Befehl 
    for(int j = 0; j < len; j++){
        (*befehle)++;                                                       // Abgleich "j < len" in Schleife => 1 Befehl jedes Mal wenn die äußere Schleife durchlaufen wird                      
        (*befehle)++;                                                       // Inkrementierung j => 1 Befehl jedes Mal wenn die äußere Schleife durchlaufen wird

        count_array[input_array[j]] = count_array[input_array[j]]+1;
        (*befehle)++;                                                       // Zuweisung => 1 Befehl
    }
    (*befehle)++;                                                           // finaler Abgleich "j < len" der zum Auslaufen der Schleife führt => 1 Befehl
}

void count_sort_write_output_array(int array[], int len, int count_array[], unsigned int* befehle) {
    int k = 0;
    (*befehle)++;                                                           // Initialisierung "k" => 1 Befehl

    (*befehle)++;                                                           // Initialisierung "j" zum Anfang der äußeren for-Schleife => 1 Befehl
    for(int j = 0; j < MAX_VALUE+1; j++){
        (*befehle)++;                                                       // Abgleich "j < MAX_VALUE" in äußere Schleife => 1 Befehl jedes Mal wenn die äußere Schleife durchlaufen wird
        (*befehle)++;                                                       // Inkrementierung j => 1 Befehl jedes Mal wenn die äußere Schleife durchlaufen wird

        (*befehle)++;                                                       // Deklaration "i" zum Anfang der inneren for-Schleife => 1 Befehl
        for(int i = 0; i < count_array[j]; i++){
            (*befehle)++;                                                   // Abgleich "i < count_array[j]" in innerer Schleife => 1 Befehl jedes Mal wenn die äußere Schleife durchlaufen wird
            (*befehle)++;                                                   // Inkrementierung i => 1 Befehl jedes Mal wenn die innere Schleife durchlaufen wird

            array[k] = j;
            (*befehle)++;                                                   // Zuweisung "array[k] = j" => 1 Befehl
            
            k = k + 1;
            (*befehle)++;                                                   // Inkrementierung k => 1 Befehl

        }
        (*befehle)++;                                                       // finaler Abgleich "i < count_array[j]" der zum Auslaufen der inneren Schleife führt => 1 Befehl
    }
    (*befehle)++;                                                           // finaler Abgleich "j < MAX_VALUE+1" der zum Auslaufen der äußeren Schleife führt => 1 Befehl
}

void count_sort(int array[], int len, unsigned int* befehle) {
    int* count_array = calloc(MAX_VALUE+1, sizeof(int));
    (*befehle)++;                                                           // Initialisierung count_array mit calloc => 1 Befehl

    count_sort_calculate_counts(array, len, count_array, befehle);
    count_sort_write_output_array(array, len, count_array, befehle);
    free(count_array);
}


void insertion_sort(int array[], int len, unsigned int* befehle) {
    (*befehle)++;                                                           // Initialisierung "j" => 1 Befehl
    for(int j = 1; j < len; j++){
        (*befehle)++;                                                       // Abgleich "j < len" in äußere Schleife => 1 Befehl jedes Mal wenn die äußere Schleife durchlaufen wird
        (*befehle)++;                                                       // Inkrementierung j => 1 Befehl jedes Mal wenn die äußere Schleife durchlaufen wird

        int key = array[j];
        (*befehle)++;                                                       // Zuweisung "key" => 1 Befehl

        int i = j - 1;
        (*befehle)++;                                                       // Zuweisung i / Dekrementierung j => 1 Befehl

        while(i >= 0 && array[i] > key){
            (*befehle)++;
            (*befehle)++;

            array[i+1] = array[i];
            (*befehle)++;                                                   // Inkrementierung array => 1 Befehl

            i = i-1;
            (*befehle)++;                                                   // Dekrementierung i => 1 Befehl
        }
        array[i+1] = key;
        (*befehle)++;                                                       // Zuweisung "key" => 1 Befehl
    }
    (*befehle)++;                                                           // finaler Abgleich "j < len" der zum Auslaufen der äußeren Schleife führt => 1 Befehl
}


int main(int argc, char *argv[]) {
    const int WERTE[] = {10000,20000,30000,40000,50000};
    const int LEN_WERTE = 5;
    const int LEN_ALGORITHMEN = 2;

    int rc = 0;
    unsigned int befehle_array[LEN_ALGORITHMEN][LEN_WERTE];
    double laufzeit_array[LEN_ALGORITHMEN][LEN_WERTE];

    for(int j = 0; j < LEN_WERTE; ++j) {
        int n = WERTE[j];

        int* array_countsort = malloc(sizeof(int) * n);
        int* array_insertionsort = malloc(sizeof(int) * n);

        fill_array_randomly(array_countsort, n, MAX_VALUE);
        copy_array_elements(array_insertionsort, array_countsort, n);

        if(!check_equality_of_arrays(array_countsort, array_insertionsort, n)) {
            printf("Die Eingaben für beide Algorithmen müssen für die Vergleichbarkeit gleich sein!\n");
            return -1;
        }

        for(int i = 0; i < LEN_ALGORITHMEN; ++i) {
            unsigned int anzahl_befehle = 0;

            start_timer();

            if(i==0) {
                    count_sort(array_countsort, n, &anzahl_befehle);
            } else if(i==1) {
                    insertion_sort(array_insertionsort, n, &anzahl_befehle);
            }

            laufzeit_array[i][j] = end_timer();
            befehle_array[i][j] = anzahl_befehle;
        }

        if(!check_equality_of_arrays(array_countsort, array_insertionsort, n)) {
            printf("Die Arrays sind nicht gleich. Eines muss (falsch) sortiert worden sein!\n");
            rc = -1;
        }

        free(array_countsort);
        free(array_insertionsort);
    }

    printf("Parameter MAX_VALUE hat den Wert %d\n", MAX_VALUE);
    printf("\t %32s           %32s \n", "Countsort","Insertionsort");
    printf("%8s \t %16s %16s \t %16s %16s \n", "n","Befehle", "Laufzeit","Befehle","Laufzeit");

    for(int j = 0; j < LEN_WERTE; ++j) {
        printf("%8d \t ",WERTE[j]);
        for(int i = 0; i < LEN_ALGORITHMEN; ++i) {
            printf("%16u %16.4f \t ",  befehle_array[i][j], laufzeit_array[i][j]);
        }
        printf("\n");
    }

    return rc;
}
