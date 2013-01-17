#define MAX 2048

struct buffer{
	int stack[MAX];
	int n; // numero de elementos na stack
};

typedef struct buffer *Buffer;

void init(Buffer);
int empty(Buffer);
int add(Buffer, int);
int next(Buffer, int*);
int rem(Buffer, int*);
