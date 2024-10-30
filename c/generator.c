/**
 * @file generator.c
 * @brief Graph generation functions.
 */

#include <stdbool.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "utils.h"
#include "api.h"
#include "search.h"

/**
 * @brief Generates a complete graph with a specified number of vertices.
 * @param n Number of vertices in the graph.
 * @return Pointer to the generated complete graph.
 */
struct Graph *genCompleteGraph(u32 n) {
    struct Graph *G = initGraph(n, n*(n-1)/2);
    u32 edgeIndex = 0;
    for (u32 i = 0; i < n; i++) {
        for (u32 j = 1+i; j < n; j++) {
            setEdge(G, edgeIndex, i, j);
            edgeIndex++;
        }
    }
    formatEdges(G);
    return G;
}


/**
 * @brief Generates a tree graph from a Prufer sequence.
 * @param seq Array representing the Prufer sequence.
 * @param seq_len Length of the Prufer sequence.
 * @return Pointer to the generated tree graph.
 */
struct Graph *fromPruferSequence(u32* seq, u32 seq_len) {
    u32 n = seq_len + 2;
    u32* degrees = genArray(n);
    struct Graph *T = initGraph(n, 0); 

    for (u32 i = 0; i < n; i++) {
        degrees[i] = 1;
    }

    for (u32 i = 0; i < seq_len; i++) {
        u32 v = seq[i];
        degrees[v]++;
    }

    for (u32 i = 0; i < seq_len; i++) {
        u32 v = seq[i];
        for (u32 j = 0; i < n; j++) {
            if (degrees[j] == 1) {
                addEdge(T, min(v, j), max(v, j));
                degrees[v]--;
                degrees[j]--;
                break;
            }
        }
    }

    u32 u = 0, v = 0;
    for (u32 i = 0; i < n; i++) {
        if (degrees[i] == 1) {
            if (u == 0) {
                u = i;
            } else {
                v = i;
                break;
            }
        }
    }

    addEdge(T, min(u, v), max(u, v));
    free(degrees);
    return T;
}

/**
 * @brief Generates the adjacency lists for each vertex in the graph.
 * @param G Pointer to the graph.
 * @return Array of adjacency lists for each vertex.
 *
 * @note Its common to use Γ(v) to denote {w : {v, w} ∈ E(G)}.  This function
 * can be understood as generating [ Γ(v₁), … , Γ(vₙ) ], which explains 
 * its name.
 */
u32** genGammas(struct Graph *G) {
    u32 n = G->n;
    u32** Γ = (u32**)calloc(n, sizeof(u32*));
    if (Γ == NULL) {
        printf("Error: calloc failed\n");
        exit(1);
    }
    for (u32 i = 0; i < numberOfVertices(G); i++) {
        u32 d = degree(i, G);
        Γ[i] = (u32*)malloc(d * sizeof(u32));
        for (u32 j = 0; j < d; j++) {
            Γ[i][j] = neighbour(j, i, G);
        }
    }
    return Γ;
}

/**
 * @brief Generates complement adjacency lists for each vertex in the graph.
 * @param G Pointer to the graph.
 * @return Array of complement adjacency lists for each vertex.
 *
 * @note Its common to use Γ(v) to denote {w : {v, w} ∈ E(G)}.  This function
 * can be understood as generating [ Γᶜ(v₁), … , Γᶜ(vₙ) ], which explains 
 * its name.
 */
u32** genGammaComplements(struct Graph *G) {
    u32 n = G->n;
    u32** S = (u32**)calloc(n, sizeof(u32*));
    if (S == NULL) {
        printf("Error: calloc failed\n");
        exit(1);
    }
    for (u32 i = 0; i < numberOfVertices(G); i++) {
        u32 d = degree(i, G);
        S[i] = (u32*)malloc((n-d-1) * sizeof(u32));
        u32 jIndex = 0;
        for (u32 j = 0; j < n; j++) {
            if (isNeighbour(j, i, G) || i == j) {
                continue;
            }
            S[i][jIndex] = j;
            jIndex++;
        }
    }
    return S;
}

/**
 * @brief Generates a random tree with the specified number of vertices.
 * @param n Number of vertices in the tree.
 * @return Pointer to the generated random tree.
 */
struct Graph *randomTree(u32 n) {
    u32* randSequence = genArray(n-2);
    for (u32 i = 0; i < n - 2; i++) {
        randSequence[i] = generate_random_u32_in_range(0, n-1);
    }

    struct Graph *T = fromPruferSequence(randSequence, n-2);
    free(randSequence);
    return T;
}

/**
 * @brief Generates a connected graph with a random number of edges up to an unbounded limit.
 * @param n Number of vertices in the graph.
 * @return Pointer to the generated connected graph.
 */
