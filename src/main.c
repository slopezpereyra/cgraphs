#include <stdio.h>
#include <assert.h>
#include "APIG24.h"
#include <stdbool.h>
#include "greedy.h"
#include "search.h"
#include "queue.h"
#include "generator.h"
#include "utils.h"

int main() {
    // clock_t t;
    // t = clock();
    printf("Comenzando la creacion del grafo.\n");     // NOTE printConsole
    Graph G = buildGraph();
   // Graph C = genConnectedGraph(10, 30);
    if (G != NULL) {
        dumpGraph(G);
//        Graph K = genCompleteGraph(100);
        Graph K = genConnectedGraphFromKn(100, 4900); //0.24
        //Graph K = genCGraph(100, 4950); //0.40

        dumpGraph(K);
        //Graph K = genConnectedGraphFromKn(6, 10);
        //printGraph(K);
    }
    return 0;
}
