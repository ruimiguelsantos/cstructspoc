#include "btree.h"
#include <stddef.h>
#include <stdlib.h>


Btree init(Btree t) {

  t = NULL;

  return t;
}

int size(Btree t) {

  return t ? 1 + size(t->left) + size(t->right) : 0;
}

int height(Btree t) {

  if(!t)
    return 0;
  
  return 1 + maximum(height(t->left), height(t->right));
}

int maximum(int a, int b) {

  return (a >= b) ? a : b;
}

int balanced(Btree t) {

  if(t) {
    int l = height(t->left);
    int r = height(t->right);
    return ((abs(l-r) <= 1) && balanced(t->left) && balanced(t->right));
  }
  else
    return 1;
}

Btree add(Btree t, int x) {
/*
  if(!t) {
    Btree new = (Btree) malloc(sizeof(Node));
    new -> value = x;
    new -> left = new -> right = NULL;
  }
  if(x <= t->value)
    t -> left = add(t -> left, x);
  else
    t -> right = add(t -> right, x);

  return t;
*/
  if(!t) {
    Btree new = (Btree) malloc(sizeof(Node));
    new -> value = x;
    new -> left = new -> right = NULL;

    t = new;
  }
  if(x < t -> value)
    t -> left = add(t -> left, x);
  if(x > t -> value)
    t -> right = add(t -> right, x);
  return t;
}

int search(Btree t, int x) {

  if(!t)
    return 0;
  
  if(x == t -> value)
    return 1;
  
  if(x < t -> value)
    return search(t -> left, x);
  
  return search(t -> right, x);
}

int max(Btree t) {

  if( !(t -> right) )
    return t -> value;

  return max(t -> right);
}