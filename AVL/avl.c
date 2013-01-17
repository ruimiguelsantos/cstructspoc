#include "avl.h"
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>

Tree createTree(void) {

  return NULL;
}

void emptyTree(Tree t) {

  if(!t)
    return;
  emptyTree(t->left);
  emptyTree(t->right);
  free(t);
}

void liberta(Tree t) {

  if(t)
    free(t);
}

void emptyTree2(Tree t) {

  postorder(t, liberta);
}

int treeHeight(Tree t) {

  if(!t)
    return 0;

  return( 1 + maximum(treeHeight(t->left), treeHeight(t->right)) );
}

int maximum(int a, int b) {

  return (a >= b) ? a : b;
}

int treeSize(Tree t) {

  if(!t)
    return 0;

  return( treeSize(t->left) + treeSize(t->right) + 1 );
}

int isEmpty(Tree t) {

  return(t==NULL);
}

void preorder(Tree t, Func f) {

  if(!t)
    return;
  f(t);
  preorder(t->left,f);
  preorder(t->right,f);
}

void inorder(Tree t, Func f) {

  if(!t)
    return;
  inorder(t->left,f);
  f(t);
  inorder(t->right,f);
}

void postorder(Tree t, Func f) {

  if(!t)
    return;
  postorder(t->left,f);
  postorder(t->right,f);
  f(t);
}

Tree searchTree(Tree t, TreeEntry e) {

  if(t) {
    if(e == t->entry)
      return t;
    else if(e < t->entry)
      return searchTree(t->left,e);
    else
      return searchTree(t->right,e);
  }
  else
    return NULL;
}


int isLeaf(Tree t) {
  
  if(!t)
    return 0;
  else if(t->left==NULL && t->right==NULL)
    return 1;
  else
    return 0;
}

int has1child(Tree t) {

  if(!t)
    return 0;
  if( (t->left==NULL && t->right!=NULL) || (t->left!=NULL && t->right==NULL) )
    return 1;
  else
    return 0;
}

Tree minEntry(Tree t) {

  if(!t)
    return NULL;
  if(t->left)
    return minEntry(t->left);
  else
    return t;
}

Tree freeMinFromTree(Tree t, TreeEntry e) {

  Tree aux;
  if(e == t->entry) {
    if(has1child(t)) { // if t has 1 child, it has to be a right subtree
      aux = t;
      t = t->right;
      free(aux);
    }
    else { // if the min is a leaf
      aux = t;
      t = NULL;
      free(aux);
    }
  }
  else
    t->left = freeMinFromTree(t->left, e);

  return t;
}

Tree deleteTree(Tree t, TreeEntry e, int *diminuiu) {
  // Node with entry e is supposed to exist. Before deleteTree, call searchTree.
  Tree aux, min;
  // step 1 - remove node with entry e
  if(e == t->entry) {
    if(isLeaf(t)) { // if node with entry e is a leaf, just (physically) remove it
      aux = t;
      t = NULL;
      free(aux);
      *diminuiu = 1;
    }
    else if(has1child(t)) {
      switch(t->bf) { // if node with entry e has only 1 child, check balance factor
        case LH: // overwrite node entry with left child entry and remove left child
          aux = t->left;
          t->entry = aux->entry;
          t->left = NULL;
          free(aux);
          break;
        case RH: // set node entry to right child entry and remove right child
          aux = t->right;
          t->entry = aux->entry;
          t->right = NULL;
          free(aux);
          break;
      }
      *diminuiu = 1;
    }
    else { // if node with entry e has both subtrees
      aux = minEntry(t->right);
      t->entry = aux->entry; // overwrite t's entry with the smallest entry in the right subtree
      t->right = deleteTree(t->right,aux->entry,diminuiu);
    }
  }
  else if(e < t->entry)
    t = deleteLeft(t, e, diminuiu);
  else
    t = deleteRight(t, e, diminuiu);

  // step 2 - rebalance the tree (if necessary)


  return t;
}

