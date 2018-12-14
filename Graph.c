#include "Graph.h"


Graph *createGraph(int V, int E){
    Graph *graph = (Graph*)calloc(1, sizeof(Graph));
    graph->numVertex = V;
    graph->numEdges = E;
    graph->visited = (int*)calloc(V, sizeof(int));
    graph->adjLists = (List**)calloc(V, sizeof(List*));
    for(int i = 0;  i < V; i++) graph->adjLists[i] = createList();
    return graph;
}


void addEdge(Graph *graph, int src, int dest){
    addNodeEnd(graph->adjLists[src], dest);
}


void readGraph(int m, FILE *input, Graph *graph){
  int a, b;
  for(int i = 0; i < m; i++){
        fscanf(input, "%d %d", &a, &b);
        addEdge(graph, a-1, b-1);
    }
}


void cleanVisits(Graph *graph){
    for(int i = 0; i < graph->numVertex; i++) graph->visited[i] = 0;
}


int AgoestoB(Graph *graph, int thisNode, int *auxVisited){
    Node *p = graph->adjLists[thisNode]->first; //começa do começo
    while(p!=NULL){ //vai passando pelos caminhos
        // printf("VERTICE Q PASSOU NO LOOP %d\n", p->value+1);
        if(auxVisited[p->value] == 1) return 1; //chegou em B
        return AgoestoB(graph, p->value, auxVisited);
        p = p->next;
    }
    return 0; //não chegou em B
}


int thisIsCycle(Graph *graph, int root){
    int flag = 0;

    Node *p = graph->adjLists[root]->first; //a partir do inicio da lista de adjacência do nó
    graph->visited[root] = 1; //marcamos o nó atual

    while(p!=NULL){ //para todo elemento da lista de adjacência do nó referência
        if(graph->visited[p->value] == 0) {
            flag = thisIsCycle(graph, p->value); //se nunca foi vá
        }
        else{ //se já foi lá encontrou o ciclo

            return 1;
        }
        p = p->next;
    }
    graph->visited[root] = 0; //desmarcamos o nó atual
    return flag;
}


int detectCycle(Graph* graph, int *roots, int nRoots){
    for(int i = 0; i < nRoots; i++) if(thisIsCycle(graph, roots[i]) == 1) return 1;//CICLO
    return 0;//SÓ PASSOU EM CASAS NOVAS, SEM CICLO
}


int detectMoreThanOnePathfromAtoB(Graph *graph, int thisNode){
    Node *q;
    Node *p = graph->adjLists[thisNode]->first;
    int *auxVisited = (int*)calloc(graph->numVertex, sizeof(int)); //1 visitado 0 não

    while(p != NULL){ //para cada nó da lista de adjacência de thisNode
        q = graph->adjLists[thisNode]->first;

        while(q != NULL){ //vemos se ele chega em algum outro da lista
            auxVisited[q->value] = 1;

            if(AgoestoB(graph, p->value, auxVisited) == 1){
                free(auxVisited);
                return 1; //se chega = same displacement
            }
            q = q->next;
        }
        p = p->next;
    }

    free(auxVisited);
    return 0; //não teve same displacement
}


int *findRoots(Graph *graph){
    for(int i = 0; i < graph->numVertex; i++){
        Node *p = graph->adjLists[i]->first;
        while(p != NULL){
            graph->visited[p->value] = 1; //alguém aponta para ele
            p = p->next;
        }
    }
    int *roots = (int*)calloc(graph->numVertex, sizeof(int));
    int k = 0;
    for(int j = graph->numVertex-1; j > -1; j--){
        if(graph->visited[j] == 0){ //se ninguém aponta pra ele é raíz
            roots[k] = j;
            k++;
        }
    }
    return roots;
}


int findNRoots(int n, int *roots){
    for(int i = 1; i < n-1; i++)  if(roots[i] == roots[i+1]) return i;
    return n;
}


int sortGraph(Graph *graph, int vertex, List *sorted){
    /*enviar o vetor de raízes inteiro e seu tamanho */
    /*1 visitou e já passou
    0 não visitou ainda
    -1 está na borda*/
    List *border = createList(); //cria borda
    addNodeBegining(border, vertex); //empilha na borda
    graph->visited[vertex] = -1; //marca que pos na borda

    Node *q = NULL;
    int verify = 1; //0 = vários caminhos, 1 teve same displacement ou só tem 1 caminho

    while(border->first != NULL){//enquanto houverem elementos no campo de visão
        q = removeNodeEnd(border); //tira o mais antigo da borda
        addNodeBegining(sorted, q->value); //empilha na lista ordenada
        graph->visited[q->value] = 1; //fala que visitou este nó e tirou da borda

        sortList(graph->adjLists[q->value]); //ordena a lista de adjacência desse nó novo

        Node *r = graph->adjLists[q->value]->first;
        int i = 0;
        while(r != NULL){ //vai passando pela lista de adjacência ordenada

            if(graph->visited[r->value] == 0){ //se ele não está nem nunca esteve na borda
               addNodeBegining(border, r->value); //empilha na borda
               graph->visited[r->value] = -1; //fala que botou na borda
            }
            r = r->next;

            if(border->size > 1){
                i = detectMoreThanOnePathfromAtoB(graph, q->value); //0 se só um caminho, 1 se mais de 1 caminho de A até B
                if(i == 0) verify = 0; //temos same displacement
            }
        }

        free(q);
    }
    freeList(border);
    return verify;
}



void freeGraph(Graph *graph){
    for(int i = 0; i < graph->numVertex; i++) freeList(graph->adjLists[i]);
    free(graph->adjLists);
    free(graph->visited);
    free(graph);
}


void processGraph(Graph *graph, FILE *output){
    int *roots = findRoots(graph);
    cleanVisits(graph);
    int nRoots = findNRoots(graph->numVertex, roots);

    if(detectCycle(graph, roots, nRoots) == 1) fprintf(output, "0 -1\n"); //REVER ISSO AQUI
    else{
        cleanVisits(graph);
        List *sorted = createList();
        int verify = sortGraph(graph, roots[0], sorted);//rever
        if(verify == 1) fprintf(output, "1 ");
        else fprintf(output, "2 ");
        printList(sorted, output);
        freeList(sorted);
    }

    free(roots);
}
