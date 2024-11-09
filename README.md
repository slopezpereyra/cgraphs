# C-Graphs

<div align="center">
    <img src="logo.png" style="width:200px;height:200px;">
</div>

A powerful and lightweight C library for graph theory. A single, common API 
is provided for all kinds of graphs (directed, weighted, flow networks, etc.),
making it easy to learn and use. 


- [API Overview](#api-overview)
    - [Reading and writing a graph](#reading-and-writing-a-graph)
    - [Initializing a graph](#initializing-a-graph)
    - [Modifying an existing graph](#modifying-an-existing-graph)
    - [Graph and vertex attributes](#graph-and-vertex-attributes)
- [Weighted graph algorithms](#weighted-graphs-algorithms)
    - [Dijkstra's algorithm](#dijkstras-algorithm)
    - [Prim's algorithm](#dijkstras-algorithm)
- [Flow network algorithms](#flow-network-algorithms)
    - [Greedy flow](#greedy-flow)
- [Random graph generation](#random-graph-generation)
    - [Bottom-up approach](#bottom-up-approach)
    - [Top-down approach](#top-down-approach)
        - [Correctness of top-down approach](#correctness-of-the-top-down-approach)
    - [Other generation algorithms](#other-generation-algorithms)
- [Contributing](#contributing)

## API Overview 

The fundamental type in this library is the struct `Graph`. A `Graph` of $n$
vertices always has vertices $0, \ldots, n-1$. A `Graph` is of a particular 
type, as indicated by one of the following bit-flags:

- `STD_FLAG` : A "standard" graph, i.e. unweighted, uncolored, undirected.
- `D_FLAG` : A directed graph.
- `W_FLAG` : A weighted graph.
- `COL_FLAG`: A colored graph.
- `CAP_FLAG`: A colored graph.
- `NETFLOW_FLAG`: A flow network.

One may combine these flags with the `|` operator. For example, `D_FLAG |
W_FLAG` specifies a directed weighted graph.

#### Reading and writing a graph

##### The Penazzi format

A `stuct Graph *` pointer may be initialized or read from a `.txt` file in a
special format, which we call the *Penazzi format*. A `.txt` file is in the
Penazzi format if it satisfies the following conditions:

- Its first line is of the form `p n m FLAG`, with `n, m`
natural numbers and `FLAG` one of the bit-flags introduced above.
- The rest of the lines are of the form:
    - `e x y` for standard graphs or directed graphs, indicating that $\\{x,y\\} \in E(G)$ (or $(x, y) \in E(G)$ in the directed case).
    - `e x y w` for weighted graphs, where `w` is the weight $w$ of the edge $\\{x, y\\}$ or $(x, y)$.
    - `e x y w c` for flow networks, where `c` specifies the capacity of the
    edge and `w` its weight (i.e. its current flow).

For instance,

```
p edge 4 3 STD_FLAG
e 0 1
e 1 2 
e 1 3
```

defines the graph

```
     0
     |
     |
     1
    / \
   2   3
```

and 


```
p edge 4 3 W_FLAG
e 0 1 10
e 1 2 20
e 1 3 30
```

specifies


```
        0
        |
        | (10)
        |
        1
  (20) / \ (30)
      2   3
```

##### Read/write operations

To read a graph from a `.txt` in Penazzi format, use `readGraph(char
*filename)` function, which returns a pointer to a `Graph`.

A `Graph *G` can be written in a `.txt` file in Penazzi format sing the
`writeGraph(Graph *G, char *fname)` function.

#### Initializing a graph

To initialize a graph with `n` vertices, `m` edges, use the function

```c 
Graph G* initGraph(n, m, FLAG) // Set FLAG to a valid flag
```

Upon initialization, all edges in `G` are set to `{0, 0}`. No unnecessary
memory is allocated - i.e. memory for the colors, weights, or capacities is
only allocated for colored, weighted, or flow-network graphs.

To set the value of an edge in a `Graph`, call 

```c
void setEdge(Graph* G, u32 i, u32 x, u32 y, u32 *w, u32 *c)
```

This function sets the `i`th edge to `(x, y)`. `w` is either `NULL` (if the
graph is not weighted) or a pointer to a `u32`, if the graph is weighted.
Naturally, $0 \leq i < |E|$ is a restriction.  The `w` and `c` pointers (weight
and capacity) should be NULL if the graph is not weighted (`w`) or is not a
flow network (`c`).

**It is fundamental to call** to call `formatEdges(G)` after dynamically
creating a graph with calls to the `setEdge` function.

For instance, 

```c
Graph *G = initGraph(4, 3, STD_FLAG);
setEdge(G, 0, 0, 1, NULL, NULL);
setEdge(G, 1, 1, 2, NULL, NULL);
setEdge(G, 2, 1, 3, NULL, NULL);
formatEdges(G);
```

also defines the graph 

```
     0
     |
     |
     1
    / \
   2   3
```

#### Modifying an existing graph

A graph initialized with `m` edges allocates the exact amount of memory
required for storing this number of edges. However, new edges can be added with
the function

```c
void addEdge(Graph *G, u32 x, u32 y, u32 *w, u32 *c)
```

Existing edges can be removed with the void 

```c 
void removeEdge(struct Graph *G, u32 x, u32 y) 
```

function. Both functions perform the necessary memory reallocations and update
the graph attributes (e.g. $\Delta(G)$, $d(x)$, $d(y)$). They also  call
`formatEdges(G)` implicitly, so there is no need for an implicit call to this
function afterwards.

#### Graph and vertex attributes

Here are some common graph properties and the function calls they 
relate to.

The number of edges or vertices in a graph can be found with the
`numberOfVertices(Graph *G)` or `numberOfEdges(Graph *G)` functions. The same
is true of the $\Delta(G)$, obtained with `Δ(Graph *G)`.

Since edges in a graph are formatted and ordered, we can find the `j`th
neighbour of vertex `i` with the `neighbour(u32 j, u32 i, Graph G*)`
function. We are assuming the neighbours of a vertex are ordered increasingly. 
For instance, in the graph generated above, the `j=0` (first) neighbour of
vertex `1` is `2`, and the `j=1` neighbour of vertex `1` is `3`.

If the graph is directed, the `j`th neighbour is understood to be the 
`j`th *target*, i.e. the neighbours of a vertex are those vertices it 
leads to.

The `bool isNeighbour(u32 x, u32 y, Graph *G)` returns `true` if $\{x, y\} \in
E(G)$ and `false` otherwise.

The degree of vertex `i` can be found with `degree(u32 i, Graph *G)`. Again, if
the graph is directed, the degree is taken to be the number of vertices the
vertex leads to. To find the number of vertices which lead into the vertex, use
`inDegree(u32 i, Graph *G)`.

The color of a vertex be obtained or set with the `getColor(u32 i, Graph G*)`
or `setColor(color x, u32 i, Graph *G)` functions. If a graph has not been
colored, the color of all vertices is set to zero.

## Weighted graph algorithms

#### Dijkstra's algorithm

The library provides an implementation of Dijkstra's algorithm to find the
shortest distance, from a starting vertex $s$, to all vertices $v \in V(G)$.  
The function 

```c 
u32 *dijkstra(u32 s, Graph *G){
```

returns an array $D$ of `u32` integers s.t. $D[i]$ is the minimum distance 
from $s$ to $i$ in $G$.

#### Prim's algorithm

The library provides an implementation of Prim's algorithm to find a 
minimum spanning tree (MST) of a weighted graph $G$. A minimum spanning 
tree $T$ of $G$ is a spanning tree $T \subseteq G$ that minimizes the 
sum of the edge weights.

The function 

```c
Graph *prim(Graph *G, u32 startVertex) {
```

returns a pointer to a `Graph`, and the `Graph` pointed to is the found MST of
`G`.

## Flow network algorithms

The flag `NETFLOW_FLAG` specifies that a `Graph` is a flow network. 

A flow network is formally a $5$-uple $(V, E, c, s, t)$, with  $c : E \mapsto
\mathbb{N}$ and $s, t \in V$. ($c$ could be a mapping into any subset of $\mathbb{R}$, but this
library restricts itself to "integer networks"). 

The weight of each edge $e \in E$ is understood in this context to represent
its current flow $f(e) \in [0, c(e)]$, and hence the usual functions
(`getEdgeWeight, setEdgeWeight`, etc.) should be use to manipulate $f$.

A flow network can be read from the Penazzi format by setting the flag as
`NETFLOW_FLAG` and adding the capacity next to the weight of each edge. For instance, 

```
p edge 6 8 NETFLOW_FLAG
e 0 1 0 10
e 0 2 0 20
e 1 3 0 10
e 1 4 0 5
e 2 3 0 5
e 2 4 0 5
e 3 5 0 10 
e 4 5 0 10
```

specifies a network with $f$ initialized to zero and capacities $10, 20, 10,
\ldots$ for the edges.

#### Greedy flow 

The simplest approach to finding a flow in a network is to greedily find
non-saturated paths from the source $s$ to the sink $t$. A path 

$$s = v_0 \to v_1 \to \ldots \to v_{k-1} \to v_k = t$$ 

is non-saturated if $f(\overrightarrow{v_i v_{i+1}}) <
c(\overrightarrow{v_i{v_{i+1}}})$ for $i = 0, \ldots, k-1$. Upon finding such path, the algorithm
increases the flow through that path by the maximum value which does not
surpass the remaining capacity of any edge. The algorithm continues until no
more saturated paths exist.

The greedy flow algorithm has some nice properties:

- It always produces a valid flow.
- It always halts, since it saturates at least an edge per iteration, and
saturated edges are never re-emptied.
- Its complexity is $O(m^2)$, since it performs $O(m)$ iterations, each of
which has complexity $O(m)$.

The downside is that the flow found is not necessarily maximal.

To find a flow $f$ using the greedy flow algorithm, assuming you have defined 
a flow network `Graph *N` with the `NETFLOW_FLAG`, call either

```c
u32 flowValue = greedyFlow(N, s, t, flowBFS)
```

or 

```c
u32 flowValue = greedyFlow(N, s, t, flowDFS)
```

The two calls differ in the way they find non-saturated paths from $s$ to $t$
(with BFS or DFS).  

The function $(a)$ returns the value of the flow found and $(b)$ updates the
flow (weight) of each edge in the `N`. 


## Random graph generation 

Two approaches are given for generating *necessarily connected* graphs of $n$
vertices and $m$ edges. Two approaches are given in this library.

#### Bottom-up approach

The *bottom-up approach* consists in generating a random Prufer sequence and
from it a random tree of $n$ vertices. The spanned tree is extended randomly
with new edges until $m$ edges exist. To generate a random graph using this 
method, call 

```c
Graph *G = genFromRandomTree(n, m);
```

assuming `n, m` are defined integers.

A formal analysis of this algorithm reveals that its complexity is $O(n^2)$,
and it should be obvious that it is particularly fast (and distant from the
$n^2$ bound) for sparse graphs. For a detailed analysis of its complexity,
see [this link](https://slopezpereyra.github.io/2024-07-08-RanGraphGen/).


> **Note**: Some graphs of $n$ vertices, $m$ edges, have more spanning trees than 
others. This entails `genFromRandomTree` *does not* sample uniformly from the 
space of all possible such graphs - i.e. it is biased towards graphs with 
many spanning trees, as opposed to graphs with fewer spanning trees.

#### Top-down approach

The *top-down* approach consists in generating a $K_n$ and the random removal
of edges in the graph. This involves some extra complexity: while adding edges
to a connected graph cannot disconnect it, removing edges from a graph may do
so. Thus, some extra cost comes with preserving the connectivity invariant. 
As a benefit, however, this procedure does sample all possible graphs of $n$
vertices, $m$ edges uniformly.

To use this algorithm, call 

```c
Graph *G = genFromKn(n, m)
```

assuming `n`, `m` are integers.

The algorithm is $O(n^4)$, or more precisely $O(n^4 - n^2m)$. (Recall that $m$
here is *not* the number of edges in a $K_n$ but the desired number of edges in
the generated graph). In practice, its complexity is much better, as observed 
in a [more detailed analysis of its complexity](https://slopezpereyra.github.io/2024-07-08-RanGraphGen/).
In that same link, it is also proven that the algorithm is unbiased, i.e. 
that it samples random connected graphs with uniformity.

#### Other generation algorithms 

There are simpler generating functions provided:

- A function `genFromRandomTreeUnbound(u32 n)`, which uses the *bottom-up* approach 
without specifying a desired number of edges, instead deciding it randomly.
- A function `randomTree(u32 n)`, which generates a random tree of `n` vertices,
and is effectively equivalent to `genFromRandomTree(n, n - 1)`.
- A function `fromPruferSequence(u32* seq, u32 seq_len)`, which generates 
a random tree from a Prufer sequence `seq` of length `seq_len`.

## Contributing

Contributions to *C-Graphs* are welcome! Please fork the repository, create a feature branch, and submit a pull request.

---

## License

*C-Graphs* is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.

