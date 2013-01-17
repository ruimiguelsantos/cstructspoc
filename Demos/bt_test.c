#include "../Btree/btree.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void bst_print_dot_null(int value, int nullcount, FILE* stream) {

    fprintf(stream, "    null%d [shape=point];\n", nullcount);
    fprintf(stream, "    %d -> null%d;\n", value, nullcount);
}

void bst_print_dot_aux(Btree node, FILE* stream) {

    static int nullcount = 0;

    if (node->left) {
        fprintf(stream, "    %d -> %d;\n", node->value, node->left->value);
        bst_print_dot_aux(node->left, stream);
    }
    else
        bst_print_dot_null(node->value, nullcount++, stream);

    if (node->right) {
        fprintf(stream, "    %d -> %d;\n", node->value, node->right->value);
        bst_print_dot_aux(node->right, stream);
    }
    else
        bst_print_dot_null(node->value, nullcount++, stream);
}

void bst_print_dot(Btree tree, FILE* stream) {
    fprintf(stream, "digraph BST {\n");
    fprintf(stream, "    node [fontname=\"Arial\"];\n");

    if (!tree)
        fprintf(stream, "\n");
    else if (!tree->right && !tree->left)
        fprintf(stream, "    %d;\n", tree->value);
    else
        bst_print_dot_aux(tree, stream);

    fprintf(stream, "}\n");
}

int main(){

  Btree t = (Btree) malloc(sizeof(Node));

  t = init(t);
  int r=0,fill,resposta;
  while(r!=1){
    char input[1024];
    printf("\naction (he for help)$ ");
    fgets(input, sizeof(input), stdin);
    input[strlen(input)-1] = '\0';
    if(strcmp(input,"pr") == 0) {
      if(t) {
        FILE* fp;
        int close;
        fp = fopen("tree.dot","w");
        if(fp)
          bst_print_dot(t,fp);
        close = fclose(fp);
        if(close==0) {
          printf("Dot file prepared.\n");
          int sys;
          sys = system("dot -Tpng tree.dot -o tree.png");
          if(sys!=-1 && sys!=127) {
            system("open tree.png");
            printf("Dot file successfully opened. ");
          }
          else
            printf("Error opening file. ");
        }
        else
          printf("An error ocurred while creating the dot file. ");
      }
      else
        printf("Tree is empty. ");
      printf("<ENTER>");
      getchar();
    }
    else if(strcmp(input,"op") == 0) {
      
    }
    else if(strcmp(input,"in") == 0) {
      int num, scanres;
      char tempInput[50], enter;
      printf("Number to insert: ");
      fgets(tempInput,sizeof(tempInput), stdin);
      scanres = sscanf(tempInput,"%d%c",&num,&enter);
      if(!(scanres == 2 && enter == '\n'))
        printf("Not a number. ");
      else {
        resposta=search(t,num);
        if(!resposta) {
          t=add(t,num);
          printf("Inserted %d. ",num);
        }
        else
          printf("%d is already in tree (no duplicates are allowed). ",num);
      }
      printf("<ENTER>");
      getchar();
    }
    else if(strcmp(input,"ht") == 0) {
      int res;
      res = height(t);
      printf("Tree height: %d <ENTER>",res);
      getchar();
    }
    else if(strcmp(input,"si") == 0) {
      int sz = size(t);
      printf("Size: %d element(s) in the tree. <ENTER>", sz);
      getchar();
    }
    else if(strcmp(input,"ma") == 0) {
      if(!t)
        printf("Tree has no elements. <ENTER>");
      else {
        int m = max(t);
        printf("Max in tree: %d. <ENTER>", m);
      }
      getchar();
    }
    else if(strcmp(input,"ba") == 0) {
      int bl = balanced(t);
      if(bl)
        printf("Tree is balanced. <ENTER>");
      else
        printf("Tree is not balanced. <ENTER>");
      getchar();
    }
    else if(strcmp(input,"se") == 0) {
      int num, scanres;
      char tempInput[50], enter;
      printf("Number to search: ");
      fgets(tempInput,sizeof(tempInput), stdin);
      scanres = sscanf(tempInput,"%d%c",&num,&enter);
      if(!(scanres == 2 && enter == '\n'))
        printf("Not a number. ");
      else {
        resposta=search(t,num);
        if(resposta)
          printf("%d was found. ",num);
        else
          printf("%d was not found. ",num);
      }
      printf("<ENTER>");
      getchar();
    }
    else if(strcmp(input,"he") == 0) {
      printf("\n# available actions:\n");
      printf("# pr - print current tree.\n");
      printf("# in - insert in tree;\n");
      printf("# ht - get tree height;\n");
      printf("# si - get tree size (number of elements);\n");
      printf("# ma - get max number in tree.\n");
      printf("# ba - check if tree is balanced.\n");
      printf("# se - search number in tree.\n");
      printf("# he - print this helper.\n");
      printf("# ex - exit.\n\n<ENTER>");
      getchar();
    }
    else if(strcmp(input,"ex") == 0) {
      r = 1;
      printf("Leaving... <ENTER>");
      getchar();
    }
    else {
      printf("\nNot an action. Type he for available actions. <ENTER>");
      getchar();
    }
  }
  printf("Done.\n");

  return 1;
}