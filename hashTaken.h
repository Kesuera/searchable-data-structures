#ifndef TEST_HASHTAKEN
#define TEST_HASHTAKEN

enum data_status {EMPTY, OCCUPIED};
 
struct Data
{
   unsigned long long key;
   enum data_status status;
}; 

extern int collisionsHashTaken;

unsigned long long hash_function(unsigned long long key, unsigned long long tableSize);
unsigned long long searchHashTaken(unsigned long long key, struct Data *hash_table, unsigned long long tableSize);
int insertHashTaken(unsigned long long key, struct Data *hash_table, unsigned long long tableSize);
void freeHashTaken(struct Data *hashTable);

#endif