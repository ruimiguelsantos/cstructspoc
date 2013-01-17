#include "queue_stat.h"


void init(Buffer b) {

	b -> n = 0;
	b -> last = 0;
	b -> first = 1;
}

int empty(Buffer b) {

	return (b -> n == 0);
}

int add(Buffer b, int x) {

	if(b -> n == QMAX)
		return 0;
	b -> last = inc(b -> last);
	(b -> queue)[b -> last] = x;
	(b -> n)++;

	return 1;
}

int next(Buffer b, int *x){ // First

	if(empty(b))
		return 0;

	(*x) = (b -> queue)[b -> first];

	return 1;
}

int rem(Buffer b, int *x){ // Dequeue

	if(!next(b,x))
		return 0;

	(b -> n)--;
	b -> first = inc(b -> first);

	return 1;
}

int inc(int x){

	if(x + 1 >= QMAX)
		x = 0;
	else
		x++;

	return x;
}