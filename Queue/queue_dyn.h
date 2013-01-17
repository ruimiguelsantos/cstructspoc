#include <stdlib.h>
#define MAX 2048

struct node{
	int info;
	struct node *next;
};

struct buffer{
	struct node *last;
	struct node *first;
	int n; // numero de elementos na queue
};

typedef struct buffer *Buffer;

void init(Buffer);
int empty(Buffer);
int add(Buffer, int);
int next(Buffer, int*);
int rem(Buffer, int*);