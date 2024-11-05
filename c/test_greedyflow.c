
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
    printGraph(G);


    Graph *W = readGraph("graphs/greedyflow.txt");
    assert(W != NULL);

    printf("Attempting FLOW DFS\n");
    greedyFlow(W, 0, 5, flowDFS);
    printGraph(W);

}

int main(){
    test_greedyflow();
}
