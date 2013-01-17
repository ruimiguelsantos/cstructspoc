#include "stack_dyn.h"


void init(Buffer b){

	b -> stack = NULL;
	b -> n = 0;
}

int empty(Buffer b){

	return (b -> stack == NULL); // ou return (b -> n == 0)
}

int add(Buffer b, int x){

	struct node *new;
	
	if( !(new = malloc(sizeof(struct node))) || (b -> n == MAX) )
	// se a alocacao de memoria falhar
		return 0;
	
	new -> next = b -> stack;
	new -> info = x;
	b -> stack = new;
	(b -> n)++;
	
	return 1;
}

int next(Buffer b, int *x){

	if(empty(b))
		return 0;
	
	(*x) = b -> stack -> info;
	
	return 1;
}

int rem(Buffer b, int *x){

	if(!next(b,x))
		return 0;
	
	(b -> n)--;
	struct node *aux;
	aux = b -> stack;
	b -> stack = aux -> next;
	free(aux);
	
	return 1;
}