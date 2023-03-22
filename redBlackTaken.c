/*
 * Predmet: Dátové štruktúry a algoritmy
 * Zadanie: Vyhľadávanie v dynamických množinách
 * Metóda: Red Black Tree - PostOrder vyhľadávanie
 * Zdroj kódu - https://www.programiz.com/dsa/red-black-tree
*/



// Implementing Red-Black Tree in C

#include <stdio.h>
#include <stdlib.h>

#include "redBlackTaken.h"

struct rbNode *rootRB = NULL;
int balancesRB = 0;

// Create a red-black tree
struct rbNode *createNode(unsigned long long data) {
    struct rbNode *newnode;
    newnode = (struct rbNode *)malloc(sizeof(struct rbNode));
    newnode->data = data;
    newnode->color = RED;
    newnode->link[0] = newnode->link[1] = NULL;
    return newnode;
}

// Insert an node
void insertRB(unsigned long long data) {
  struct rbNode *stack[98], *ptr, *newnode, *xPtr, *yPtr;
  int dir[98], ht = 0, index;
  ptr = rootRB;
  if (!rootRB) {
    rootRB = createNode(data);
    return;
  }

  stack[ht] = rootRB;
  dir[ht++] = 0;
  while (ptr != NULL) {
    if (ptr->data == data) {
      return;
    }
    index = (data - ptr->data) > 0 ? 1 : 0;
    stack[ht] = ptr;
    ptr = ptr->link[index];
    dir[ht++] = index;
  }
  stack[ht - 1]->link[index] = newnode = createNode(data);
  while ((ht >= 3) && (stack[ht - 1]->color == RED)) {
    balancesRB++;
    if (dir[ht - 2] == 0) {
      yPtr = stack[ht - 2]->link[1];
      if (yPtr != NULL && yPtr->color == RED) {
        stack[ht - 2]->color = RED;
        stack[ht - 1]->color = yPtr->color = BLACK;
        ht = ht - 2;
      } else {
        if (dir[ht - 1] == 0) {
          yPtr = stack[ht - 1];
        } else {
          xPtr = stack[ht - 1];
          yPtr = xPtr->link[1];
          xPtr->link[1] = yPtr->link[0];
          yPtr->link[0] = xPtr;
          stack[ht - 2]->link[0] = yPtr;
        }
        xPtr = stack[ht - 2];
        xPtr->color = RED;
        yPtr->color = BLACK;
        xPtr->link[0] = yPtr->link[1];
        yPtr->link[1] = xPtr;
        if (xPtr == rootRB) {
          rootRB = yPtr;
        } else {
          stack[ht - 3]->link[dir[ht - 3]] = yPtr;
        }
        break;
      }
    } else {
      yPtr = stack[ht - 2]->link[0];
      if ((yPtr != NULL) && (yPtr->color == RED)) {
        stack[ht - 2]->color = RED;
        stack[ht - 1]->color = yPtr->color = BLACK;
        ht = ht - 2;
      } else {
        if (dir[ht - 1] == 1) {
          yPtr = stack[ht - 1];
        } else {
          xPtr = stack[ht - 1];
          yPtr = xPtr->link[0];
          xPtr->link[0] = yPtr->link[1];
          yPtr->link[1] = xPtr;
          stack[ht - 2]->link[1] = yPtr;
        }
        xPtr = stack[ht - 2];
        yPtr->color = BLACK;
        xPtr->color = RED;
        xPtr->link[1] = yPtr->link[0];
        yPtr->link[0] = xPtr;
        if (xPtr == rootRB) {
          rootRB = yPtr;
        } else {
          stack[ht - 3]->link[dir[ht - 3]] = yPtr;
        }
        break;
      }
    }
  }
  rootRB->color = BLACK;
}

struct rbNode *searchRB(unsigned long long value){
    struct rbNode *temp = rootRB;

    while(temp != NULL){
        if(temp->data > value){
            temp = temp->link[0];
        }else if(temp->data < value){
            temp = temp->link[1];
        } else if(temp->data == value){
            return temp;
        }
    }
    return NULL;
}

void freeRB(struct rbNode *vertex){    
    if(vertex == NULL)
        return;
        
    freeRB(vertex->link[0]);
    freeRB(vertex->link[1]);
    free(vertex);
    vertex = NULL;
    rootRB = NULL;
}