#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "introprog_input_stacks-rpn.h"

typedef struct _stack stack;
typedef struct _stack_element stack_element;

struct _stack {
    stack_element* top;
};

struct _stack_element {
    stack_element* next;
    float value;
};

void stack_push(stack* astack, float value){
    stack_element* new_elem = malloc(sizeof(stack_element));
    new_elem -> value = value;
    new_elem -> next = astack -> top;
    astack -> top = new_elem; 
}

float stack_pop(stack* astack){
    if (astack -> top == NULL){
        return NAN;
    }
    else{
        stack_element* elem = astack -> top;
        float value = astack -> top -> value;
        astack -> top = elem -> next;
        free(elem);
        return value;
    }
}

void process(stack* astack, char* token){
    float tmp1;
    float tmp2;
    if(is_add(token) == 1){
        tmp1 = stack_pop(astack);
        tmp2 = stack_pop(astack);
        stack_push(astack, tmp1 + tmp2);
        return;         
    }
    else if(is_sub(token) == 1){
        tmp1 = stack_pop(astack);
        tmp2 = stack_pop(astack);
        stack_push(astack, tmp2 - tmp1);    
        return;    
    }
    else if(is_mult(token) == 1){
        tmp1 = stack_pop(astack);
        tmp2 = stack_pop(astack);
        stack_push(astack, tmp1 * tmp2);
        return;
    }
    else if(is_number(token) == 1){
        stack_push(astack, atof(token));
        return;
    }    
    printf("\n<Logik fehlt!>\n");
    return;
}

void print_stack(stack *astack) {
    int counter = 0;
    printf("\n |xxxxx|xxxxxxxxxxxxxxxxxxx|xxxxxxxxxxxxxxxxxxx|xxxxxxxxx|\n");
    printf(" | Nr. | Adresse           | Next              | Wert    |\n");
    printf(" |-----|-------------------|-------------------|---------|\n");
    for (stack_element* elem=astack->top; elem != NULL; elem = elem->next) {
        printf(" | %3d | %17p | %17p | %7.3f |\n", counter, elem, elem->next, elem->value);
        counter++;
    }
    printf(" |xxxxx|xxxxxxxxxxxxxxxxxxx|xxxxxxxxxxxxxxxxxxx|xxxxxxxxx|\n");
}

stack* stack_erstellen() {
    stack* astack = malloc(sizeof(stack));
    astack -> top = NULL;
    return astack;
}

int main(int argc, char** args){
    stack* astack = stack_erstellen();
    char zeile[MAX_STR];
    char* token;

    intro();
    while (taschenrechner_input(zeile) == 0) {
        token = strtok(zeile, " ");

        while (token != NULL) {
            printf("Token: %s\n", token);
            process(astack, token);
            token = strtok(NULL, " ");
            print_stack(astack);
        }

        printf("\nExtrahiere Resultat\n");
        float result = stack_pop(astack);
        print_stack(astack);

        if (astack->top != NULL) {
            while (astack->top != NULL) {
                stack_pop(astack);
            }
            printf("\nDoes not Compute: Stack nicht leer!\n");
        } else if (result != result) {
            printf("\nDoes not Compute: Berechnung fehlgeschlagen!\n");
        } else {
            printf("\nDein Ergebnis:\t%7.3f\n\n", result);
        }
    }
    free(astack);
}
