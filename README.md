# C-Graphs

<div align="center">
    <img src="logo.png" style="width:200px;height:200px;">
</div>

*C-Graphs* is a powerful and lightweight C library for (labeled) graph
generation, manipulation, and traversal. It offers implementations of elemental
graph traversal and coloring algorithms, as well as more sophisticated
algorithms for the generation of random connected graphs.

- [API Overview](#api-overview)
    - [Reading and writing a graph](#reading-and-writing-a-graph)
    - [Initializing a graph](#initializing-a-graph)
    - [Modifying an existing graph](#modifying-an-existing-graph)
    - [Graph and vertex attributes](#graph-and-vertex-attributes)
- [Weighted graphs](#weighted-graphs)
    - [Dijkstra's algorithm](#dijkstras-algorithm)
    - [Prim's algorithm](#dijkstras-algorithm)
- [Random graph generation](#random-graph-generation)
    - [Bottom-up approach](#bottom-up-approach)
    - [Top-down approach](#top-down-approach)
        - [Correctness of top-down approach](#correctness-of-the-top-down-approach)
    - [Other generation algorithms](#other-generation-algorithms)
- [Contributing](#contributing)

## API Overview 

The fundamental structure in this library is the `Graph`. A `struct Graph` of
$n$ vertices always has vertices $0, \ldots, n-1$.

Graph data, such as the degree of a vertex or its neighbours, is accessed in
constant or almost constant time in most cases. This makes it possible to
handle extremely large graphs, though at the expense of some extra memory
consumption.

#### Reading and writing a graph

A `stuct Graph *` pointer may be initialized or read from a `.txt` file in a 
special format, which we call the *Penazzi format*. A `.txt` file is in 
the Penazzi format if it satisfies the following conditions:

- Its first line is of the form `p n m FLAG`, with `n, m`
natural numbers and `FLAG` one of the follownig strings:
    - `STD_FLAG` : Specifies that this is a "standard" graph, i.e. unweighted and uncolored.
    - `W_FLAG` : Specifies that this is a weighted graph.
    - `COL_FLAG`: Specifies that this is a colored graph.
- The rest of the lines are of the form `e x y` for standard graphs 
or `e x y w` for weighted graphs. Each `x y` pair is read into an edge,
with weight `w` if the graph is weighted.


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

To read a graph from a `.txt` in Penazzi format, use `readGraph(char *filename)` function, which returns a pointer to a `Graph`.

A `Graph G*` can be written in a `.txt` file in Penazzi format (for
instance, to be read by a graph plotting algorithm) using the
`writeGraph(Graph *G, char *fname)` function.

#### Initializing a graph

To initialize a graph with `n` vertices, `m` edges, use the function

```c 
Graph G* initGraph(n, m, FLAG) // Set FLAG to STD_FLAG, W_FLAG or COL_FLAG, or 
                               // a combination (e.g. W_FLAG | G_FLAG)
```

Upon initialization, all edges in `G` are set to `{0, 0}`. Memory is not
allocated for edge weights nor vertex colors if the weighted/colored flags are
not used. This allows all kinds of graphs to share a common API without using
unnecessary memory.

To add an edge, the function

```c
void setEdge(Graph* G, u32 i, u32 x, u32 y, u32 * w)
```


This function sets the `i`th edge to `(x, y)`, with `w` either `NULL` (if the
graph is not weighted) or a pointer to a `u32`, if the graph is weighted.
Passing a non-null `w` pointer to the function with a non-weighted graph `G` is
undefined behavior and will produce a crash.

**It is fundamental to call** to call `formatEdges(G)` after dynamically
creating a graph with calls to the `setEdge` function.

For instance, 

```c
Graph *G = initGraph(4, 3, STD_FLAG);
setEdge(G, 0, 0, 1, NULL);
setEdge(G, 1, 1, 2, NULL);
setEdge(G, 2, 1, 3, NULL);
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
void addEdge(Graph *G, u32 x, u32 y, NULL)
```

Existing edges can be
removed with the void 

```c 
void removeEdge(struct Graph *G, u32 x, u32 y) 
```


function. Both functions perform the necessary memory reallocations and update
the graph attributes (e.g. $\Delta(G)$, $d(x)$, $d(y)$). They also  call
`formatEdges(G)` implicitly, so there is no need for an implicit call to this
function afterwards.

#### Graph and vertex attributes

The number of edges or vertices in a graph can be found with the
`numberOfVertices(Graph *G)` or `numberOfEdges(Graph *G)` functions. The same
is true of the $\Delta(G)$, obtained with `Δ(Graph *G)`.

Since edges in a graph are formatted and ordered, we can find the `j`th
neighbour of vertex `i` with the `neighbour(u32 j, u32 i, Graph G*)`
function. For instance, in the graph generated above, the `j=0` (first)
neighbour of vertex `1` is `2`, and the `j=1` neighbour of vertex `1` is `3`.


The `bool isNeighbour(u32 x, u32 y, Graph *G)` returns `true` if $\{x, y\} \in
E(G)$ and `false` otherwise.

The degree of vertex `i` can be found with `degree(u32 i, Graph G*)`,
and its color can be obtained or set with the `getColor(u32 i, Graph
G*)` or `setColor(color x, u32 i, Graph *G)` functions. The `color` type
is a mask over `u32`. If a graph has not been colored, the color of all
vertices is set to zero.

## Weighted graphs 

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
$n^2$ bound) for sparse graphs. To see why, consider the following formalization 
of the algorithm:


$$
\begin{align*}
    &\textbf{Input: } n, m\\
    &T := (V, E) = \textbf{genRandomTree}(n)\\
    &S_T := [\Gamma^c(v_1), \ldots, \Gamma^c(v_n)]  \\
    &C := [ |S_T[1]|, \ldots, |S_T|[n]|]  \\
    &V := [1, \ldots, n]   \\
    &n' := n\\
    &\textbf{while } |E(T)| < m \textbf{ do } \\ 
    &\qquad i := \textbf{random}(1, n') \\ 
    &\qquad v := V[i]\\
    &\qquad \textbf{if }  d(v) == n - 1  \textbf{ do } \\ 
    &\qquad \qquad \textbf{deleteAt}(V, i)\\ 
    &\qquad\qquad n' := n' - 1 \\ 
    &\qquad\textbf{else } \\ 
    &\qquad\qquad j = \textbf{random}(1, C[v])\\
    &\qquad\qquad w := S_T[v][j] \\ 
    &\qquad\qquad E(T) := E(T) \cup  \\{ v, w \\} \\
    &\qquad\qquad C[v] := C[v] - 1 \\ 
    &\qquad\qquad \textbf{deleteAt}(S_T[v], j)  \\ 
    &\qquad\qquad\textbf{deleteElement}(S_T[w], v)\\ 
    &\qquad\textbf{fi}\\
    &\textbf{od}\\
    &\textbf{return }
\end{align*}
$$

Generating a tree from a random Prüfer sequence is $O(n^2)$. Forming $S_T$ is
also $O(n^2)$. Within the while loop there are simply index manipulations, so
the complexity of the loop is $\varphi \times O(1) = \varphi$, with $\varphi$
the complexity of the number of iterations.

All iterations add an edge except those where a saturated vertex (i.e. one
connected to all other vertices) is chosen. A saturated vertex may be chosen at
most once. 

$\therefore$ There are $O(n)$ iterations where a saturated vertex is chosen.

Since the rest of the iterations add an edge, their number is fixed: $m- (n-1)$, 
where $(n-1)$ is the number of edges in the spanned tree.

$\therefore$ There are exactly $m -n + 1$ edge-adding iterations.

$\therefore  \varphi = O(n) + O(m - n + 1) = O(n) + O(m) = O(m)$

$\therefore$ The complexity of the algorithm is
$O(n^2) + O(m) = O(n^2)$.

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
the generated graph). To see why, consider the formalization of the algorithm:

$$
\begin{align*}
&(V, E) := \textbf{genKn}(n)\\
&\Gamma := [\Gamma(v_1), \ldots, \Gamma(v_n)]\\
&V_c := [v_1, \ldots, v_n]\\ 
&\textbf{while } |E| \neq m \textbf{do } \\ 
&\quad\quad v = \textbf{randFrom}(V_c) \\ 
&\quad\quad w = \textbf{randomFrom}(\Gamma[v]) \\ 
&\quad\quad \Gamma[v] = \Gamma[v] - \{w\} \\ 
&\quad\quad \Gamma[w] = \Gamma[w] - \{v\} \\ 
&\quad\quad \textbf{if BFSFind}(E - \{v, w\}, v, w) \textbf{ do}  \\ 
&\quad\quad\quad\quad E := E - \{v, w\}\\
&\quad\quad \textbf{fi}  \\ 
&\quad\quad \textbf{if } d(v) = 1 \lor \Gamma[v] = \emptyset \textbf{ do } \\
&\quad\quad\quad\quad V_c := V_c - \{v\} \\ 
&\quad\quad\textbf{fi}  \\ 
&\quad\quad \textbf{if } d(w) = 1 \lor \Gamma[w] = \emptyset \textbf{ do } \\
&\quad\quad\quad\quad V_c := V_c - \{w\} \\ 
&\quad\quad\textbf{fi}  \\ 
&\textbf{od}
\end{align*}
$$

Generating a $K_n$ is $O(n^2)$. The $\textbf{while}$ selects a random vertex
from $V_c$ and attempts to erase one of its edges. There is only one case one
an edge is not removed; namely, when the sampled edge is a bridge. This happens
at most once per bridge. There are at most $n - 1$ bridges in a graph.

$\therefore$ There are $O(n)$ iterations which do not remove an edge.

The remaining iterations will remove an edge and there will be exactly
$\frac{n(n-1)}{2} - m$ of them.

$\therefore$ There are $O(n) + O(\frac{n(n-1)}{2} - m) = O(n^2 - m)$
iterations.

The operations in each iteration are $O(1)$ except BFS search, whose 
complexity is $O(n^2)$.

$\therefore$ The algorithm is $O(n^2) + O(n^2 - m)O(n^2) = O(n^4 - n^2m)$.

In practice the algorithm will perform better than this. The BFS search stops
whenever $w$ is found starting from $v$. This still is asymptotically $O(|E|)$,
but in practice the bound will seldom be reached. Furthermore, BFS is ran over
an increasingly sparser graph. Its asymptotic complexity is given by the number
of edges in the initial $K_n$, but it decreases with each edge-removing
iteration.

#### Correctness of the top-down approach

Proving that the *top-down* algorithm is correct and unbiased requires more
formalization. Let $\mathcal{C}\_{n,m}$ be the set of connected graphs of $n$
vertices, $m$ edges. Let $\mathcal{E}\_{n,m}$ be the class of edges which, if
removed from a $K_n$, produce a graph in $\mathcal{C}\_{n,m}$. Since any $G
\in \mathcal{C}\_{n,m}$ corresponds univocally to a set of edges $W \in
\mathcal{E}\_{n,m}$,

$$
|\mathcal{E}\_{n,m}| = |\mathcal{C}\_{n,m}|
$$

$\therefore$ There is a bijection $f\_{n,m} : \mathcal{E}\_{n,m} \mapsto \mathcal{C}_{n,
m}$ mapping a set of edges to the connected graph generated by removing those
edges from $K_n$.

We shall first prove that our algorithm constructs a $W \in \mathcal{E}\_{n,m}$
and that it computes $f(W)$. Secondly, we shall prove that any $W \in
\mathcal{E}\_{n,m}$ has an equal probability of being constructed.

*(1)* The algorithm iteratively samples and removes edges ensuring that the
connectivity invariant is preserved. It is trivial to see that it removes $k :=\binom{n}{2} - m$ edges. 

Let $S = \\{e_1, \ldots, e_{k}\\}$ be the set of randomly sampled edges, where
$e_i$ was sampled at the $i$th edge-removing iteration. Preserving the
invariant entails that, across iterations, the sampling spaces $E_1, \ldots,
E_r$ from which each $e_i$ was sampled are:

- $E_1 = \\{ e \in W : W \in \mathcal{E}\_{n,m}  \\}$
- $E_2 = \\{ e \in W : W \in \mathcal{E}\_{n,m} \land \\{ e_1 \\}  \subseteq  W  \\}$
- $E_3 = \\{ e \in W : W \in \mathcal{E}\_{n,m} \land \\{ e_1, e_2 \\}  \subseteq  W  \\}$

etc. Thus, the general form is 

$$E_i = \\{ e \in W : W \in \mathcal{E}\_{n,m} \land \\{ e_1, \ldots, e\_{i-1}\\} \subseteq W \\} $$

It follows that $S = \\{ e_1, \ldots, e_k \\} \subseteq W$ for some $W
\in \mathcal{E}\_{n,m}$. But $|S| = |W| = k$. Then $S = W$ and $S \in
\mathcal{E}\_{n,m}$. And since $S$ is the set of removed edges, the algorithm
computes $f(S)$. $\blacksquare$

*(2)* Since there is a bijection between $\mathcal{C}\_{n,m}$ and
$\mathcal{E}\_{n,m}$, a graph is more probable than others if and only if there
is a set $S \in \mathcal{E}\_{n,m}$ that is more probably constructed than
others. This could only be true for two cases: *(1)* An edge or set of edges in
$S$ is more likely to be chosen, or *(2)* $S$ contains more elements than other
members of $\mathcal{E}\_{n,m}$. But *(1)* is impossible if the selection is
random, and *(2)* contradicts that $|S| = \binom{n}{2} - m$ for every $S \in
\mathcal{E}\_{n,m}$. $\blacksquare$

$\therefore$ The algorithm is correct and unbiased.

#### Other generation algorithms 

Aside from the top-down and bottom-up approaches, the library provides:

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

