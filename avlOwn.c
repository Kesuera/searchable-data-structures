/*
 * Autor: Samuel Hetteš
 * Predmet: Dátové šturktúry a algoritmy
 * Zadanie: Vyhľadávanie v dynamických množinách
 * Metóda: AVL Tree
 * Prostredie: Visual Studio Code
 * Dátum: 5. 4. 2021
*/



/*HEADER*/

#include <stdio.h>
#include <stdlib.h>    //alok. pamäte

#include "avlOwn.h"

int balancesAVL = 0;


/*FUNCTIONS*/

//vytvorenie nového stromu
AVLTREE *create(unsigned long long key){
    AVLTREE *newTree;

    if(!(newTree = (AVLTREE *) malloc(sizeof(AVLTREE)))){    //alokuj dostatok miesta
        printf("Allocation of memory for new tree failed\n");
        return newTree;
    }

    newTree->key = key;    //nastav kľúč
    newTree->height = 0;    //výšku nastav na 0, keďže sa jedná o list
    newTree->rightChild = NULL;    //strom je listom, čiže nemá potomkov
    newTree->leftChild = NULL;

    return newTree;    //vráť pointer na nový strom
}

//rotácia stromu vpravo
AVLTREE *rightRotation(AVLTREE *root){
    AVLTREE *newRoot = root->leftChild;    //náš nový koreň nastav na ľavého potomka predchádzajúceho koreňa
    root->leftChild = newRoot->rightChild;    //ľavého potomka predchádzajúceho koreňa nastav na pravého potomka nového koreňa
    newRoot->rightChild = root;    //pravého potomka nového koreňa nastav na predchádzajúci koreň

    //aktualizuj výšky koreňov
    root->height = NEW_HEIGHT(root);
    newRoot->height = NEW_HEIGHT(newRoot);

    return newRoot;    //vráť pointer na nový koreň
}

//rotácia stromu vľavo
AVLTREE *leftRotation(AVLTREE *root){
    AVLTREE *newRoot = root->rightChild;    //náš nový koreň nastav na pravého potomka predchádzajúceho koreňa
    root->rightChild = newRoot->leftChild;    //pravý potom predch. koreňa nastav na ľavého potomka nového koreňa
    newRoot->leftChild = root;    //ľavého potomka nového koreňa nastav na predch. koreň

    //aktualizuj výšky koreňov
    root->height = NEW_HEIGHT(root);
    newRoot->height = NEW_HEIGHT(newRoot);

    return newRoot;    //vráť pointer na nový koreň
}

//pridanie dát do stromu
AVLTREE *insertAVL(AVLTREE *vertex, unsigned long long key){
    if(vertex && vertex->key == key)    //ak existuje strom, kt. kľúč sa zhoduje s pridávaným, vráť vrchol / nebudeme pridávať nič
        return vertex;

    if(!vertex)    //ak sme prišli na miesto, kde už pointer na nič neukazuje, vytvor nový strom pre daný kľúč
        vertex = create(key);

    else if(key < vertex->key)    //ak pridávaný kľúč je menší ako kľúč v koreni
        vertex->leftChild = insertAVL(vertex->leftChild, key);    //rekurzívne zavolaj funkciu pre pridanie kľúča do ľavého podstromu

    else    //ak je pridávaný kľúč väčší ako kľúč v koreni
        vertex->rightChild = insertAVL(vertex->rightChild, key);    //rekurzívne zavolaj funkciu pre pridanie dát do pravého podstromu

    vertex->height = NEW_HEIGHT(vertex);    //aktualizuj výšku vrchola

    int heightDifference = HEIGHT_DIFFERENCE(vertex);    //získaj rozdiel výšok ľavého a pravého podstromu, ak je strom vybalancovaný bude sa rovnať {-1, 0, 1}

    //ak je rozdiel väčší ako 1 a pridávaný kľúč je menší ako kľúč ľavého potomka
    if(heightDifference > 1 && key < vertex->leftChild->key){
        vertex = rightRotation(vertex);    //strom je nevyvážený vľavo, preto sprav rotáciu stromu vpravo
        balancesAVL++;
    }

    //ak pridávané kľúč je väčší ako kľúč ľavého potomka
    else if(heightDifference > 1 && key > vertex->leftChild->key){
        vertex->leftChild = leftRotation(vertex->leftChild);    //najprv sprav rotáciou ľavého podstromu vľavo
        vertex = rightRotation(vertex);    //následne rotáciou stromu vpravo
        balancesAVL++;
    }

    //ak je rozdiel menší ako -1 a pridávaný kľúč je väčší ako kľúč pravého potomka
    else if(heightDifference < -1 && key > vertex->rightChild->key){
        vertex = leftRotation(vertex);    //strom je nevyvážený vpravo, preto sprav rotáciu stromu vľavo
        balancesAVL++;
    }

    //ak pridávaný kľúč je menší ako kľúč pravého potomka
    else if(heightDifference < -1 && key < vertex->rightChild->key){
        vertex->rightChild = rightRotation(vertex->rightChild);    //najprv sprav rotáciu pravého podstromu vpravo
        vertex = leftRotation(vertex);    //následne rotáciu stromu vľavo
        balancesAVL++;
    }

    return vertex;    //vráť pointer na vrchol
}

//vyhľadanie dát v strome - preorder
AVLTREE *searchAVL(AVLTREE *vertex, unsigned long long key){
    if(!vertex)   //ak taký vrchol neexistuje vráť NULL
        return NULL;

    else if(key == vertex->key)    //ak sa kľúč v koreni zhoduje s hľadaným vráť pointer na dáta
        return vertex;

    else if(key < vertex->key)    //ak hľadaný kľúč je menší ako kľúč v koreni
        return searchAVL(vertex->leftChild, key);    //rekurzívne zavolaj funkciu pre hľadanie v ľavom podstrome

    else    //ak hľadaný kľuč je väčší ako kľúč v koreni
        return searchAVL(vertex->rightChild, key);    //rekurzívne zavolaj funkciu pre hľadanie v pravom podstrome
}

//uvoľnenie pamäti alokovanej pre strom
void freeAVL(AVLTREE *vertex){
    if(vertex == NULL)
        return;

    freeAVL(vertex->leftChild);    //zavolaj rekurzívne funkciu pre uvoľnenie ľavého podstromu
    freeAVL(vertex->rightChild);    //zavolaj rekurzívne funkciu pre uvoľnenie pravého podstromu

    free(vertex);    //uvoľni pamäť stromu
    vertex = NULL;
}