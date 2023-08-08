// Phil Pereira Schultz 12.01.2023

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "introprog_input_merge_sort.h"

void merge(int* array, int first, int middle, int last){
  int* array_b = calloc(last - first + 2,  sizeof(int));
  int k = first;
  int m = middle +1;
  int i = 1;
  int j = 1;

  while(k <= middle && m <= last){
    if(array[k] <= array[m]){
      array_b[i] = array[k];
      k++;
    }
    else{
      array_b[i] = array[m];
      m++;
    }
    i++;
  }
  
  while(k <= middle){
    array_b[i] = array[k];
    k++;
    i++;
  }

  while(m <= last){
    array_b[i] = array[m];
    m++;
    i++;
  }

  while(j < i){
    array[first + j -1] = array_b[j];
    j++;
  }
  
  free(array_b);
}

void merge_sort(int* array, int first, int last){
  if(first < last){
    int middle = (first + last) /2;
    merge_sort(array, first, middle);
    merge_sort(array, middle + 1, last);
    merge(array, first, middle, last);
  }
}

int main (int argc, char *argv[]){
  if (argc!=3){
    printf ("usage: %s <maximale anzahl>  <dateipfad>\n", argv[0]);
    exit(2);
  }
    
  char *filename = argv[2];
  int length = atof(argv[1]);   
  int* array = calloc(length, sizeof(int));
    
  int len = read_array_from_file(array, atoi(argv[1]), filename);

  printf("Eingabe:\n");
  print_array(array, len);

  merge_sort(array, 0, len -1);

  printf("Sortiert:\n");
  print_array(array, len);

  free(array);
  return 0;
}
