#include "../Queue/queue_stat.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>

void printQueue(Buffer b){
  int i=QMAX-1;
  printf("\nStatus [%d/%d]:\n",b->n,QMAX);
  printf("--\n");
  int ptr = b->first;
  while(i >= 0){
    if(b->queue[i]==INT_MAX)
      printf("EMPTY ");
    else
      printf("|%d| ",b->queue[i]);
    if(i==b->first && i!=b->last)
      printf("<- First\n");
    else if(i==b->last && i!=b->first)
      printf("<- Last\n");
    else if(i==b->first && i==b->last)
      printf("<- First, Last\n");
    else
      printf("\n");
    i--;
  }
  printf("--\n");
}

int main(){

  Buffer b = (Buffer) malloc(sizeof(struct buffer));

  init(b);
  int r=0,fill,resposta;
  for(fill=0;fill<QMAX;fill++)
    b->queue[fill]=INT_MAX;
  while(r!=1){
    printQueue(b);
    char input[1024];
    printf("\naction (he for help)$ ");
    fgets(input, sizeof(input), stdin);
    input[strlen(input)-1] = '\0';
    if(strcmp(input,"en") == 0) {
      int num, scanres;
      char tempInput[50], enter;
      printf("Number to enqueue: ");
      fgets(tempInput,sizeof(tempInput), stdin);
      scanres = sscanf(tempInput,"%d%c",&num,&enter);
      if(!(scanres == 2 && enter == '\n'))
        printf("Not a number. ");
      else {
        resposta=add(b,num);
        if(resposta)
          printf("Enqueued %d. ",num);
        else
          printf("Queue is full. ");
      }
      printf("<ENTER>");
      getchar();
    }
    else if(strcmp(input,"de") == 0) {
      int removed, ret;
      ret = empty(b);
      if(ret)
        printf("Queue is empty. <ENTER>");
      else {
        rem(b,&removed);
        printf("Dequeued %d. <ENTER>",removed);
      }
      getchar();
    }
    else if(strcmp(input,"ne") == 0) {
      int top, res;
      res = next(b,&top);
      if (res)
        printf("Next in queue: %d <ENTER>",top);
      else
        printf("Queue is empty. <ENTER>");
      getchar();
    }
    else if(strcmp(input,"em") == 0) {
      if(empty(b))
        printf("Queue is empty. <ENTER>");
      else
        printf("Queue is not empty. <ENTER>");
      getchar();
    }
    else if(strcmp(input,"he") == 0) {
      printf("\n# available actions:\n");
      printf("# en - enqueue (add to queue);\n");
      printf("# de - dequeue (remove from queue);\n");
      printf("# ne - get next in queue;\n");
      printf("# em - check if queue is empty.\n");
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