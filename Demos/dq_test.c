#include "../Queue/queue_dyn.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void printQueue(Buffer b){
  printf("\nStatus [%d/%d]:\n",b->n,MAX);
  printf("--\n");
  struct node *aux = b -> first;
  while(aux != NULL){
      printf("|%d| ",aux->info);
    if(aux==b->first && aux!=b->last)
      printf("<- First\n");
    else if(aux==b->last && aux!=b->first)
      printf("<- Last\n");
    else if(aux==b->first && aux==b->last)
      printf("<- First, Last\n");
    else
      printf("\n");
    aux = aux -> next;
  }
  if(b -> first == NULL)
    printf("EMPTY\n");
  printf("--\n");
}

int main(){

  Buffer b = (Buffer) malloc(sizeof(struct buffer));

  init(b);
  int r=0,resposta;
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