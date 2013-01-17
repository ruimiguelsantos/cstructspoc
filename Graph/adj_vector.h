#ifndef _GRAPH_CONST
#include <math.h>
#define NOEDGE -1
#define MAX 20
#define MAXEDGE sqrt(MAX)
#endif

typedef struct {
  int v;
  int adjStartIndex[MAX];
  int adjNode[MAX];
  int weight[MAX];
}GraphV;

GraphV* initGraphV(GraphV*);
int inDegV(GraphV *gv, int k);
int outDegV(GraphV *gv, int k);