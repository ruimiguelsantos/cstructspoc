#include "adj_matrix.h"
#include <stdlib.h>

GraphM* initGraphM(GraphM *gm) {
  gm = (GraphM*) malloc(sizeof(GraphM));

  return gm;
}

int inDegM(GraphM *gm, int k) {
  int i, acc = 0;
  for(i=0; i < gm -> v; i++)
    if(gm -> g[i][k] != NOEDGE)
      acc++;

  return acc;
}

int outDegM(GraphM *gm, int k) {
  int i, acc = 0;
  for(i=0; i < gm -> v; i++)
    if(gm -> g[k][i] != NOEDGE)
      acc++;

  return acc;
}