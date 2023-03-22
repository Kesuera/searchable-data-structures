/*
 * Autor: Samuel Hetteš
 * Predmet: Dátové šturktúry a algoritmy
 * Zadanie: Vyhľadávanie v dynamických množinách
 * Testovanie
 * Prostredie: Visual Studio Code
 * Dátum: 6. 4. 2021
*/



//hlavičky
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "hashOwn.h"
#include "hashTaken.h"
#include "avlOwn.h"
#include "redBlackTaken.h"


//globálne premenné - počítanie kolízií, balancovaní stromov a glob. koreň red black stromu
extern int balancesRB;
extern int balancesAVL;
extern int collisionsHashTaken;
extern int collisionsHashOwn;
extern struct rbNode *rootRB;


//tester
void tester(unsigned long long tableSize, unsigned long long items, unsigned long long searchedItems, int linearData){    int length;
    unsigned long long data, alreadySearched = 0, i;

    AVLTREE *avlRoot = NULL;    //pointer na koreň avl stromu

    HASHTABLE *hashTableOwn = NULL;    //pointer na tabuľku s reťazením
    hashTableOwn = initHashOwn(hashTableOwn, tableSize);    //inicializácia tabuľky

    if(hashTableOwn == NULL)
        return;

    struct Data *hashTableTaken = (struct Data *) malloc(tableSize * sizeof(struct Data));    //pointer na tabuľku s lineárnym skúšaním
    
    if(hashTableTaken == NULL)
        return;
    
    for(unsigned long long count = 0; count <= tableSize - 1; count++)    //inicializácia tabuľky
        hashTableTaken[count].status = EMPTY;

    double insertTimeAVL = 0;    //jednotlivé časy pre vyhľadávanie a vkladanie v jednotlivých metódách
    double insertTimeRB = 0;
    double insertTimeHO = 0;
    double insertTimeHT = 0;
    double searchTimeAVL = 0;
    double searchTimeRB = 0;
    double searchTimeHO = 0;
    double searchTimeHT = 0;
    clock_t start, end;

    length = (rand() % (20 - 10 + 1)) + 10;    //náhodná dĺžka čísla, ktoré budeme generovať (počet cifier od 10 - 20)

    char *randomNumber = (char *) malloc((length + 1) * sizeof(char));

    if(randomNumber == NULL)
        return;

    for(int j = 0; j < length; j++){    //generovanie náhodného číselného reťazca
        if(j == 0)
            randomNumber[j] = (char)((rand() % ('9' - '1' + 1)) + '1');
        else
            randomNumber[j] = (char)((rand() % ('9' - '0' + 1)) + '0');
    }

    randomNumber[length] = 0;

    data = atoll(randomNumber);    //prevedenie reťazca na číslo, ktoré budeme vkladať

    for(i = 0; i < items; i++){
        if(linearData)    //ak máme zapnuté lineárne dáta, vždy budeme iba inkrementovať dané náhodné číslo
            data++;
        else{    //inak budeme generovať vždy nové náhodné číslo
            length = (rand() % (20 - 10 + 1)) + 10;

            for(int j = 0; j < length; j++){
                if(j == 0)
                    randomNumber[j] = (char)((rand() % ('9' - '1' + 1)) + '1');
                else
                    randomNumber[j] = (char)((rand() % ('9' - '0' + 1)) + '0');
            }

            randomNumber[length] = 0;

            data = atoll(randomNumber);
        }

        //samotné vkladanie dát a meranie časov
        start = clock();
        avlRoot = insertAVL(avlRoot, data);
        end = clock();
        insertTimeAVL += (((double) (end - start)) / CLOCKS_PER_SEC);

        start = clock();
        insertRB(data);
        end = clock();
        insertTimeRB += (((double) (end - start)) / CLOCKS_PER_SEC);

        start = clock();
        insertHashOwn(hashTableOwn, data);
        end = clock();
        insertTimeHO += (((double) (end - start)) / CLOCKS_PER_SEC);

        start = clock();
        insertHashTaken(data, hashTableTaken, tableSize);
        end = clock();
        insertTimeHT += (((double) (end - start)) / CLOCKS_PER_SEC);

        if(alreadySearched < searchedItems){ 
            alreadySearched++;

            //vyhľadávanie dát a zápis časov
            start = clock();
            searchAVL(avlRoot, data);
            end = clock();
            searchTimeAVL += (((double) (end - start)) / CLOCKS_PER_SEC);

            start = clock();
            searchRB(data);
            end = clock();
            searchTimeRB += (((double) (end - start)) / CLOCKS_PER_SEC);
            
            start = clock();
            searchHashOwn(hashTableOwn, data);
            end = clock();
            searchTimeHO += (((double) (end - start)) / CLOCKS_PER_SEC);

            start = clock();
            searchHashTaken(data, hashTableTaken, tableSize);
            end = clock();
            searchTimeHT += (((double) (end - start)) / CLOCKS_PER_SEC);
        }
    }

    //uvoľnenie pamäte
    freeHashOwn(hashTableOwn);
    freeHashTaken(hashTableTaken);
    freeRB(rootRB);
    freeAVL(avlRoot);
    free(randomNumber);

    //výpis výsledkov daného testu
    if(searchedItems != 0)
        printf("Test - inserting %I64u items and searching %I64u items\n", items, searchedItems);
    else
        printf("Test - insertion of %I64u items\n", items);
    printf("Available hash table size: %I64u\n", tableSize);
    if(linearData)
        printf("Linear data\n");
    else
        printf("Random data\n");
    printf("----------------------------------------\nInsert time of:\n");
    printf("AVL TREE: %lf s\n", insertTimeAVL);
    printf("RED BLACK TREE: %lf s\n", insertTimeRB);
    printf("CHAINING HASH TABLE: %lf s\n", insertTimeHO);
    printf("LINEAR PROBING HASH TABLE: %lf s\n", insertTimeHT);
    if(searchedItems != 0){
        printf("----------------------------------------\nSearch time of:\n");
        printf("AVL TREE: %lf s\n", searchTimeAVL);
        printf("RED BLACK TREE: %lf s\n", searchTimeRB);
        printf("CHAINING HASH TABLE: %lf s\n", searchTimeHO);
        printf("LINEAR PROBING HASH TABLE: %lf s\n", searchTimeHT);
        printf("----------------------------------------\nOverall time:\n");
        printf("AVL TREE: %lf s\n", searchTimeAVL + insertTimeAVL);
        printf("RED BLACK TREE: %lf s\n", searchTimeRB + insertTimeRB);
        printf("CHAINING HASH TABLE: %lf s\n", searchTimeHO + insertTimeHO);
        printf("LINEAR PROBING HASH TABLE: %lf s\n", searchTimeHT + insertTimeHT);
    }
    
    printf("----------------------------------------\nTrees were balanced:\n");
    printf("AVL TREE: %d times\n", balancesAVL);
    printf("RED BLACK TREE: %d times\n", balancesRB);
    printf("----------------------------------------\nCollisions in hash tables:\n");
    printf("CHAINING HASH TABLE: %d\n", collisionsHashOwn);
    printf("LINEAR PROBING HASH TABLE: %d\n\n\n", collisionsHashTaken);

    balancesAVL = 0;
    balancesRB = 0;
    collisionsHashOwn = 0;
    collisionsHashTaken = 0;
}


