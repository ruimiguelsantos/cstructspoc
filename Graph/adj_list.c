#include "adj_list.h"
#include <stdlib.h>
#include <stdio.h>

GraphL* initGraphL(GraphL *gl) {
  gl = (GraphL*) malloc(sizeof(GraphL));

  return gl;
}

int inDegL(GraphL *gl, int k) {
  int i, acc = 0;
  Node *p;
  for(i=0; i < gl -> v; i++) {
    p = gl -> g[i];
    while(p) {
      if(p -> dest == k) {
        acc++;
        break; // optimization for simple graphs (doesn't work for multigraphs)
      }
      p = p -> next;
    }
  }

  return acc;
}

int* inDegLall(GraphL *gl) {
  
  int *inDegArray = (int*) malloc(sizeof(int)*gl->v);
  int i,j;
  for(j=0; j < gl -> v; j++)
    inDegArray[j] = 0;
  Node *p;
  for(i=0; i < gl -> v; i++) {
    p = gl -> g[i];
    while(p) {
      inDegArray[p->dest]++;
      p = p -> next;
    }
  }

  return inDegArray;
}

int outDegL(GraphL *gl, int k) {
  int acc = 0;
  Node *p = gl -> g[k];
  while(p) {
    acc++;
    p = p -> next;
  }

  return acc;
}

int* outDegLall(GraphL *gl) {

  int *outDegArray = (int*) malloc(sizeof(int)*gl->v);
  int i;
  Node *p;
  for(i=0; i < gl -> v; i++)
    outDegArray[i] = 0;
  for(i=0; i < gl -> v; i++) {
    p = gl -> g[i];
    while(p) {
      outDegArray[i]++;
      p = p -> next;
    }
  }

  return outDegArray;
}

/***************************************
 * Topological Sorting (Breadth-first) *
 *      (acyclic directed graphs)      *
 ***************************************/
void topSortBL(GraphL *gl, int ot[]) {

  Node *p;
  int *ant = inDegLall(gl);
  Buffer q = (Buffer) malloc(sizeof(struct buffer));
  init(q);
  int i, dequeued, next = 0;
  for(i=0; i < gl -> v; i++)
    if(ant[i]==0)
      add(q,i);
  while(!empty(q)) {
    rem(q,&dequeued);
    ot[next++] = dequeued;
    p = gl->g[dequeued];
    while(p) {
      ant[p->dest]--;
      if(ant[p->dest] == 0)
        add(q,p->dest);
      p = p -> next;
    }
  }
}

/*************************************
 * Topological Sorting (Depth-first) *
 *     (acyclic directed graphs)     *
 *************************************/
void topSortDL(GraphL *gl, int ot[]) {

  int *visitado = (int*) malloc(sizeof(int)*gl->v);
  int i, next = (gl -> v) - 1;

  for(i = 0; i < gl -> v; i++)
    visitado[i] = 0;
  for(i = 0; i < gl -> v; i++)
    if(!visitado[i]) {
      //printf("starting dfsL (gl, ot, %d, visitado, %d (next))..\n",i,next);
      dfsL(gl, ot, i, visitado, &next);
    }
}

void dfsL(GraphL *gl, int ot[], int i, int visitado[], int *next) {

  Node *p = gl -> g[i];
  visitado[i] = 1;

  while(p) {
    if(!visitado[p->dest])
      dfsL(gl, ot, p->dest, visitado, next);
    p = p -> next;
  }
  ot[(*next)--] = i;
  //printf("ot[%d] = %d, next=%d\n",(*next)+1,i,*next);
}






