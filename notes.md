


# Iterating through edges without repeating


```c
    u32 j = 0; // Index shift per iteration
    for (u32 i = 0; i < 2*numberOfEdges(T); i+=j){
        Edge e = getIthEdge(i, G);
        // Do something with edges and so on
        j = degree(e.x, T) + 1;
    }
```
