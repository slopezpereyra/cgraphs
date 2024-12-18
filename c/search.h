#include "graphStruct.h"
#include "insertionArray.h"

Graph *BFS(Graph *G, u32 s);
Graph *DFS(Graph *G, u32 s);
bool BFSSearch(Graph *G, u32 s, u32 target);
u32 *DFSSearch(Graph *G, u32 s, u32 target);
bool isConnected(Graph *G);
Graph *_TreeFromInsertionArray(InsertionArray *insertionArray,
                               u32 insertionArrayLength, u32 n);