struct Graph *genCGraphUnbound(u32 n) {
    struct Graph *T = randomTree(n);
    u32** S = genGammaComplements(T);
    u32 k = generate_random_u32_in_range(0, n*(n-1)/2 - numberOfEdges(T) - 1);
    u32* nCandidates = genArray(n);
    u32* vMatchable = genArray(n);
    for (u32 i = 0; i < n; i++) {
        nCandidates[i] = n - degree(i, T) - 1;
        vMatchable[i] = i;
    }

    u32 nMatchable = n;
    for (u32 j = 0; j < k; j++) {
        u32 v, vIndex;
        while (true) {
            vIndex = generate_random_u32_in_range(0, nMatchable - 1);
            v = vMatchable[vIndex];
            if (nCandidates[v] == 0) {
                removeElement(&vMatchable, &nMatchable, vIndex);
                continue;
            }
            break;
        }
        u32 i = generate_random_u32_in_range(0, nCandidates[v] - 1);
        u32 w = S[v][i];
        removeElement(&( S[v] ), &( nCandidates[v] ), i);
        removeTargetElement(S[w], &( nCandidates[w] ), v);
        addEdge(T, min(v, w), max(v, w));
    }
    free(nCandidates);
    for (u32 i = 0; i < numberOfVertices(T); i++) {
        free(S[i]);
    }
    free(S);
    free(vMatchable);
    return T;
}

/**
 * @brief Generates a connected graph with a specified number of edges.
 * @param n Number of vertices in the graph.
 * @param m Number of edges in the graph.
 * @return Pointer to the generated connected graph.
 */
struct Graph *genCGraph(u32 n, u32 m) {
    assert(m <= n*(n-1)/2 && m >= n - 1);

    struct Graph *T = randomTree(n);
    u32** S = genGammaComplements(T);
    u32* nCandidates = genArray(n);
    u32* vMatchable = genArray(n);

    for (u32 i = 0; i < n; i++) {
        nCandidates[i] = n - degree(i, T) - 1;
        vMatchable[i] = i;
    }

    u32 nMatchable = n;
    while (numberOfEdges(T) < m) {
        u32 vIndex = generate_random_u32_in_range(0, nMatchable - 1);
        u32 v = vMatchable[vIndex];
        if (nCandidates[v] == 0) {
            removeElement(&vMatchable, &nMatchable, vIndex);
            continue;
        }
        u32 i = generate_random_u32_in_range(0, nCandidates[v] - 1);
        u32 w = S[v][i];
        removeElement(&( S[v] ), &( nCandidates[v] ), i);
        removeTargetElement(S[w], &( nCandidates[w] ), v);
        addEdge(T, min(v, w), max(v, w));
    }
    free(nCandidates);
    for (u32 i = 0; i < numberOfVertices(T); i++) {
        free(S[i]);
    }
    free(S);
    free(vMatchable);
    return T;
}

/**
 * @brief Generates a connected graph by removing edges from a complete graph.
 * @param n Number of vertices in the graph.
 * @param m Number of edges to retain in the graph.
 * @return Pointer to the generated connected graph.
 */
struct Graph *genConnectedGraphFromKn(u32 n, u32 m) {
    assert(m <= n*(n-1)/2 && m >= n - 1);
   
    struct Graph *Kn = genCompleteGraph(n);
    u32** Γ = genGammas(Kn);
    u32* R = genArray(n);
    u32* nCandidates = genArray(n);

    for (u32 i = 0; i < n; i++) {
        R[i] = i;
        nCandidates[i] = n-1;
    }

    u32 nRemovable = n;
    while (numberOfEdges(Kn) > m) {
        u32 vIndex = generate_random_u32_in_range(0, nRemovable-1); 
        u32 v = R[vIndex];
        u32 wIndex = generate_random_u32_in_range(0, nCandidates[v] - 1);
        u32 w = Γ[v][wIndex];

        removeElement(&( Γ[v] ), &( nCandidates[v] ), wIndex);
        removeTargetElement(Γ[w], &( nCandidates[w] ), v);
        
        if (BFSSearch(Kn, v, w)) {
            removeEdge(Kn, min(v, w), max(v, w));
        }
        if (degree(v, Kn) == 1 || nCandidates[v] == 0) {
            removeElement(&R, &nRemovable, vIndex);
        }
        if (degree(w, Kn) == 1 || nCandidates[w] == 0) {
            removeTargetElement(R, &nRemovable, w);
        }
    }
    free(nCandidates);
    free(R);
    for (u32 i = 0; i < numberOfVertices(Kn); i++) {
        free(Γ[i]);
    }
    free(Γ);
    formatEdges(Kn);
    return Kn;
}
