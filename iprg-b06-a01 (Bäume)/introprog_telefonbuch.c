#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "introprog_telefonbuch.h"

// !!!! Anfang introprog_telefonbuch.h  -- nach Fertigstellung löschen !!!!
/*
typedef struct bst_node bst_node;
typedef struct bstree  bstree;

struct bst_node
{
    bst_node* left;
    bst_node* right;
    bst_node* parent;
    unsigned long phone;
    char *name;
};

struct bstree
{
    struct bst_node* root;
    int count;
};
*/
// !!!! Ende introprog_telefonbuch.h  -- nach Fertigstellung löschen !!!!

void bst_insert_node(bstree* bst, unsigned long phone, char *name) {                     
    bst_node* new_node = (bst_node*) malloc(sizeof(bst_node));                       // construct_node innerhalb der insert_node Funktion
    new_node -> name = (char*) calloc(strlen(name)+1, sizeof(char)); 
    new_node -> left = NULL;
    new_node -> right = NULL;
    new_node -> parent = NULL;
    new_node -> phone = phone;
    strncpy(new_node -> name, name, strlen(name)+1);      
    
    bst_node* nummer_doppelt = find_node(bst, phone);                                   // Nutzt die find_node Funktion um nach der Telefonnummer zu suchen um auf Dopelgänger zu überprüfen
    if(nummer_doppelt != NULL){
        printf("Die Telefonnummer %lu existiert bereits im Telefonbuch \n ", phone);
        return;
    }       
    bst_node* temp = bst -> root;
    bst_node* temp_parent = NULL;
    if(bst -> root == NULL){
        bst -> root = new_node;                                    
        return;
    }
    else{
        while(temp != NULL){
            temp_parent = temp;
            if(temp -> phone > phone){
                temp = temp -> left;
            }
            else{
                temp = temp -> right;
            }
        }
    }
    if(phone <= temp_parent -> phone){
        new_node -> parent = temp_parent;
        temp_parent -> left = new_node;
    }
    else{
        new_node -> parent = temp_parent;
        temp_parent -> right = new_node;
    }
    return;
}


bst_node* find_node(bstree* bst, unsigned long phone) {
    bst_node* temp = bst -> root;
    while(temp != NULL){
        if(temp -> phone == phone){
            return temp;
        }
        else if(temp -> phone >= phone){
            temp = temp -> left;
        }
        else if(temp -> phone < phone){
            temp = temp -> right;
        }
    }
    return NULL;
}

void bst_in_order_walk_node(bst_node* node) {
    if(node == NULL){                           // Falls node nicht existiert wird die Funktion direkt abgebrochen
        return;
    }
    bst_node* temp = node;
    if(temp -> left != NULL){
        bst_in_order_walk_node(node -> left);   // Falls es eine linkes Child gibt wird dieses rekursiv zuerst angesteuert
    }
    print_node(node);
    if(temp -> right != NULL){
        bst_in_order_walk_node(node -> right);   // Falls es eine rechtes Child gibt wird dieses rekursiv angesteuert nachdem das linke Child angesteuert und geprintet wurde
    }
}

void bst_in_order_walk(bstree* bst) {
    if (bst != NULL) {
        bst_in_order_walk_node(bst->root);
    }
}

void bst_free_subtree(bst_node* node) {           
    if(node == NULL){
        return;
    }
    bst_free_subtree(node -> left);                         
    bst_free_subtree(node -> right);
    free(node -> name);
    free(node);                            
    return; 
}

void bst_free_tree(bstree* bst) {
    if(bst != NULL && bst->root != NULL) {
        bst_free_subtree(bst->root);
        bst->root = NULL;
    }
}
