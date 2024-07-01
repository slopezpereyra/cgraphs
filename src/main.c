#include <stdio.h>
#include "APIG24.h"
#include "greedy.h"
#include "search.h"

int main() {
    // clock_t t;
    // t = clock();
    printf("Comenzando la creacion del grafo.\n");     // NOTE PrintConsole
    Graph G = BuildGraph();
    if (G != NULL) {
        printf("Coloreando el grafo con orden natural.\n");
        u32* order = NaturalOrder(G);
        u32 gr = Greedy(G, order);
        printf("Comenzando descripción del grafo.\n"); // NOTE PrintConsole
        PrintGraph(G);                              // NOTE PrintConsole
        printf("\nA coloring with χ(G) = %d was found\n", gr);
        printf("\n\n");
        printf("\nRunning BFS from vertex 0.\n");
        Graph B = BFS(G, 3);
        printf("\nDescribing BFS graph.\n");
        PrintGraph(B);                              // NOTE PrintConsole
        printf("Destruyendo grafos...\n"); // NOTE PrintConsole
        DumpGraph(G);
        DumpGraph(B);
    } else {
        printf("Error construyendo el grafo.\n");
    }
    return 0;
}
