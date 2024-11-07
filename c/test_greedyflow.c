
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "api.h"
#include "greedyflow.h"

void test_greedyflow(){

    Graph *G = readGraph("graphs/network.txt");
    printGraph(G);
    assert(G != NULL);

    greedyFlow(G, 0, 9, flowBFS);


    Graph *W = readGraph("graphs/network.txt");
    assert(W != NULL);

    printf("Attempting FLOW DFS\n");
    greedyFlow(W, 0, 9, flowDFS);
    printGraph(W);
    printGraph(G);

}

int main(){
    test_greedyflow();
}
