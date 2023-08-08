#include <stdlib.h>		
#include <stdio.h>
#include <math.h>
#include "avl.h"

void AVL_in_order_walk_node(AVLNode* node){
    if(node -> left != NULL){
        AVL_in_order_walk_node(node -> left);   // Falls es eine linkes Child gibt wird dieses rekursiv zuerst angesteuert
    }
    printf(" %d", node -> value);
    if(node -> right != NULL){
        AVL_in_order_walk_node(node -> right);   // Falls es eine rechtes Child gibt wird dieses rekursiv angesteuert nachdem das linke Child angesteuert und geprintet wurde
    }
    return;       
}

void AVL_in_order_walk(AVLTree* avlt){
    if(avlt == NULL){                           // Falls node nicht existiert wird die Funktion direkt abgebrochen
        return;
    }
    AVL_in_order_walk_node(avlt -> root);
    printf("\n");
    return;
}

int AVL_node_height(AVLNode* node){
    if(node == NULL){
        return -1;
    }
    else if(node -> left == NULL && node -> right == NULL){
        return 0;
    }
    else if(node -> left == NULL){
        return node -> right -> height + 1;
    }
    else if(node -> right == NULL){
        return node -> left -> height + 1;
    }
    else{
        int lh = node -> left -> height;
        int rh = node -> right -> height;
        
        if(lh > rh){
            return 1 + lh;
        }
        else{
            return 1 + rh;
        }
    }
}

void AVL_rotate_left(AVLTree* avlt, AVLNode* x){
    AVLNode* y = x -> right;
    x -> right = y -> left;
    if (y -> left != NULL) {
        y -> left -> parent = x;
    }
    y -> parent = x -> parent;
    if (x -> parent == NULL) {
        avlt -> root = y;
    }
    else if (x == x -> parent -> left) {
        x -> parent -> left = y;
    }
    else {
        x -> parent -> right = y;
    }
    y -> left = x;
    x -> parent = y;
    
    x -> height = AVL_node_height(x);
    y -> height = AVL_node_height(y);
}

void AVL_rotate_right(AVLTree* avlt, AVLNode* y){
    AVLNode* x = y -> left;
    y -> left = x -> right;
    if (x -> right != NULL) {
        x -> right -> parent = y;
    }
    x -> parent = y -> parent;
    if (y -> parent == NULL) {
        avlt -> root = x;
    }
    else if (y == y -> parent -> right) {
        y -> parent -> right = x;
    }
    else {
        y -> parent -> left = x;
    }
    x -> right = y;
    y -> parent = x;
    
    y -> height = AVL_node_height(y);
    x -> height = AVL_node_height(x);
}

void AVL_balance(AVLTree* avlt, AVLNode* node){
    if(node == NULL){
        return;
    }
    if(AVL_node_height(node -> left) > AVL_node_height(node -> right) + 1){
        if(AVL_node_height(node -> left -> left) < AVL_node_height(node -> left -> right)){
            AVL_rotate_left(avlt, node -> left);
        }
        AVL_rotate_right(avlt, node);
    }
    else if(AVL_node_height(node -> right) > AVL_node_height(node -> left) + 1){
        if(AVL_node_height(node -> right -> right) < AVL_node_height(node -> right -> left)){
            AVL_rotate_right(avlt, node -> right);
        }
        AVL_rotate_left(avlt, node);
    }
}


AVLNode* AVL_create_new_node(int value, AVLNode* parent){
    AVLNode* new_node = malloc(sizeof(AVLNode));
    new_node -> value = value;
    new_node -> left = NULL;
    new_node -> right = NULL;
    new_node -> parent = parent;
    new_node -> height = 0;
    return new_node;
}

void AVL_insert_node(AVLTree* avlt, AVLNode* node, int value){
    if(node == NULL){
        return;
    }
    if(value < node -> value){
        if(node -> left == NULL){
            node -> left = AVL_create_new_node(value, node);
        }
        else{
            AVL_insert_node(avlt, node -> left, value);
        }
    }    
    else if(value > node -> value){
        if(node -> right == NULL){
            node -> right = AVL_create_new_node(value, node);
        }
        else{
            AVL_insert_node(avlt, node -> right, value);
        }
    }
    node -> height = AVL_node_height(node);
    AVL_balance(avlt, node);
}

void AVL_insert_value(AVLTree* avlt, int value){
    avlt -> numberOfNodes++;
    if(avlt -> root == NULL){
        avlt -> root = AVL_create_new_node(value, NULL);
    }
    else{
        AVL_insert_node(avlt, avlt -> root, value);
    } 
}

void AVL_remove_all_elements_node(AVLNode* node){
    if(node == NULL){
        return;
    }
    AVL_remove_all_elements_node(node -> right);
    AVL_remove_all_elements_node(node -> left);                         
    free(node);                            
    return;     
}

void AVL_remove_all_elements(AVLTree* avlt){
    if(avlt == NULL){
        return;
    }
    AVL_remove_all_elements_node(avlt -> root);                       
    return; 
}
