#include "closed_addressing.h"

int fhash(char *str, int len, int tableSize) {

  unsigned int b    = 378551;
  unsigned int a    = 63689;
  unsigned int hash = 0;
  unsigned int i    = 0;

  for(i = 0; i < len; str++, i++) {
      hash = hash * a + (*str);
      a    = a * b;
   }

   return hash%tableSize;
}

Hashtable init(Hashtable h, int size) {

  int i = 0;
  h = (Node*) malloc(sizeof(Node)*size);
  while(i<size) {
    h[i] = NULL;
    i++;
  }
  return h;
}

void updateLoadFactor(int used, int total, float *loadFactor) {

  printf("# Used: %d | Total: %d\n# Before -> loadfactor=%f | ",used,total,*loadFactor);
  *loadFactor = used/(float)total;
  printf("After -> loadfactor=%f\n",*loadFactor);

}

Hashtable duplicate(Hashtable h, int *tableSize) {

  int i = 0, old = (*tableSize);
  int new = old*2;
  char auxKey[MAXLENGTH];
  HashEntry auxEntry;

  Hashtable nh = (Node*) malloc(sizeof(Node)*new);
  // initialize new hash table to default values
  while(i<new) {
    nh[i] = NULL;
    i++;
  }
  i = 0;
  // insert all the values from the old hash table into the new
  while(i<old) {
    Node aux = h[i];
    while(aux!=NULL) {
      strncpy(auxKey,aux->key,MAXLENGTH);
      auxEntry = aux->entry;
      insert(nh,auxKey,strlen(auxKey),auxEntry,new);
      aux = aux -> next;
    }
    i++;
  }
  // free all memory space previously allocated to the old hash table
  liberta(h,old);
  
  // update global var with table size and pointer to the table
  h = nh;
  (*tableSize) = new;
  return h;
}

int liberta(Hashtable h, int size) {

  int i = 0;
  Node aux, prev;
  while(i<size) {
    prev = h[i];
    aux = prev;
    while(aux!=NULL) {
      aux = aux->next;
      printf("\nfreeing h[%d]...",i);
      free(prev);
      prev = aux;
    }
    i++;
  }

  return 1;
}

int insert(Hashtable h, char *str, int length, HashEntry e, int tableSize) {

  int index = fhash(str, length, tableSize);

  int i=0;
  Node dup = NULL;
  dup = search(h,str,length,tableSize);
  if(dup==NULL) {
    Node aux;
    aux = (Node) malloc(sizeof(struct node));
    strncpy(aux->key,str,MAXLENGTH);
    aux->entry = e;
    aux->next = h[index];
    h[index] = aux;
    return 1;
  }
  else {   
    printf("[error] Duplicates are not allowed.\n");
    return 0;
  }

}

int rem(Hashtable h, char *str, int length, int tableSize) { // lixo

  int index = fhash(str, length, tableSize);
  int found = 0;
  Node aux = h[index];
  Node prev = aux;
  if(!aux)
    return 0;
  else {
    if(strncmp(aux->key,str,MAXLENGTH)==0) {
      free(aux);
      h[index] = NULL;
      return 1;
    }
    else {
      aux = aux->next;
      while(aux!=NULL && found == 0) {
        if(strncmp(aux->key,str,MAXLENGTH)==0)
         found = 1;
        else {
         aux = aux -> next;
          prev = prev -> next;
        }
      }
      if(found == 1) {
        prev -> next = aux -> next;
        free(aux);

        return 1;
      }
      else
        return 0;
    }
  }
}

Node search(Hashtable h, char *str, int length, int tableSize) {

  int index = fhash(str, length, tableSize);

  int found = 0;
  Node aux = h[index];
  while(aux!=NULL && found == 0) {
    if(strncmp(aux->key,str,MAXLENGTH)==0)
      found = 1;
    else
      aux = aux -> next;
  }
  
  return aux;
}

int alter(Hashtable h, char *str, int length, HashEntry new, int tableSize) {

  Node found = search(h,str,length,tableSize);
  if(found) {
    found->entry = new;
    return 1;
  }
  else
    return 0;
}