#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "introprog_structs_lists_input.h"

#define MAX_STR 255

typedef struct _element element; 

typedef struct _list {
    element *first;
    int count;
} list;

struct _element{
    char title[MAX_STR];
    char author[MAX_STR];
    int year;
    long long int isbn;
    element* next;
};

element* insert_sorted(element *first, element *new_elem) {
    if(first == NULL){
        first = new_elem;
    }
    else if(new_elem -> isbn < first -> isbn){
        new_elem -> next = first;
        first = new_elem;
    }
    else{
        element *temp = first;
        while(temp -> next != NULL && temp -> next -> isbn < new_elem -> isbn){
            temp = temp -> next;
        }
        new_elem -> next = temp -> next;
        temp -> next = new_elem;
    }
    return first;
}

element *construct_element(char *title, char* author, int year, long long int isbn) {
    element* buch = (element*) malloc(sizeof(element));
    strncpy (buch -> title, title, MAX_STR-1);
    strncpy (buch -> author, author, MAX_STR-1);
    buch -> title[254] ='\0';
    buch -> year = year;
    buch -> isbn = isbn;
    buch -> next = NULL;
    return buch;
};

void free_list(list *alist) {
    element* temp = alist -> first; 
    while(temp != NULL){
        element* tempsave = temp->next;
        free(temp);
        temp = tempsave;
    }
    free(alist);
}

void read_list(char* filename, list *alist) {
    element* new_elem;
    char* title;
    char* author;
    int year;
    long long int isbn;
    read_line_context ctx;
    open_file(&ctx, filename);
    while(read_line(&ctx, &title, &author, &year, &isbn) == 0) {
        new_elem = construct_element(title, author, year, isbn);
        alist->first = insert_sorted(alist->first, new_elem);
        alist->count++;
    }
}

list* construct_list() {
    list *alist = malloc(sizeof(list));
    alist->first = NULL;
    alist->count = 0;
    return alist;
}

void print_list(list *alist) {
    printf("Meine Bibliothek\n================\n\n");
    int counter = 1;
    element *elem = alist->first;
    while (elem != NULL) {
        printf("Buch %d\n", counter);
        printf("\tTitel: %s\n", elem->title);
        printf("\tAutor: %s\n", elem->author);
        printf("\tJahr:  %d\n", elem->year);
        printf("\tISBN:  %lld\n", elem->isbn);
        elem = elem->next;
        counter++;
    }
}

int main(int argc, char** argv) {
    list *alist = construct_list();
    read_list(argc>1?argv[1]:"buecherliste.txt", alist);
    print_list(alist);
    free_list(alist);
    return 0;
}
