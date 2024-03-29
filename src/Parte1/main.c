#include <stdio.h>
#include "APIG24.h"

int main() {
    // clock_t t;
    // t = clock();
    printf("Comenzando la creacion del grafo.\n");     // NOTE PrintConsole
    Grafo G = ConstruirGrafo();
    if (G != NULL) {
        printf("Comenzando descripción del grafo.\n"); // NOTE PrintConsole
        //ImprimirGrafo(G);                              // NOTE PrintConsole

        // PRUEBAS VECINO //
        // u32 j = 3; // y
        // u32 i = 3; // x
        // ProbarVecino(j, i, G);
        // END PRUEBAS //

        printf("Destruyendo grafo...\n"); // NOTE PrintConsole
        DestruirGrafo(G);
    } else {
        printf("Error construyendo el grafo.\n");
    }
    // t = clock() - t;
    // double time_taken = ((double)t) / CLOCKS_PER_SEC; // in seconds
    // printf("main() took %f seconds to execute \n", time_taken);
    return 0;
}
