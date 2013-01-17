#include "../Heap/minheap.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void printHeap(Buffer h){
  int i=0;
  printf("\nStatus [%d/%d]:\n",h->n,MAX);
  printf("--\n");
  while(i < h -> n){
    printf("%d | ",h->heap[i]);
    i++;
  }
  printf("\n--\n");
}

int main(){

  Buffer h = (Buffer) malloc(sizeof(struct buffer));

  init(h);
  int r=0,fill,resposta;
  while(r!=1){
    printHeap(h);
    char input[1024];
    printf("\naction (he for help)$ ");
    fgets(input, sizeof(input), stdin);
    input[strlen(input)-1] = '\0';
    if(strcmp(input,"in") == 0) {
      int num, scanres;
      char tempInput[50], enter;
      printf("Number to insert: ");
      fgets(tempInput,sizeof(tempInput), stdin);
      scanres = sscanf(tempInput,"%d%c",&num,&enter);
      if(!(scanres == 2 && enter == '\n'))
        printf("Not a number. ");
      else {
        resposta=add(h,num);
        if(resposta)
          printf("Inserted %d. ",num);
        else
          printf("Heap is full. ");
      }
      printf("<ENTER>");
      getchar();
    }
    else if(strcmp(input,"re") == 0) {
      int removed, ret;
      ret = empty(h);
      if(ret)
        printf("Heap is empty. <ENTER>");
      else {
        rem(h,&removed);
        printf("Removed %d. <ENTER>",removed);
      }
      getchar();
    }
    else if(strcmp(input,"ne") == 0) {
      int top, res;
      res = next(h,&top);
      if (res)
        printf("Next in heap: %d <ENTER>",top);
      else
        printf("Heap is empty. <ENTER>");
      getchar();
    }
    else if(strcmp(input,"em") == 0) {
      if(empty(h))
        printf("Heap is empty. <ENTER>");
      else
        printf("Heap is not empty. <ENTER>");
      getchar();
    }
    else if(strcmp(input,"he") == 0) {
      printf("\n# available actions:\n");
      printf("# in - insert in heap;\n");
      printf("# re - remove from heap);\n");
      printf("# ne - get next in heap (root);\n");
      printf("# em - check if heap is empty.\n");
      printf("# he - printfnt this helper.\n");
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