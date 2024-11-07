
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "api.h"
#include "greedyflow.h"

void test_greedyflow(){

    Graph *G = readGraph("graphs/greedyflow.txt");
    assert(G != NULL);

    greedyFlow(G, 0, 5, flowBFS);


    Graph *W = readGraph("graphs/greedyflow.txt");
    assert(W != NULL);

    printf("Attempting FLOW DFS\n");
    greedyFlow(W, 0, 5, flowDFS);
    printGraph(W);
    printGraph(G);

}

int main(){
    test_greedyflow();
}
