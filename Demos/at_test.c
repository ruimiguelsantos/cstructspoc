#include "../AVL/avl.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void bst_print_dot_null(int entry, int nullcount, FILE* stream) {

    fprintf(stream, "    null%d [shape=point];\n", nullcount);
    fprintf(stream, "    %d -> null%d;\n", entry, nullcount);
}

void bst_print_dot_aux(Tree node, FILE* stream) {

    static int nullcount = 0;

    if (node->left) {
        fprintf(stream, "    %d -> %d;\n", node->entry, node->left->entry);
        bst_print_dot_aux(node->left, stream);
    }
    else
        bst_print_dot_null(node->entry, nullcount++, stream);

    if (node->right) {
        fprintf(stream, "    %d -> %d;\n", node->entry, node->right->entry);
        bst_print_dot_aux(node->right, stream);
    }
    else
        bst_print_dot_null(node->entry, nullcount++, stream);
}

void bst_print_dot(Tree tree, FILE* stream) {
    fprintf(stream, "digraph BST {\n");
    fprintf(stream, "    node [fontname=\"Arial\"];\n");

    if (!tree)
        fprintf(stream, "\n");
    else if (!tree->right && !tree->left)
        fprintf(stream, "    %d;\n", tree->entry);
    else
        bst_print_dot_aux(tree, stream);

    fprintf(stream, "}\n");
}

int main(){

  Tree t = createTree();
  int cresceu, diminuiu;

  int r=0;
  Tree resposta;
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
    else if(strcmp(input,"in") == 0) {
      int num, scanres;
      char tempInput[50], enter;
      printf("Number to insert: ");
      fgets(tempInput,sizeof(tempInput), stdin);
      scanres = sscanf(tempInput,"%d%c",&num,&enter);
      if(!(scanres == 2 && enter == '\n'))
        printf("Not a number. ");
      else {
        resposta=searchTree(t,num);
        if(!resposta) {
          t=insertTree(t,num,&cresceu);
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
      res = treeHeight(t);
      printf("Tree height: %d <ENTER>",res);
      getchar();
    }
    else if(strcmp(input,"si") == 0) {
      int sz = treeSize(t);
      printf("Size: %d element(s) in the tree. <ENTER>", sz);
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
        resposta=searchTree(t,num);
        if(resposta!=NULL)
          printf("%d was found. ",num);
        else
          printf("%d was not found. ",num);
      }
      printf("<ENTER>");
      getchar();
    }
    else if(strcmp(input,"bf") == 0) {
      int num, scanres;
      char tempInput[50], enter;
      printf("Number to search: ");
      fgets(tempInput,sizeof(tempInput), stdin);
      scanres = sscanf(tempInput,"%d%c",&num,&enter);
      if(!(scanres == 2 && enter == '\n'))
        printf("Not a number. ");
      else {
        resposta=searchTree(t,num);
        if(resposta!=NULL)
          printf("%d's balance factor: %d. ",resposta->entry, resposta->bf);
        else
          printf("%d was not found. ",num);
      }
      printf("<ENTER>");
      getchar();
    }
    else if(strcmp(input,"re") == 0) {
      int num, scanres;
      char tempInput[50], enter;
      printf("Number to remove: ");
      fgets(tempInput,sizeof(tempInput), stdin);
      scanres = sscanf(tempInput,"%d%c",&num,&enter);
      if(!(scanres == 2 && enter == '\n'))
        printf("Not a number. ");
      else {
        resposta=searchTree(t,num);
        if(resposta!=NULL) {
          t = deleteTree(t,num,&diminuiu);
          printf("%d was removed. ",num);
        }
        else
          printf("%d was not found. ",num);
      }
      printf("<ENTER>");
      getchar();
    }
    else if(strcmp(input,"mi") == 0) {
      Tree res;
      res = minEntry(t);
      if(!res)
        printf("Tree is empty. <ENTER>");
      else
        printf("Smallest value in tree: %d <ENTER>",res->entry);
      getchar();
    }
    else if(strcmp(input,"he") == 0) {
      printf("\n# available actions:\n");
      printf("# pr - print current tree.\n");
      printf("# in - insert in tree;\n");
      printf("# ht - get tree height;\n");
      printf("# si - get tree size (number of elements);\n");
      printf("# se - search number in tree;\n");
      printf("# bf - get balance factor;\n");
      printf("# re - remove from tree;\n");
      printf("# mi - get smallest value in tree (min);\n");
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