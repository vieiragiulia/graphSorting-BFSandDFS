#include "Graph.h"

int main(int argc, char *argv[]){
    if(argc < 3) printf("NUMERO DE ARGUMENTOS INVALIDO, INSIRA NOME DOS ARQUIVOS ENTRADA E SAIDA");
    FILE *input = fopen(argv[1], "r");   if(input == NULL) printf("ERRO AO ABRIR ENTRADA");
    FILE *output = fopen(argv[2], "w");   if(output == NULL) printf("ERRO AO ABRIR SAIDA");


    int V, E;
    fscanf(input, "%d %d", &V, &E);

    Graph *graph = createGraph(V, E);
    readGraph(E, input, graph);
    processGraph(graph, output);
    
    freeGraph(graph);

    fclose(input);
    fclose(output);
    return 0;
}
