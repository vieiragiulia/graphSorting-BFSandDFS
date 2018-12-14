#ifndef GRAPH_H
#define GRAPH_H

#include "List.h"


typedef struct Graph{
    int numVertex;
    int numEdges;
    List **adjLists;
    int *visited;
}Graph;

Graph *createGraph(int V, int E);
Graph *invertGraph(Graph *graph);
void addEdge(Graph *graph, int src, int dest);

int *findRoots(Graph *graph);
int findNRoots(int n, int *roots);

int AgoestoB(Graph *graph, int thisNode, int *auxVisited);
int passesOnItself(Graph *inverted, int vertex);
int detectCycle(Graph *graph, int *roots, int nRoots);
int thisIsCycle(Graph *graph, int root);


int sortGraph(Graph *graph, int vertex, List *sorted);

void cleanVisits(Graph *graph);
void freeGraph(Graph *graph);

void readGraph(int m, FILE *input, Graph *graph);
void processGraph(Graph *graph, FILE *output);

int detectMoreThanOnePathfromAtoB(Graph *graph, int thisNode);

#endif
