#include "../Graph/adj_list.h"
#include "../Graph/adj_matrix.h"
#include "../Graph/adj_vector.h"
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>

/*********************
 *    Conversions    *
 *********************/
void graphL2M(GraphL *gl, GraphM *gm);
void graphM2L(GraphM *gm, GraphL *gl);
void graphL2V(GraphL *gl, GraphV *gv);
void graphV2L(GraphV *gv, GraphL *gl);
void graphM2V(GraphM *gm, GraphV *gv);
void graphV2M(GraphV *gv, GraphM *gm);


void graphL2M(GraphL *gl, GraphM *gm) {

  int i,j;
  for(i=0; i < gl->v; i++)
    for(j=0; j < gl->v; j++)
      gm -> g[i][j] = NOEDGE;
  Node *p;
  for(i=0; i < gl->v; i++) {
    p = gl -> g[i];
    while(p) {
      gm -> g[i][p->dest] = p -> w;
      p = p -> next;
    }
  }
  gm -> v = gl -> v;
}

void graphM2L(GraphM *gm, GraphL *gl) {

  int i, j;
  for(i=0; i < gm -> v; i++)
    gl -> g[i] = NULL;
  for(i=0; i < gm -> v; i++)
    for(j=0; j < gm -> v; j++)
      if(gm -> g[i][j] != NOEDGE) {
        Node *new = (Node*) malloc(sizeof(Node));
        new -> w = gm -> g[i][j];
        new -> dest = j;
        new -> next = gl -> g[i];
        gl -> g[i] = new;
      }
  gl -> v = gm -> v;
}

void graphL2V(GraphL *gl, GraphV *gv) {

  int i, edges = 0;
  Node *p;
  for(i=0; i < gl -> v; i++) {
    p = gl -> g[i];
    gv -> adjStartIndex[i] = edges;
    while(p) {
      gv -> adjNode[edges] = p -> dest;
      gv -> weight[edges] = p -> w;
      edges++;
      p = p -> next;
    }
  }
  gv -> v = gl -> v;
}

void graphV2L(GraphV *gv, GraphL *gl) {

  int i, j, outDeg, edges = 0;
  for(i=0; i < (gv -> v); i++) {
    outDeg = gv -> adjStartIndex[i+1] - gv -> adjStartIndex[i];
    for(j=0; j < outDeg; j++) {
      Node *new = (Node*) malloc(sizeof(Node));
      new -> w = gv -> weight[edges];
      new -> dest = gv -> adjNode[edges];
      new -> next = gl -> g[i];
      gl -> g[i] = new;
      edges++;
    }
  }/*
  outDeg = gv -> adjStartIndex[i] - gv -> adjStartIndex[i-1];
  for(j=0; j < outDeg; j++) {
    Node *new = (Node*) malloc(sizeof(Node));
    new -> w = gv -> weight[edges];
    new -> dest = gv -> adjNode[edges];
    new -> next = gl -> g[i];
    gl -> g[i] = new;
    edges++;
  }*/
  gl -> v = gv -> v;
}

void graphM2V(GraphM *gm, GraphV *gv) {
  // possible, but very inefficient:
  // Graph *gl = initGraphL(gl);
  // graphM2L(gm,gl);
  // graphL2V(gm,gv);

  int i, j, edges = 0;
  for(i=0; i < gm -> v; i++) {
    gv -> adjStartIndex[i] = edges;
    for(j=0; j < gm -> v; j++)
      if(gm -> g[i][j] != NOEDGE) {
        gv -> adjNode[edges] = j;
        gv -> weight[edges] = gm->g[i][j];
        edges++;
      }
  }
  gv -> v = gm -> v;
}

void graphV2M(GraphV *gv, GraphM *gm) {

  int i, j, edges = 0, outDeg;
  for(i=0; i < gv -> v; i++)
    for(j=0; j < gv -> v; j++)
      gm -> g[i][j] = NOEDGE;
  for(i=0; i < (gv -> v); i++) {
    outDeg = gv -> adjStartIndex[i+1] - gv -> adjStartIndex[i];
    for(j=0; j < outDeg; j++) {
      gm -> g[i][gv -> adjNode[edges]] = gv -> weight[edges];
      edges++;
    }
  }/*
  outDeg = gv -> adjStartIndex[i] - gv -> adjStartIndex[i-1];
  for(j=0; j < outDeg; j++) {
    gm -> g[i][gv -> adjNode[edges]] = gv -> weight[edges];
    edges++;
  }*/
  gm -> v = gv -> v;
}

