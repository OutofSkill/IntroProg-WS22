#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "quicksort.h"

void init_list(list* mylist){                                                   // Diese Funktion initialisiert die Liste
    mylist -> first = NULL;
    mylist -> last = NULL;
}


void insert_list(list_element* le, list* mylist){                               // Diese Funktion fügt Listenelemente an die Liste an
    if(mylist -> first == NULL){
        mylist -> first = le;
        mylist -> last = le;
    }
    else if(mylist -> first -> count == mylist -> last -> count){
        mylist -> first -> next = le;
        mylist -> last = le;
    }
    else{
        mylist -> last -> next = le;
        mylist -> last = le;
    }     
}

void free_list(list* mylist){                                                   // Speicher für Listenelemente wieder freigeben
    list_element* temp = mylist -> first; 
    while(temp != NULL){
        list_element* tempsave = temp->next;
        free(temp -> password);
        free(temp);
        temp = tempsave;
    }
}

void read_data(char* filename, list* mylist){                                   // Namen, Zahlen Paare in Liste einlesen
    FILE* eingabe_quicksort = fopen(filename, "r");
    
    char* buffer = malloc(sizeof(char) * 50);                                  // Speicher allozieren

    char* passwort = malloc(sizeof(char) * 50);                                // Daten in list_element einlesen
    int häufigkeit = 0;                                                         // insert_list benutzen, um list_element in Liste einzufügen

    while(fgets(buffer, 50, eingabe_quicksort) != NULL) {
        sscanf(buffer, "%s %d", passwort, &häufigkeit);
        list_element* new_elem = malloc(sizeof(list_element));
        new_elem -> password = malloc(sizeof(char) * 50);
        strcpy(new_elem -> password, passwort);
        new_elem -> count = häufigkeit;
        new_elem -> next = NULL;
        insert_list(new_elem, mylist);
    }
    fclose(eingabe_quicksort);
    free(buffer);
    free(passwort);
}                                                                               // read_data funktional, do not change

list_element* partition( list* input, list* left, list* right ){                // Liste teilen. Teillisten werden in left und right zurück gegeben
    list_element* pivot = input -> first;
    list_element* temp = pivot -> next;
    pivot -> next = NULL;

    while(temp != NULL){
        list_element* tempsave = temp -> next;
        temp -> next = NULL;

        if(temp -> count < pivot -> count){
            insert_list(temp, left);
        }
        else{
            insert_list(temp, right);
        }
        temp = tempsave;
    }
    return pivot;
}

void qsort_list(list* mylist){                                                  // Hauptfunktion des quicksort Algorithmus
    if(mylist -> first == mylist -> last){
        return;
    }
    else{
        list left;
        list right;
        init_list(&left);
        init_list(&right);
        list_element* pivot = partition(mylist, &left, &right);

        qsort_list(&left);
        qsort_list(&right);

        if(left.first == NULL){
            mylist -> first = pivot;
        }
        else{
            mylist -> first = left.first;
            left.last -> next = pivot;         
        }
        if(right.first == NULL){
            pivot -> next = NULL;
            mylist -> last = pivot;          
        }
        else{
            pivot -> next = right.first;
            mylist -> last = right.last;        
        }
    }
}

void print_list(list* mylist){                                                  // Liste ausgeben
    int counter = 1;
    list_element* print_elem = mylist -> first;
    printf("%s %d\n", print_elem -> password, print_elem -> count);
    print_elem = print_elem -> next;
    while (print_elem != NULL) {                                                // Laufe über die list_element in mylist und gebe sie aus.
        printf("%s %d\n", print_elem -> password, print_elem -> count);
        print_elem = print_elem -> next;
        counter++;
    }
}
