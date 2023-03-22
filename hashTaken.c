/*
 * Predmet: Dátové štruktúry a algoritmy
 * Zadanie: Vyhľadávanie v dynamických množinách
 * Metóda: Red Black Tree
 * Zdroj kódu - https://www.codingalpha.com/hash-table-c-program/
*/



#include<stdio.h>
#include<stdlib.h>

#include "hashTaken.h" 

int collisionsHashTaken = 0;
 
unsigned long long hash_function(unsigned long long key, unsigned long long tableSize)
{
   return (key % tableSize);
}
 
unsigned long long searchHashTaken(unsigned long long key, struct Data *hash_table, unsigned long long tableSize)
{
   unsigned long long count, temp, position;
   temp = hash_function(key, tableSize); 
   position = temp;
   for(count = 1; count != tableSize - 1; count++)
   {
      if(hash_table[position].status == EMPTY) 
      {
         return -1;
      }
      if(hash_table[position].key == key)
      {
         return position;
      }
      position = (temp + count) % tableSize; 
   }
   return -1;
}
 
int insertHashTaken(unsigned long long key, struct Data *hash_table, unsigned long long tableSize)
{
   unsigned long long count, position, temp;
   temp = hash_function(key, tableSize); 
   position = temp; 
   for(count = 1; count != tableSize - 1; count++)
   {
      if(hash_table[position].status == EMPTY)
      {
         hash_table[position].key = key;
         hash_table[position].status = OCCUPIED; 
         return 1;
      }
      if(hash_table[position].key == key)
      {
        return 0;
      }
      collisionsHashTaken++;
      position = (temp + count) % tableSize; 

   }

   return 0;
}

void freeHashTaken(struct Data *hashTable){
   free(hashTable);
}