int main(void){
    srand(time(0));

    //testovanie
    tester(200000, 100000, 100000, 1);    //malý počet dát, lineárne dáta, ideálna veľkosť tabuľky
    tester(200000, 100000, 100000, 0);    //malý počet dát, náhodné dáta, ideálna veľkosť tabuľky
    tester(100000, 100000, 100000, 1);    //malý počet dát, lineárne dáta, počet dát = veľkosť tabuľky
    tester(100000, 100000, 100000, 0);    //malý počet dát, náhodné dáta, počet dát = veľkosť tabuľky
    tester(2000000, 1000000, 1000000, 1);    //stredný počet dát, lineárne dáta, ideálna veľkosť tabuľky
    tester(2000000, 1000000, 1000000, 0);    //stredný počet dát, náhodné dáta, ideálna veľkosť tabuľky
    tester(1000000, 1000000, 1000000, 1);    //stredný počet dát, lineárne dáta, počet dát = veľkosť tabuľky
    tester(1000000, 1000000, 1000000, 0);    //stredný počet dát, náhodné dáta, počet dát = veľkosť tabuľky
    tester(20000000, 10000000, 10000000, 1);    //veľký počet dát, lineárne dáta, ideálna veľkosť tabuľky
    tester(20000000, 10000000, 10000000, 0);    //veľký počet dát, náhodné dáta, ideálna veľkosť tabuľky
    tester(10000000, 10000000, 10000000, 1);    //veľký počet dát, lineárne dáta, počet dát = veľkosť tabuľky
    tester(10000000, 10000000, 10000000, 0);    //veľký počet dát, náhodné dáta, počet dát = veľkosť tabuľky
    
    return 0;
}