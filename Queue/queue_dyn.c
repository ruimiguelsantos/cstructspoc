#include "queue_dyn.h"

void init(Buffer b) {

  b -> first = NULL;
  b -> last = NULL;
  b -> n = 0;
}

int empty(Buffer b) {

  return (b -> n == 0);
}

int add(Buffer b, int x) {

  struct node *new;

  if( !(new = malloc(sizeof(struct node))) || (b -> n == MAX) )
    return 0;

  new -> info = x;
  new -> next = NULL;

  if(b -> n==0) {
    b -> first = new;
    b -> last = new;
  }
  else {
    b -> last -> next = new;
    b -> last = new;
  }

  (b -> n)++;
  
  return 1;
}

int next(Buffer b, int *x) {

  if(empty(b))
    return 0;

  (*x) = b -> first -> info;

  return 1;
}

int rem(Buffer b, int *x) {

  if(!next(b,x))
    return 0;

  (b -> n)--;

  struct node *aux;
  aux = b -> first;
  b -> first = aux -> next;
  free(aux);

  return 1;
}