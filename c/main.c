#include <stdio.h>
#include <assert.h>
#include "api.h"
#include <stdbool.h>
#include "greedy.h"
#include "search.h"
#include "queue.h"
#include "generator.h"
#include "utils.h"
#include <time.h>


int main(int argc, char* argv[]) {
    // default seed : srand(123412);
    int n = atoi(argv[1]);
    int m = atoi(argv[2]);
    int seed = atoi(argv[3]); 
    int method = atoi(argv[4]); // 0 -> Bottom up; 1 -> Top-down
    srand(seed);
    char * fileName = "GeneratedGraph.txt";
    printf("Comenzando la creacion del grafo con nombre %s: n = %d, m = %d, seed = %d.\n", fileName, n, m, seed );     // NOTE printConsole

    Graph *K = NULL;
    if (method == 1){
        printf("Generating from Kn\n");
        K = genFromKn(n, m); //0.24
    }
    else{
        printf("Generating from Prufer\n");
        K = genFromRandomTree(n, m);
    }
    writeGraph(K, fileName);
    return 0;
}
