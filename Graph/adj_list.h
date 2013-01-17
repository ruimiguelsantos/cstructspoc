#ifndef _GRAPH_CONST
#define NOEDGE -1
#define MAX 20
#endif
#include "../Queue/queue_stat.h"

typedef enum Color { WHITE , GRAY , BLACK } Color;

typedef struct node {
  int w;
  int dest;
  struct node *next;
}Node;

typedef struct {
  int v;
  Node *g[MAX];
}GraphL;

GraphL* initGraphL(GraphL*);
int inDegL(GraphL *gl, int k);
int outDegL(GraphL *gl, int k);
int* inDegLall(GraphL *gl);
int* outDegLall(GraphL *gl);
void topSortBL(GraphL *gl, int ot[]);
void topSortDL(GraphL *gl, int ot[]);
void dfsL(GraphL *gl, int ot[], int i, int visitado[], int *next);