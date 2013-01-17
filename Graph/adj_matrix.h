#ifndef _GRAPH_CONST
#define NOEDGE -1
#define MAX 20
#endif

typedef struct {
  int v;
  int g[MAX][MAX];
}GraphM;

GraphM* initGraphM(GraphM*);
int inDegM(GraphM *gm, int k);
int outDegM(GraphM *gm, int k);