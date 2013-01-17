// Ficha 3, seccao 3, ex.1
typedef struct btree {
  int value;
  struct btree *left, *right;
}Node, *Btree;

Btree init(Btree);
int size(Btree); // a)
int height(Btree); // b)
int maximum(int, int);
Btree add(Btree, int); // c)
int search(Btree, int); // d)
int max(Btree); // e)
