
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "api.h"
#include "greedyflow.h"

void test_greedyflow(){

    Graph *G = readGraph("graphs/greedyflow.txt");
    assert(G != NULL);
    printGraph(G);

    greedyFlow(G, 0, 5);

    printGraph(G);


}

int main(){
    test_greedyflow();
}
