import networkx as nx

G =  nx.read_edgelist("new_graph.txt", delimiter=',', data=(('weight',float),))
print(nx.minimum_spanning_tree(G).size(weight='weight'))


#with open("vallog.csv", "w") as f:

