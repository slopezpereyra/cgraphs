#ifndef APIG24_H
#define APIG24_H


#include <stdio.h>
#include <stdlib.h>


//el .h de abajo debe tener definida GrafoSt, u32 y color.
#include "EstructuraGrafo24.h"



//Grafo es un puntero a una estructura GrafoSt, la cual debe estar definida en el .h de arriba

typedef GrafoSt *Grafo;


//construcci'on/destrucci'on

//debe leer desde stdin
Grafo ConstruirGrafo();

void DestruirGrafo(Grafo G);



//funciones para extraer datos del grafo. u32 debe estar definida en el .h de arriba

u32 NumeroDeVertices(Grafo G);
u32 NumeroDeLados(Grafo G);
u32 Delta(Grafo G);


//funciones de extraccion de informacion de vertices 


u32 Grado(u32 i,Grafo G);
color Color(u32 i,Grafo G);
u32 Vecino(u32 j,u32 i,Grafo G);



//funciones con colores


void AsignarColor(color x,u32 i,Grafo  G);
void ExtraerColores(Grafo G,color* Color);
void ImportarColores(color* Color,Grafo  G);



#endif
