#include "../HashTable/open_addressing.h"
#include <stdio.h>
#include <string.h>

void printHash(Hashtable h, int used, int maxSize) {
  printf("\nStatus [%d/%d]:\n",used, maxSize);
  printf("--\n");
  int i=0;
  Hashtable aux = h;
  while(i < maxSize) {
    printf("%d # (%s,%ld) \n",i, aux[i]->key, aux[i]->entry);
    i++;
  }
  printf("--\n");
}

int main(){

  int maxSize = 8;
  int used = 0;
  float loadFactor = 0;
  Hashtable h;

  h = init(h,maxSize);

  int r=0,resposta;
  while(r!=1){
    printHash(h,used, maxSize);
    char input[1024];
    printf("\naction (he for help)$ ");
    fgets(input, sizeof(input), stdin);
    input[strlen(input)-1] = '\0';
    if(strcmp(input,"in") == 0) {
      long int num, scanres;
      char tempInput[50], enter;
      printf("Key to insert: ");
      fgets(tempInput,sizeof(tempInput), stdin);
      tempInput[strlen(tempInput)-1] = '\0';
      char tempNum[20];
      printf("Value: ");
      fgets(tempNum,sizeof(tempNum), stdin);
      scanres = sscanf(tempNum,"%ld%c",&num,&enter);
      if(!(scanres == 2 && enter == '\n'))
        printf("Not a number. ");
      else {
        resposta=insert(h,tempInput,strlen(tempInput),num,maxSize);
        if(resposta) {
          used++;
          updateLoadFactor(used,maxSize,&loadFactor);
          printf("Inserted %ld. ",num);
          if(loadFactor > 0.7) {
            h = duplicate(h,&maxSize);
            printf("\n--> Load Factor of 0.7 exceeded. Duplicated hash table size. ");
          }
        }
        else
          printf("Not inserted. ");
      }
      printf("<ENTER>");
      getchar();
    }
    else if(strcmp(input,"te") == 0) {
      printf("h[0]: %s\n",h[0]->key);
      getchar();
    }
    else if(strcmp(input,"al") == 0) {
      long int num, scanres;
      char tempInput[50], enter;
      printf("Key to alter: ");
      fgets(tempInput,sizeof(tempInput), stdin);
      tempInput[strlen(tempInput)-1] = '\0';
      char tempNum[20];
      printf("New value: ");
      fgets(tempNum,sizeof(tempNum), stdin);
      scanres = sscanf(tempNum,"%ld%c",&num,&enter);
      if(!(scanres == 2 && enter == '\n'))
        printf("Not a number. ");
      else {
        resposta=alter(h,tempInput,strlen(tempInput),num,maxSize);
        if(resposta)
          printf("%s's value altered to %ld. ",tempInput,num);
        else
          printf("[error] No changes. ");
      }
      printf("<ENTER>");
      getchar();
    }
    else if(strcmp(input,"se") == 0) {
      long int num, scanres;
      Node res;
      char tempInput[50], enter;
      printf("Key to search: ");
      fgets(tempInput,sizeof(tempInput), stdin);
      tempInput[strlen(tempInput)-1] = '\0';
      res=search(h,tempInput,strlen(tempInput),maxSize);
      if(res)
        printf("Found '%s'. Value: %ld. ", tempInput, res->entry);
      else
        printf("'%s' was not found. ", tempInput);
      printf("<ENTER>");
      getchar();
    }
    else if(strcmp(input,"re") == 0) {
      long int num, scanres;
      char tempInput[50], enter;
      printf("Key to remove: ");
      fgets(tempInput,sizeof(tempInput), stdin);
      tempInput[strlen(tempInput)-1] = '\0';
      resposta=rem(h,tempInput,strlen(tempInput),maxSize);
      if(resposta) {
        used--;
        updateLoadFactor(used,maxSize,&loadFactor);
        printf("Removed %s. ",tempInput);
      }
      else
        printf("'%s' was not removed. ", tempInput);
      printf("<ENTER>");
      getchar();
    }
    else if(strcmp(input,"pr") == 0) {
      printHash(h,used,maxSize);
    }
    else if(strcmp(input,"he") == 0) {
      printf("\n# available actions:\n");
      printf("# in - insert in hash table;\n");
      printf("# re - remove from hash table;\n");
      printf("# al - alter the value of a key;\n");
      printf("# se - search in hash table;\n");
      printf("# pr - print hashtable contents;\n");
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