#include <stdio.h>
#include <assert.h>
#include "APIG24.h"
#include <stdbool.h>
#include "greedy.h"
#include "search.h"
#include "queue.h"
#include "generator.h"
#include "utils.h"
#include <time.h>

int main() {
    // clock_t t;
    // t = clock();
    printf("Comenzando la creacion del grafo.\n");     // NOTE printConsole
    Graph G = buildGraph();
   // Graph C = genConnectedGraph(10, 30);
    if (G != NULL) {
        dumpGraph(G);
//        Graph K = genCompleteGraph(100);
        srand(0);
        Graph K = genConnectedGraphFromKn(50, 49); //0.24
        srand(123412);
        Graph K2 = genCGraph(50, 49); //0.24
        srand(111);
        Graph K3 = genConnectedGraphFromKn(50, 100); //0.24
        srand(123123);
        Graph K4 = genConnectedGraphFromKn(50, 100); //0.24
        //Graph K = genCGraph(100, 4950); //0.40
        writeGraph(K, "50-49a.txt");
        writeGraph(K2, "50-49b.txt");
        writeGraph(K3, "50-49c.txt");
        writeGraph(K4, "50-49d.txt");

        dumpGraph(K);
        dumpGraph(K2);
        dumpGraph(K3);
        dumpGraph(K4);
        //Graph K = genConnectedGraphFromKn(6, 10);
        //printGraph(K);
    }
    return 0;
}