void printGraphL(GraphL *gl) {
  printf("\nStatus:\n");
  printf("--\n");
  int i=0;
  GraphL *aux = gl;
  Node *auxNode;
  while(i < gl->v) {
    auxNode = aux->g[i];
    printf("%d # ",i);
    while(auxNode!=NULL) {
      printf("(dest %d,w %d) --> ",auxNode->dest,auxNode->w);
      auxNode = auxNode -> next;
    }
    printf("NULL\n");
    i++;
  }
  printf("--\n");
}

void printDegs(int *degs, int total) {
  int i = 0;
  printf("i | Deg\n");
  while(i < total) {
    printf("%d |- %d\n",i,degs[i]);
    i++;
  }
  printf("--\n");
}

int main() {
  GraphL *gl = initGraphL(gl);

  GraphM *gm = initGraphM(gm);
  gm -> v = 6;
  int i, j;
  for(i=0; i < gm -> v; i++)
    for(j=0; j < gm -> v; j++)
      gm -> g[i][j] = NOEDGE;
  
  /*
  gm->g[0][1] = 2;
  gm->g[0][2] = 1;
  gm->g[1][2] = 3;
  gm->g[1][5] = 5;
  gm->g[2][3] = 1;
  gm->g[3][1] = 4;
  gm->g[4][1] = 4;
  gm->g[4][3] = 2;
  gm->g[4][5] = 2;
  */
  gm->g[0][1] = 2;
  gm->g[0][2] = 1;
  gm->g[1][3] = 3;
  gm->g[2][3] = 1;
  gm->g[2][5] = 1;
  gm->g[4][1] = 4;

  GraphV *gv = initGraphV(gv);
  //graphM2L(gm,gl);
  gv -> v = 6;
  gv -> adjStartIndex[0] = 0;
  gv -> adjStartIndex[1] = 2;
  gv -> adjStartIndex[2] = 4;
  gv -> adjStartIndex[3] = 5;
  gv -> adjStartIndex[4] = 6;
  gv -> adjStartIndex[5] = 9;
  gv -> adjStartIndex[6] = 9;
  gv -> adjNode[0] = 1;
  gv -> adjNode[1] = 2;
  gv -> adjNode[2] = 2;
  gv -> adjNode[3] = 5;
  gv -> adjNode[4] = 3;
  gv -> adjNode[5] = 1;
  gv -> adjNode[6] = 1;
  gv -> adjNode[7] = 3;
  gv -> adjNode[8] = 5;
  gv -> weight[0] = 2;
  gv -> weight[1] = 1;
  gv -> weight[2] = 3;
  gv -> weight[3] = 5;
  gv -> weight[4] = 1;
  gv -> weight[5] = 4;
  gv -> weight[6] = 3;
  gv -> weight[7] = 1;
  gv -> weight[8] = 2;

  //graphV2L(gv,gl);
  GraphM *gm2 = initGraphM(gm2);
  GraphL *gl2 = initGraphL(gl2);
  GraphV *gv2 = initGraphV(gv2);
  //graphL2M(gl,gm2);
  //graphM2V(gm,gv2);
  //graphL2V(gl,gv2);
  //graphV2L(gv2,gl2);
  //graphV2L(gv2,gl2);
  //graphV2M(gv,gm2);
  graphM2L(gm,gl2);
  printGraphL(gl2);
  //printf("(3)'s In Degree: %d\n",inDegV(gv,3));
  //printf("(0)'s Out Degree: %d\n",outDegV(gv,0));
  //printf("(3)'s In Degree: %d\n",inDegM(gm2,3));
  //printf("(0)'s Out Degree: %d\n",outDegM(gm2,0));
  int *indegs = inDegLall(gl2);
  printDegs(indegs,gl2->v);
  int *outdegs = outDegLall(gl2);
  printDegs(outdegs,gl2->v);
  int ot[gl2->v];
  //topSortBL(gl2,ot);
  topSortDL(gl2,ot);
  int h;
  for(h=0;h<gl2->v;h++)
    printf("ot[%d]: %d | ",h,ot[h]);
  printf("\n");
  //printf("(0)'s Out Degree: %d\n",outDegL(gl2,0));
  
  return 1;
}
