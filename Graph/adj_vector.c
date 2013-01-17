#include "adj_vector.h"
#include <stdlib.h>

GraphV* initGraphV(GraphV *gv) {

  gv = (GraphV*) malloc(sizeof(GraphV));

  return gv;
}

int inDegV(GraphV *gv, int k) {
  int i, acc = 0, edgesEnd = gv -> adjStartIndex[gv -> v];
  for(i=0; i < edgesEnd; i++)
    if(gv->adjNode[i] == k)
      acc++;
   return acc;
}

int outDegV(GraphV *gv, int k) {

  return gv -> adjStartIndex[k+1] - gv -> adjStartIndex[k];
}