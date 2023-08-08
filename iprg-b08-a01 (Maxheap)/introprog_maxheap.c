#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "introprog_heap.h"

heap* heap_create(size_t capacity) {
    heap* new_heap = (heap*)malloc(sizeof(heap));
    new_heap -> elements = (int*)malloc(sizeof(int) * capacity);
    new_heap -> capacity = capacity;
    new_heap -> size = 0;
    return new_heap;

}

void heapify(heap* h, size_t i) {
    int L = 2 * i + 1;
    int R = 2 * i + 2;
    int largest;
    if(L < h -> size && h -> elements [L] > h -> elements [i]){
        largest = L;
    } 
    else{
        largest = i;
    }
    if(R < h -> size && h -> elements [R] > h -> elements [largest]){
        largest = R;
    }
    if(largest != i){
        size_t temp = h -> elements[largest];
        h -> elements[largest] = h -> elements[i];
        h -> elements[i] = temp;
        heapify(h, largest);
    }
}

int heap_extract_max(heap* h) {
    if(h -> size == 0){
        return -1;
    }
    int MAX = h -> elements[0];
    h -> elements[0] = h -> elements[h -> size - 1];
    h -> size = h -> size -1;
    heapify(h, 0);
    return MAX;
}

int heap_insert(heap* h, int key) {
    size_t i = h -> size;
    if(h -> size == h -> capacity ){
        return -1;
    }
    h -> size = h -> size + 1;
    while( i > 0 && h -> elements[(i+1) / 2 -1] < key){
        h -> elements[i] = h -> elements[(i+1) / 2 -1];
        i = (i+1) / 2 -1;
    }
    h -> elements[i] = key;
    return key;
}

void heap_free(heap* h) {
    free(h -> elements);
    free(h);
}
