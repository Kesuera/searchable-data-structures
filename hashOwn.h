#ifndef TEST_HASHOWN
#define TEST_HASHOWN


/*DEFINED TYPES*/

//štruktúra uložených dát
typedef struct data{
    unsigned long long key;
    struct data *next;
} DATA;

//štruktúra hashovacej tabuľky
typedef struct hashTable{
    DATA **data;
    unsigned long long size;
    unsigned long long inserted;
} HASHTABLE;

extern int collisionsHashOwn;

/*FUNCTIONS*/

HASHTABLE *resizeHashTable(HASHTABLE *hashTable);
unsigned long long getPrime(unsigned long long number);
HASHTABLE *initHashOwn(HASHTABLE *hashTable, unsigned long long tableSize);
DATA *createData(unsigned long long key);
unsigned long long hashData(HASHTABLE *hashTable, unsigned long long key);
DATA *searchHashOwn(HASHTABLE *hashTable, unsigned long long key);
void freeHashOwn(HASHTABLE *hashTable);
int insertHashOwn(HASHTABLE *hashTable, unsigned long long key);

#endif