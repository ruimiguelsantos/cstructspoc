#include "open_addressing.h"

Hashtable init(Hashtable h, int size) {

  int i = 0;
  h = (Node*) malloc(sizeof(Node)*size);
  while(i<size) {
    h[i] = (Node) malloc(sizeof(struct node));
    //printf("malloc'ed h[%d]..\n",i);
    strncpy(h[i]->key,"EMPTY",strlen("EMPTY"));
    h[i]->entry = -1;
    i++;
  }
  return h;
}

Hashtable duplicate(Hashtable h, int *tableSize) {

  int i = 0, old = (*tableSize);
  int new = old*2;
  char auxKey[MAXLENGTH];
  HashEntry auxEntry;

  Hashtable nh = (Node*) malloc(sizeof(Node)*new);
  // initialize new hash table to default values
  while(i<new) {
    nh[i] = (Node) malloc(sizeof(struct node));
    strncpy(nh[i]->key,"EMPTY",strlen("EMPTY"));
    nh[i]->entry = -1;
    i++;
  }
  i = 0;
  // insert all the values from the old hash table into the new
  while(i<old) {
    strncpy(auxKey,h[i]->key,MAXLENGTH);
    auxEntry = h[i]->entry;
    insert(nh,auxKey,strlen(auxKey),auxEntry,new);
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
  while(i<size) {
    //printf("\nfreeing h[%d]...",i);
    free(h[i++]);
  }

  return 1;
}

void updateLoadFactor(int used, int total, float *loadFactor) {

  printf("# Used: %d | Total: %d\n# Before -> loadfactor=%f | ",used,total,*loadFactor);
  *loadFactor = used/(float)total;
  printf("After -> loadfactor=%f\n",*loadFactor);

}

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

// if EMPTY key is inserted, function has undefined behaviour
// (probing gets messed up and keys in the hash table might not get found
// when using search() function) -----> Note: take defensive action in presentation layer
int insert(Hashtable h, char *str, int length, HashEntry e, int tableSize) {

  int index = fhash(str, length, tableSize);

  int i=0;
  Node dup = NULL;
  int newindex = (index)%tableSize;
  dup = search(h,str,length,tableSize);
  if(dup==NULL) {
    while(strcmp(h[newindex]->key,"EMPTY")!=0 && strcmp(h[newindex]->key,"REMOVED")!=0 && i < tableSize) {
      i++;
      newindex = (index + i*i)%tableSize;
    }
    if(i < tableSize-1) {
      strncpy(h[newindex]->key,str,MAXLENGTH);
      h[newindex]->entry = e;

      return 1;
    }
    else {
      printf("[error] All slots are full for the requested key.\n");
      return 0;
    }
  }
  else {
    printf("[error] Duplicates are not allowed.\n");
    return 0;
  }

}

int rem(Hashtable h, char *str, int length, int tableSize) {

  int index = fhash(str, length, tableSize);
  int i = 0;
  int newindex = (index)%tableSize;
  while(strncmp(h[newindex]->key,str,MAXLENGTH)!=0 && i < tableSize) {
    i++;
    newindex = (index + i*i)%tableSize;
  }
  if(i < tableSize) {
    strncpy(h[newindex]->key,"REMOVED",MAXLENGTH);
    h[newindex]->entry = -1;

    return 1;
  }
  else {
    printf("[error] Key '%s' was not found.\n",str);

    return 0;
  }
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

// if key is found, returns corresponding value
// otherwise returns -1
Node search(Hashtable h, char *str, int length, int tableSize) {

  int index = fhash(str, length, tableSize);

  int i=0, found = 0;
  int newindex = (index)%tableSize;
  while(strcmp(h[newindex]->key,"EMPTY")!=0 && i < tableSize && found == 0) {
    if(strncmp(h[newindex]->key,str,MAXLENGTH)==0)
      found = 1;
    else {
      i++;
      newindex = (index + i*i)%tableSize;
    }
  }
  if(i < tableSize && found == 1)
      return h[newindex];
  else {
    //printf("[error] '%s' is not in the hash table.\n",str);
    return NULL;
  }
}








