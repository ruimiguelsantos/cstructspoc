#include "minheap.h"

int init(Buffer h) {
  
  h -> n = 0;
  
  return 1;
}

int add(Buffer h, int x) {
  
  if(h -> n == MAX) return 0;

  int i = h -> n;
  int *heap = h->heap; // renamed for readability
  heap[(h -> n)++] = x;

  while(i>0)
    if(heap[pai(i)] > heap[i]) {
      swap(pai(i), i, heap);
      i = pai(i);
    }
    else
      break;

  return 1;
}

int rem(Buffer h, int *x) {

  if(empty(h))
    return 0;

  //int *heap = h -> heap; // renamed for readability
  // save removed min to x
  (*x) = h -> heap[0];
  // put last value (array max) in root
  // and decrease number of elements in heap
  h -> heap[0] = h -> heap[--(h -> n)];
  // start bubble down
  int min, i = 0, N = h -> n;

  while(esq(i) < N) {

    min = esq(i);
    if( dir(i) < N && h -> heap[dir(i)] < h -> heap[min] )
      min = dir(i);
    if(h -> heap[min] < h -> heap[i]) {
      swap(min, i, h -> heap);
      i = min;
    }
    else
      break;
  }

  return 1;
}

int next(Buffer h, int *x) {

  if(empty(h))
    return 0;

  (*x) = h->heap[0];

  return 1;
}

int empty(Buffer h) {

  return (h -> n == 0);
}

// Funcoes auxiliares pai(), esq(), dir() e swap()
int pai(int i) {

  return (i-1)/2;
}

int esq(int i) {

  return 2*i+1;
}

int dir(int i) {

  return 2*i+2;
}

void swap(int a, int b, int h[]) {

  int aux;
  aux = h[a];
  h[a] = h[b];
  h[b] = aux;
}