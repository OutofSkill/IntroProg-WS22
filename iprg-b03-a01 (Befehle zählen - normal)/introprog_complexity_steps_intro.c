#include <stdio.h>
#include "introprog_complexity_steps_input.h"

long for_linear(int n, int* befehle){ 
    long sum = 0;
    (*befehle)++;                                           // Initialisierung sum => 1 Befehl
    
    (*befehle)++;                                           // Deklaration "i" in for-Schleife => 1 Befehl
    for(int i = 1; i <= n; ++i) {
        (*befehle)++;                                       // Vergleich "i <= n" in for-Schleife => 1 Befehl jedes Mal wenn die Schleife durchlaufen wird
        (*befehle)++;                                       // Inkrementierung i => 1 Befehl jedes Mal wenn die Schleife durchlaufen
        sum += get_value_one();
        (*befehle)++;                                       // Deklaration sum => 1 Befehl jedes Mal wenn die Schleife durchlaufen wird
    }
    (*befehle)++;                                           // finaler Abgleich "i <= n" der zum Auslaufen der Schleife führt => 1 Befehl
    
    (*befehle)++;                                           // Funktion gibt einen Wert zurück => 1 Befehl
    return sum;         
}

long for_quadratisch(int n, int* befehle){
    long sum = 0;
    (*befehle)++;                                           // Initialisierung sum => 1 Befehl
    
    (*befehle)++;                                           // Deklaration i zum Anfang der äußere Schleife => 1 Befehl
    for(int i = 1; i <= n; ++i) {
        (*befehle)++;                                       // Vergleich "i <= n" in äußere Schleife => 1 Befehl jedes Mal wenn die äußere Schleife durchlaufen wird
        (*befehle)++;                                       // Inkrementierung i => 1 Befehl jedes Mal wenn die äußere Schleife durchlaufen wird
        
        (*befehle)++;                                       // Deklaration j zum Anfang der inntere Schleife => 1 Befehl                               
        for(int j = 1; j <= n; ++j) {
            (*befehle)++;                                   // Vergleich "j <= n" in innere Schleife => 1 Befehl jedes Mal wenn die innere Schleife durchlaufen wird
            (*befehle)++;                                   // Inkrementierung j => 1 Befehl jedes Mal wenn die innere Schleife durchlaufen wird
            sum += get_value_one();
            (*befehle)++;                                   // Deklaration sum => 1 Befehl jedes Mal wenn die Schleifen durchlaufen werden
        }
        (*befehle)++;                                       // finaler Abgleich "j <= n" der zum Auslaufen der inneren Schleife führt => 1 Befehl
    }                                                       
    (*befehle)++;                                           // finaler Abgleich "i <= n" der zum Auslaufen der äußeren Schleife führt => 1 Befehl
    
    (*befehle)++;                                           // Funktion gibt einen Wert zurück => 1 Befehl
    return sum;
}

long for_kubisch(int n, int* befehle){
    long sum = 0;
    (*befehle)++;                                           // Initialisierung von sum => 1 Befehl

    (*befehle)++;                                           // Initialisierung von i für äußere Schleife => 1 Befehl
    for(int i = 1; i <= n; ++i) {
        (*befehle)++;                                       // Vergleich "i <= n" in äußere Schleife => 1 Befehl jedes Mal wenn die äußere Schleife durchlaufen wird
        (*befehle)++;                                       // Inkrementierung i => 1 Befehl jedes Mal wenn die äußere Schleife durchlaufen wird
        
        (*befehle)++;                                       // Initialisierung von j für mittlere Schleife => 1 Befehl 
        for(int j = 1; j <= n; ++j) {
            (*befehle)++;                                   // Vergleich "j <= n" in mittlere Schleife => 1 Befehl jedes Mal wenn die mittlere Schleife durchlaufen wird
            (*befehle)++;                                   // Inkrementierung j => 1 Befehl jedes Mal wenn die mittlere Schleife durchlaufen wird

            (*befehle)++;                                   // Initialisierung von k für innere Schleife => 1 Befehl
            for(int k = 1; k <= n; ++k) {
                (*befehle)++;                               // Vergleich "k <= n" in innerer Schleife => 1 Befehl jedes Mal wenn die innere Schleife durchlaufen wird
                (*befehle)++;                               // Inkrementierung k => 1 Befehl jedes Mal wenn die innere Schleife durchlaufen wird
                sum += get_value_one();
                (*befehle)++;                               // Deklaration sum => 1 Befehl jedes Mal wenn die Schleife durchlaufen wird
            }
            (*befehle)++;                                   // finaler Abgleich "k <= n" der zum Auslauf der inneren Schleife führt
        }
        (*befehle)++;                                       // finaler Abgleich "j <= n" der zum Auslauf der mittleren Schleife führt
    }
    (*befehle)++;                                           // finaler Abgleich "i <= n" der zum Auslauf der äußeren Schleife führt

    (*befehle)++;                                           // Funktion gibt einen Wert zurück => 1 Befehl
    return sum;
}

int main(int argc, char *argv[])
{
    const int WERTE[] = {5,6,7,8,9,10};
    const int LEN_WERTE = 6;
    const int LEN_ALGORITHMEN = 3;

    long befehle_array[LEN_ALGORITHMEN][LEN_WERTE];
    long werte_array[LEN_ALGORITHMEN][LEN_WERTE];
    double laufzeit_array[LEN_ALGORITHMEN][LEN_WERTE];

    for(int j = 0; j < LEN_WERTE; ++j) {
        int n = WERTE[j];
        for(int i = 0; i < LEN_ALGORITHMEN; ++i) {
            printf("Starte Algorithmus %d mit Wert %d\n",
                (i+1), n);
            int anzahl_befehle = 0;
            int wert = 0;

            start_timer();

            if(i==0) {
                wert = for_linear(n, &anzahl_befehle);
            }
            else if(i==1) {
                wert = for_quadratisch(n, &anzahl_befehle);
            }
            else if(i==2) {
                wert = for_kubisch(n, &anzahl_befehle);
            }

            laufzeit_array[i][j] = end_timer();
            werte_array[i][j] = wert;
            befehle_array[i][j] = anzahl_befehle;
        }
        printf("\n");
    }

    printf("%3s \t%-28s \t%-28s \t%-28s\n", "","linear", "quadratisch", "kubisch");
    printf("%3s \t %5s %10s %10s\t %5s %10s %10s\t %5s %10s %10s\n", "n","Wert","Befehle","Laufzeit","Wert","Befehle","Laufzeit","Wert","Befehle","Laufzeit");

    for(int j = 0; j < LEN_WERTE; ++j) {
        printf("%3d \t ",WERTE[j]);
        for(int i = 0; i < LEN_ALGORITHMEN; ++i) {
            printf("%5ld %10ld %10.4f \t ", werte_array[i][j], befehle_array[i][j], laufzeit_array[i][j]);
        }
        printf("\n");
    }

    return 0;
}