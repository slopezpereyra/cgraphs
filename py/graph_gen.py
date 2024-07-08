import random
import networkx as nx
import matplotlib.pyplot as plt
from collections import deque, Counter
from itertools import chain

def gen_kn(n):
    
    e = []
    k = 0
    for i in range(n):
        for j in range(1+i, n):
            e.append((i, j))
        k += 1

    if  len(e) != n*(n-1)/2:
        raise(ValueError)

    return(e)

# Always smallest vertex adds greatest vertex
# The index of edge x ~> y is given by:

# x neighbors begin at:
#    
#    (n-i) for 
# 
# (n-1) for 0... 
# (n - 2) for 1...
# (n - 3) for 2... 
# 
# So 1 starts at (n-1) 
# And 2 starts at (n-1) + (n-2) 

# In general, vertex i begins at (n-1)+(n-2) + ... + (n-i)
# = in - (1 + 2 + ... + i)
# = in - (i(i+1)/2)
def edge_to_index(x, y, n):
    x_index = int(x*n - (x*(x+1))/2)
    return x_index + (y - ( x + 1 ))

def neighbors(edges, x, n, degrees):
    x_index = int(x*n - (x*(x+1))/2)
    return [edges[x_index + i][1] for i in range(degrees[x])]


def bfs(edges, n, start, target, neighbors):
    visited = [False] * n
    queue = deque([start])
    visited[start] = True

    while queue:
        node = queue.popleft()

        for neighbor in neighbors[node]:
            if neighbor == target:
                return True
            if node < neighbor:
                index = edge_to_index(node, neighbor, n)
            else:
                index = edge_to_index(neighbor, node, n)

            if index < len(edges) and edges[index] != 0 and not visited[neighbor]:
                queue.append(neighbor)
                visited[neighbor] = True
    
    return False




def gen_graph(n, m):

    k = 0

    if (m < (n-1)):
        raise(ValueError)
    
    E = gen_kn(n)
    M = len(E)
    degrees = [(n-1) for _ in range(n)]
    chosen = []
    indexes = []
    neighbors = [ [i for i in range(n) if i != j] for j in range (n)]

    while M > m:
        k+=1 
        v, w, = 0, 0
        # Select an edge
        while v == w or (degrees[v] == 1 or degrees[w] == 1) or [v, w] in chosen:
            v, w = random.randint(0, n-1), random.randint(0, n-1)


        x = min(v, w)
        y = max(v, w)

        xy_index = edge_to_index(x, y, n)
        if xy_index in chosen:
            continue
#        E_prime = [e for e in E if e != (v, w)]
#        neighbors[v].remove(w)
#        neighbors[w].remove(v)
#        if not bfs(E_prime, n, x, y, neighbors):
#            print("Could not reach... backtracking")
#            continue
        chosen.append(xy_index)
        degrees[v] -= 1 
        degrees[w] -= 1

        indexes.append(xy_index)
        M -= 1

    for index in sorted(indexes, reverse=True):
        del E[index]

    return E

def from_prufer_sequence(sequence):
    E = []
    n = len(sequence) + 2
    degree = Counter(chain(sequence, range(n)))
    T = nx.empty_graph(n)
    # `not_orphaned` is the set of nodes that have a parent in the
    # tree. After the loop, there should be exactly two nodes that are
    # not in this set.
    not_orphaned = set()
    index = u = next(k for k in range(n) if degree[k] == 1)
    for v in sequence:
        # check the validity of the prufer sequence
        E.append( (u, v) )
        not_orphaned.add(u)
        degree[v] -= 1
        if v < index and degree[v] == 1:
            u = v
        else:
            index = u = next(k for k in range(index + 1, n) if degree[k] == 1)
    # At this point, there must be exactly two orphaned nodes; join them.
    orphans = set(T) - not_orphaned
    u, v = orphans
    E.append( (u, v) )
    return(E)


E = from_prufer_sequence([0, 6, 2, 6, 4])
    
#E = gen_graph(50, 500)
G = nx.Graph()
for e in E:
    G.add_edge(e[0], e[1])
#
#
#
#subax1 = plt.subplot(121)
nx.draw(G, with_labels=True, font_weight='bold')
plt.show()
#
#nx.draw(G)
#plt.show()

