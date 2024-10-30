# C-Graphs

<div align="center">
    <img src="logo.png" style="width:200px;height:200px;">
</div>

*C-Graphs* is a powerful and lightweight C library for (labeled) graph
generation, manipulation, and traversal. It offers robust implementations of
essential graph algorithms, including search, coloring, and random (connected)
graph generation. This library is suited for researchers, developers, and
anyone working with graph-based data structures in C.

The most interesting algorithms are those for the generation of random
connected graphs, insofar as it is non-trivial to preserve the connectivity
invariant in a stochastic generation process. For a detailed description of
these algorithms see [this article in my
website](https://slopezpereyra.github.io/2024-07-08-RanGraphGen/).

## Features

C-Graphs provides a rich set of graph functionalities:

- **Graph Search Algorithms**: Breadth-First Search (BFS), Depth-First Search (DFS), connectivity checks, and pathfinding.
- **Graph Coloring Algorithms**: Greedy coloring and 2-coloring for bipartite graph checks.
- **Random Connected Graph Generation**: Efficient random graph generation that ensures connectivity.

All algorithms are optimized for performance and compatibility with C programs.



## Contributing

Contributions to *C-Graphs* are welcome! Please fork the repository, create a feature branch, and submit a pull request.

---

## License

*C-Graphs* is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.

---

Happy graphing with *C-Graphs*!

