#include "List.h"


Node *createNode(int v){
    Node *l = (Node*)calloc(1,sizeof(Node));
    l->value = v;
    l->next = NULL;
    return l;
}


List *createList(){
    List *list = (List*)calloc(1, sizeof(List));
    list->first = NULL;
    list->size = 0;
    return list;
}


void addNodeEnd(List *list, int v){
    Node *n = createNode(v);
    if(list->first == NULL){
        list->first = n;
        list->first->next = NULL;
        return;
    }
    Node *p = list->first;
    while(p->next != NULL) p = p->next;
    p->next = n;
    list->size++;
}


void addNodeBegining(List *list, int v){
    Node *n = createNode(v);
    n->next = list->first;
    list->first = n;
    list->size++;
}

int getPivot(Node *first, int k){
    while(first && k){
        first = first->next;
        k--;
    }
    if (first != NULL) return first->value;
    return -1;
}


void swap(Node *first, int i, int j){
    Node *p = first;
    int auxI;
    int auxJ;
    int x = i;
    while(p && i){
        p = p->next;
        i--;
    }
    auxI = p->value;
    p = first;
    while(p && j){
        p = p->next;
        j--;
    }
    auxJ = p->value;
    p->value = auxI;
    p = first;
    i = x;
    while(p && i){
        p = p->next;
        i--;
    }
    p->value = auxJ;
}


Node *quickSortList(Node *first, int k, int r){
    int i, j;
    int jval;
    int pivot;
    i = k + 1;
    if (k + 1 < r) {
        pivot = getPivot(first, k);
        for (j = k + 1; j <= r; j++) {
            jval = getPivot(first, j);
            if (jval > pivot && jval != -1) {
                swap(first, i, j);
                i++;
            }
        }
        swap(first, i - 1, k);
        quickSortList(first, k, i);
        quickSortList(first, i, r);
    }
    return first;
}


void sortList(List *list){
    Node *p = list->first;
    int n = 0;
    while (p){
        p = p->next;
        n++;
    }
    list->first = quickSortList(list->first, 0, n);
}


Node *removeNodeEnd(List *list){
    Node *p = list->first;
    if(p->next == NULL){
        list->first = NULL;
        list->size--;
        return p;
    }
    Node *q = p->next;
    while(q->next != NULL){
        p = q;
        q = q->next;
    }
    p->next = NULL;
    list->size--;
    return q;
}




void printList(List *list, FILE *output){
    Node *p = list->first;
    while(p != NULL){
        fprintf(output, "%d", p->value+1);
        if(p->next != NULL) fprintf(output, ",");
        p = p->next;
    }
    fprintf(output, "\n");
}


void freeList(List *list){
    Node *p = list->first;
    Node *q;
    while(p != NULL){
        q = p->next;
        free(p);
        p = q;
    }
    free(list);
}
