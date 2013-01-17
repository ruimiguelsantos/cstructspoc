typedef int TreeEntry;

typedef enum BalanceFactor { LH , EH , RH } BalanceFactor;

typedef struct treenode TreeNode;

struct treenode {
  BalanceFactor bf;
  TreeEntry entry;
  TreeNode *left;
  TreeNode *right;
};

typedef TreeNode *Tree;

Tree createTree(void);
void emptyTree(Tree t);
void emptyTree2(Tree t);
int treeHeight(Tree t);
int maximum(int, int);
int treeSize(Tree t);
int isEmpty(Tree t);

typedef void (*Func)(Tree);

void preorder(Tree t, Func f);
void inorder(Tree t, Func f);
void postorder(Tree t, Func f);

Tree searchTree(Tree t, TreeEntry e);

Tree deleteTree(Tree t, TreeEntry e, int *diminuiu);
Tree deleteRight(Tree t, TreeEntry e, int *diminuiu);
Tree deleteLeft(Tree t, TreeEntry e, int *diminuiu);

Tree insertTree(Tree t, TreeEntry e, int *cresceu);

Tree insertRight(Tree t, TreeEntry e, int *cresceu);
Tree balanceRight(Tree t);

Tree insertLeft(Tree t, TreeEntry e, int *cresceu);
Tree balanceLeft(Tree t);

Tree rotateLeft(Tree t);
Tree rotateRight(Tree t);

// aux
Tree minEntry(Tree t);
int isLeaf(Tree t);
int has1Child(Tree t);