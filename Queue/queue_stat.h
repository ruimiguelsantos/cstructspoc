#define QMAX 8

struct buffer{
	int queue[QMAX];
	int n; // numero de elementos na queue
	int first, last; // array circular
};

typedef struct buffer *Buffer;

void init(Buffer);
int empty(Buffer);
int add(Buffer, int);
int next(Buffer, int*);
int rem(Buffer, int*);
int inc(int);