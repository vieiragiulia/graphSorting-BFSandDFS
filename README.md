# graphSorting-BFSandDFS

graph sorting using DFS and BFS This program solves a graphs problem that is better explained in the documentation (it is in portuguese, but I may translate it later). In sumarry, here we need to know if a directed graph can be ordered, and if yes, if there is only one order or may of them, that means, if it is a list or a tree.

To solve this I used the cycle detecting modification of DFS, to determine whether it can be ordered or not and pure BFS to sort - the original problem asked us to sort the vertex of the same level in a growing order based on it's number, for this task I used Quicksort.

It requires an entry, which is a txt file with the graph's connections written in it the following way: base-node next-node base-node next-node

The output is a number: 0 - it is not possible to sort this graph 1 - it is possible and there is only one way 2 - it possible and there are more than one ways Followed by the final order of the vertex.

This was also a college project.
