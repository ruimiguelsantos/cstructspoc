#define MAX 20

struct buffer {
  int heap[MAX];
  int n;
};

typedef struct buffer *Buffer;

int init(Buffer);
int add(Buffer, int);
int rem(Buffer, int*);
int next(Buffer, int*);
int empty(Buffer);
int pai(int);
int esq(int);
int dir(int);
void swap(int, int, int*);