#include "stack_stat.h"

void init(Buffer b){
	
	b -> n = 0;
}

int empty(Buffer b){
	
	return (b->n==0);
}

int add(Buffer b, int x){

	if(b -> n == MAX)
		return 0;
	
	(b -> stack)[b -> n++] = x;
	
	return 1;
}

int next(Buffer b, int *x){ // top

	if(empty(b))
		return 0;
	
	(*x) = (b -> stack)[(b -> n)-1];
	
	return 1;
}

int rem(Buffer b, int *x){ // pop / top

	if(!next(b,x))
		return 0;
	
	(b -> n)--;
	
	return 1;
}

