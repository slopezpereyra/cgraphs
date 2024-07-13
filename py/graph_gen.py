import random
import networkx as nx
import matplotlib.pyplot as plt
from collections import deque, Counter
from itertools import chain

def read_colors(filename):
    with open(filename, 'r') as file:
        lines = file.readlines()

    C = []

    for line in lines:
        line = line.strip()
        value = int(line)
        C.append(value)

    return C


def neighbours(edges, x, n, degrees):
    x_index = int(x*n - (x*(x+1))/2)
    return [edges[x_index + i][1] for i in range(degrees[x])]

def read_edges(file_path):
    edges = set()  # Using a set to track unique edges
    unique_edges = []  # List to store the unique edges

    with open(file_path, 'r') as file:
        for line in file:
            if line.startswith('e'):
                _, node1, node2 = line.split()
                node1, node2 = int(node1), int(node2)
                edge = tuple(sorted((node1, node2)))
                
                if edge not in edges:
                    edges.add(edge)
                    unique_edges.append((node1, node2))

    return unique_edges

def sort_tuples(tuples_list):
    return sorted(tuples_list, key=lambda tup: (tup[0], tup[1]))

def extend_tuples(tuples_list):
    unique_numbers = set()
    for x, y in tuples_list:
        unique_numbers.add(x)
        unique_numbers.add(y)
    return list(unique_numbers)

file_path = '100-150.txt'
#C = read_colors('graphs/improvedColors.txt')
E = read_edges(file_path)
V = extend_tuples(E)
V = sorted(V)
print(V)

##E = gen_graph(50, 500)
G = nx.Graph()
for v in V:
    G.add_node(v)

for e in E:
    G.add_edge(e[0], e[1])

##
##
nx.draw(G, with_labels=True, font_weight='bold')
plt.show()
#
#nx.draw(G)
#plt.show()