Tree deleteRight(Tree t, TreeEntry e, int *diminuiu) {

  t -> right = deleteTree(t->right, e, diminuiu);

  if(*diminuiu) {
    switch(t->bf) {
      case RH:
        t -> bf = EH;
        *diminuiu = 1;
        break;
      case EH:
        t -> bf =  LH;
        *diminuiu = 0;
        break;
      case LH:
        printf("[bL]\n");
        t = balanceLeft(t);
        *diminuiu = 1;
    }
  }

  return t;
}

Tree deleteLeft(Tree t, TreeEntry e, int *diminuiu) {

  t -> left = deleteTree(t -> left, e, diminuiu);

  if(*diminuiu) {
    switch(t->bf) {
      case LH:
        t -> bf = EH;
        *diminuiu = 1;
        break;
      case EH:
        t -> bf = RH;
        *diminuiu = 0;
        break;
      case RH:
        printf("[bR]\n");
        t = balanceRight(t);
        *diminuiu = 1;
    }
  }

  return t;
}

Tree insertTree(Tree t, TreeEntry e, int *cresceu) {

  if(!t) {
    t = (Tree) malloc(sizeof(struct treenode));
    t -> entry = e;
    t -> left = NULL;
    t -> right = NULL;
    t -> bf = EH;
    *cresceu = 1;
  }
  else if(e == t->entry)
    printf("\n[error] %d already in tree.\n",e);
  else if(e > t->entry)
    t = insertRight(t, e, cresceu);
  else
    t = insertLeft(t, e, cresceu);

  return(t);
}

Tree insertRight(Tree t, TreeEntry e, int *cresceu) {

  t -> right = insertTree(t -> right, e, cresceu);

  if(*cresceu) {
    switch(t->bf) {
      case LH:
        t -> bf = EH;
        *cresceu = 0;
        break;
      case EH:
        t -> bf = RH;
        *cresceu = 1;
        break;
      case RH:
        t = balanceRight(t);
        *cresceu = 0;
    }
  }

  return t;
}

Tree balanceRight(Tree t) {

  if(t -> right -> bf == RH) {
    // simple (rotate left)
    t = rotateLeft(t);
    t -> bf = EH;
    t -> left -> bf = EH;
  }
  else {
    // double (rotate right and then left)
    t -> right = rotateRight(t -> right);
    t = rotateLeft(t);
    switch(t -> bf) {
      case EH:
        t -> left -> bf = EH;
        t -> right -> bf = EH;
        break;
      case LH:
        t -> left -> bf = EH;
        t -> right -> bf = RH;
        break;
      case RH:
        t -> left -> bf = LH;
        t -> right -> bf = EH;
    }
    t -> bf = EH;
  }

  return t;
}

Tree insertLeft(Tree t, TreeEntry e, int *cresceu) {

  t -> left = insertTree(t -> left, e, cresceu);

  if(*cresceu) {
    switch(t -> bf) {
      case RH:
        t -> bf = EH;
        *cresceu = 0;
        break;
      case EH:
        t -> bf = LH;
        *cresceu = 1;
        break;
      case LH:
        t = balanceLeft(t);
        *cresceu = 0;
    }
  }

  return t;
}

Tree balanceLeft(Tree t) {

  if(t -> left -> bf == LH) {
    // simple (rotate right)
    t = rotateRight(t);
    t -> bf = EH;
    t -> right -> bf = EH;
  }
  else {
    // double (rotate left and then right)
    t -> left = rotateLeft(t -> left);
    t = rotateRight(t);
    switch(t->bf) {
      case EH:
        t -> left -> bf = EH;
        t -> right -> bf = EH;
        break;
      case RH:
        t -> left -> bf = LH;
        t -> right -> bf = EH;
        break;
      case LH:
        t -> left -> bf = EH;
        t -> right -> bf = RH;
    }
    t -> bf = EH;
  }

  return t;
}

Tree rotateRight(Tree t) {

  Tree aux;
  if(!t || !(t->left))
    printf("\n[error] Can't rotate right.\n");
  else {
    aux = t -> left;
    t -> left = aux -> right;
    aux -> right = t;
    t = aux;
  }

  return t;
}

Tree rotateLeft(Tree t) {

  Tree aux;
  if(!t || !(t->right))
    printf("\n[error] Can't rotate left.\n");
  else {
    aux = t -> right;
    t -> right = aux -> left;
    aux -> left = t;
    t = aux;
  }

  return t;
}