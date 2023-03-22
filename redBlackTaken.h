#ifndef TEST_RBTAKEN
#define TEST_RBTAKEN

enum nodeColor {
    RED,
    BLACK
};

typedef struct rbNode {
    unsigned long long data;
    int color;
    struct rbNode *link[2];
} RBNODE;

extern struct rbNode *rootRB;
extern int balancesRB;

struct rbNode *createNode(unsigned long long data);
void insertRB(unsigned long long data);
struct rbNode *searchRB(unsigned long long value);
void freeRB(struct rbNode *vertex);

#endif