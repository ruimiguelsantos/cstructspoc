#include "../Stack/stack_stat.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void printStack(Buffer b){
  int i=(b->n)-1;
  printf("\nStatus [%d/%d]:\n",b->n,MAX);
  printf("--\n");
  if(b -> n == 0)
    printf("EMPTY\n");
  else
    while(i >= 0){
      printf("|%d|\n",b->stack[i--]);
    }
  printf("--\n");

}

int main(){

  Buffer b = (Buffer) malloc(sizeof(struct buffer));

  init(b);
  int r=0, resposta;
  while(r!=1){
    printStack(b);
    char input[1024];
    printf("\naction (he for help)$ ");
    fgets(input, sizeof(input), stdin);
    input[strlen(input)-1] = '\0';
    if(strcmp(input,"pu") == 0) {
      int num, scanres;
      char tempInput[50], enter;
      printf("Number to push: ");
      fgets(tempInput,sizeof(tempInput), stdin);
      scanres = sscanf(tempInput,"%d%c",&num,&enter);
      if(!(scanres == 2 && enter == '\n'))
        printf("Not a number. ");
      else {
        resposta = add(b,num);
        if(resposta)
          printf("Pushed %d to stack. ",num);
        else
          printf("Stack is full. ");
      }
      printf("<ENTER>");
      getchar();
    }
    else if(strcmp(input,"po") == 0) {
      int removed, ret;
      ret = empty(b);
      if(ret)
        printf("Stack is empty. <ENTER>");
      else {
        rem(b,&removed);
        printf("Popped %d. ",removed);
        printf("<ENTER>");
      }
      getchar();
    }
    else if(strcmp(input,"to") == 0) {
      int top, res;
      res = next(b,&top);
      if (res)
        printf("Stack top: %d <ENTER>",top);
      else
        printf("Stack is empty. <ENTER>");
      getchar();
    }
    else if(strcmp(input,"em") == 0) {
      if(empty(b))
        printf("Stack is empty. ");
      else
        printf("stack is not empty. ");
      printf("<ENTER>");
      getchar();
    }
    else if(strcmp(input,"he") == 0) {
      printf("\n# available actions:\n");
      printf("# pu - push to stack;\n");
      printf("# po - pop the stack;\n");
      printf("# to - get stack top;\n");
      printf("# em - check if stack is empty.\n");
      printf("# he - print this helper.\n");
      printf("# ex - exit.\n\n");
      printf("<ENTER>");
      getchar();
    }
    else if(strcmp(input,"ex") == 0) {
      r = 1;
      printf("Leaving... ");
      printf("<ENTER>");
      getchar();
    }
    else {
      printf("\nNot an action. Type he for available actions. ");
      printf("<ENTER>");
      getchar();
    }
  }
  printf("Done.\n");

  return 1;
}