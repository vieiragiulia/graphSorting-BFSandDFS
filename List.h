#ifndef LIST_H
#define LIST_H

#include <stdio.h>
#include <stdlib.h>

typedef struct Node{
    int value;
    struct Node *next;
}Node;

Node *createNode(int v);

typedef struct List{
    Node *first;
    int size;
}List;

List *createList();
void addNodeEnd(List *list, int v);
void addNodeBegining(List *list, int v);
Node *removeNodeEnd(List *list);

int getPivot(Node *first, int k);
void swap(Node *first, int i, int j);
Node *quickSortList(Node *first, int k, int r);
void sortList(List *list);

void printList(List *list, FILE *output);
void freeList(List *list);

#endif
