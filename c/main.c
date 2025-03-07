/**MIT License
*
*Copyright (c) 2024 Santiago López Pereyra
*
*santiagolopezpereyra@gmail.com
*
*Permission is hereby granted, free of charge, to any person obtaining a copy
*of this software and associated documentation files (the "Software"), to deal
*in the Software without restriction, including without limitation the rights
*to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
*copies of the Software, and to permit persons to whom the Software is
*furnished to do so, subject to the following conditions:
*
*The above copyright notice and this permission notice shall be included in all
*copies or substantial portions of the Software.
*
*The software is provided "as is", without warranty of any kind, express or
*implied, including but not limited to the warranties of merchantability,
*Fitness for a particular purpose and noninfringement. In no event shall the
*authors or copyright holders be liable for any claim, damages or other
*liability, whether in an action of contract, tort or otherwise, arising from,
*out of or in connection with the software or the use or other dealings in the
*software.
 */

//#include <stdio.h>
//#include <assert.h>
//#include "api.h"
//#include <stdbool.h>
//#include "greedy.h"
//#include "search.h"
//#include "queue.h"
//#include "generator.h"
//#include "utils.h"
//#include <time.h>
//
//
//int main(int argc, char* argv[]) {
//    // default seed : srand(123412);
//    int n = atoi(argv[1]);
//    int m = atoi(argv[2]);
//    int seed = atoi(argv[3]); 
//    int method = atoi(argv[4]); // 0 -> Bottom up; 1 -> Top-down
//    srand(seed);
//    char * fileName = "GeneratedGraph.txt";
//    printf("Comenzando la creacion del grafo con nombre %s: n = %d, m = %d, seed = %d.\n", fileName, n, m, seed );     // NOTE printConsole
//
//    Graph *K = NULL;
//    if (method == 1){
//        printf("Generating from Kn\n");
//        K = genFromKn(n, m); //0.24
//    }
//    else{
//        printf("Generating from Prufer\n");
//        K = genFromRandomTree(n, m);
//    }
//    writeGraph(K, fileName);
//    return 0;
//}
