/******************************************
 * hash table com closed addressing       *
 * e separate chaining com listas ligadas *
 ******************************************/

#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAXLENGTH 50

typedef long int HashEntry;

typedef struct node {
  char key[MAXLENGTH];
  HashEntry entry;
  struct node *next;
}*Node;

typedef Node *Hashtable;

int fhash(char*, int, int);
Hashtable init(Hashtable, int);
int insert(Hashtable h, char *str, int length, HashEntry e, int tableSize);
int rem(Hashtable, char *str, int length, int tableSize);
int alter(Hashtable, char *str, int length, HashEntry new, int tableSize);
Node search(Hashtable h, char *str, int length, int tableSize);
Hashtable duplicate(Hashtable, int*);
int liberta(Hashtable, int);
void updateLoadFactor(int used, int total, float *loadFactor);