#include <stdio.h>
#include <assert.h>
#include "APIG24.h"
#include <stdbool.h>
#include "greedy.h"
#include "search.h"
#include "queue.h"
#include "generator.h"

int main() {
    // clock_t t;
    // t = clock();
    printf("Comenzando la creacion del grafo.\n");     // NOTE PrintConsole
    Graph G = BuildGraph();
   // Graph C = genConnectedGraph(10, 30);
    if (G != NULL) {
        Graph C = genConnectedGraph(300, 1000);
//        printf("Passed\n");
//        PrintGraph(C);

 //       Graph K = genCompleteGraph(10);
 //       PrintGraph(K);
//        Graph B = BFS(K, 0);
//        PrintGraph(B);
//        removeEdge(K, 5, 6);
//        removeEdge(K, 0, 3);
//        removeEdge(K, 0, 9);
//        removeEdge(K, 5, 9);
//        removeEdge(K, 4, 9);
//        B = BFS(K, 0);
//        PrintGraph(B);
//        PrintGraph(K);

//        printf("\n ---------------- Greedy coloring ----------------\n");
//        u32* order = NaturalOrder(G);
//        u32 gr = Greedy(G, order);
//        free(order);
//        printf("\nA coloring with %d colors was found\n", gr);
//        PrintGraph(G);                              // NOTE PrintConsole
//        
//        printf("\nTesting permutations...\n");
//
//        order = reverseOrder(G, gr);
//        gr = Greedy(G, order);
//        free(order);
//        printf("\nA coloring with %d colors was found with reverse order\n", gr);
//        order = cardinalityOrder(G, gr);
//        gr = Greedy(G, order);
//        free(order);
//        printf("\nA coloring with %d colors was found with cardinality order\n", gr);
//        printf("\nPrinting reverse order: \n");
//        order = divisibilityOrder(G, gr);
//        gr = Greedy(G, order);
//        free(order);
//        printf("\nA coloring with %d colors was found with divisibility order\n", gr);
//        printf("\n ---------------- Two color ----------------\n");
//        removeColors(G);
//        u32 x = twoColorable(G);
//        printf("Two colorable: %d\n", x); 
//        printf("\n ---------------- BFS (Root vertex 0) ----------------\n");
//        Graph B = BFS(G, 0);
//        PrintGraph(B);                              // NOTE PrintConsole
//        printf("\n ---------------- DFS (Root vertex 0) ----------------\n");
//        Graph D = DFS(G, 0);
//        PrintGraph(D);                              // NOTE PrintConsole
//        DumpGraph(B);
//        printf("G was dumped, dealing with B...\n"); // NOTE PrintConsole
//        DumpGraph(G);
//        printf("B was dumped, dealing with D...\n"); // NOTE PrintConsole
//        DumpGraph(D);
    } else {
        printf("Error construyendo el grafo.\n");
    }
    return 0;
}
