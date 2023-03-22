#ifndef TEST_AVLOWN
#define TEST_AVLOWN


/*DEFINED TYPES*/

//štruktúra stromu
typedef struct avlTree{
    unsigned long long key;
    int height;
    struct avlTree *leftChild, *rightChild;
} AVLTREE;

extern int balancesAVL;


/*MACROS*/

#define MAX(x, y) (x > y ? x : y)
#define HEIGHT(tree) (tree ? tree->height : -1)
#define HEIGHT_DIFFERENCE(root) (root ? HEIGHT(root->leftChild) - HEIGHT(root->rightChild) : 0)
#define NEW_HEIGHT(root) (1 + MAX(HEIGHT(root->leftChild), HEIGHT(root->rightChild)))


/*FUNCTIONS*/

AVLTREE *create(unsigned long long key);
AVLTREE *rightRotation(AVLTREE *root);
AVLTREE *leftRotation(AVLTREE *root);
AVLTREE *insertAVL(AVLTREE *vertex, unsigned long long key);
AVLTREE *searchAVL(AVLTREE *vertex, unsigned long long key);
void freeAVL(AVLTREE *vertex);

#endif