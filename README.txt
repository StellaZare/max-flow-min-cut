## Problem

Consider a directed edge-weighted graph with real value edge weights. 
This *graph* G has a finite set of *vertices* $(V)$ and a finite set of *edges* $(E)$. Each edge can be denotes as $(u,v)\in E$ such that  $u,v \in V$. Each edge $(u,v)$ is then labelled with a real value *capacity* $c(u,v) > 0$. Lastly, there are 2 distinct vertices $s, t \in V$ labelled as the *source* and *sink* vertices respectively.

A *cut* of a graph is the partitioning of  vertices into 2 disjoint sets, let call these $S$ and $T$.  An *st-cut* is a cut such that the $s \in S$ and the $t \in T$. The cut edges of the graph are edges $(u,v) \in E$ such that one end-point is in $S$ and the other is in $T$. The capacity of an st-cut is the sum of the capacities of its cut edges.

A *flow* on a network is a labelling of the edges with real values such that:
1. the flow on each edge is a real value greater than zero and bounded by the capacity of the edge
2. for all vertices (except $s$ and $t$) the in-coming flow is equal to the outgoing flow 
The flow of an st-cut is the sum of the flows along the cut edges from $S$ to $T$, minus the sum of the flows along the cut edges from $T$ to $S$. 

The max-flow min-cut problem aims to find the st-cut such that the capacity along no other cut is smaller, and determine the flow along the cut. This will be the maximum flow of the entire network. 

## Solution

The Ford-Fulkerson class of algorithms can be applied to solve the maximum flow problem. An important instance of this class is the Edmonds-Karp algorithm. This algorithm is one of the first to solve the maximum flow problem in polynomial time for the general case of networks with real-valued capacities[1]. 

The algorithm begins by constructing the *residual network* $G_f = (V_f, E_f)$ from the input graph $G = (V,E)$ such that:
1. $V_f = V$
2. For each $(u,v) \in E$ with $c(u,v) = C$, we have $(u,v) \in E_f$ with  $c(u,v) = C$  and $(v,u) \in E_f$ with  $c(u,v) = 0$ 

At each iteration, the algorithm attempts to find an *augmenting path* from source to sink in the residual network. The Edmonds-Karp algorithm specifically uses Breadth First Search to find the shortest path from $s$ to $t$ each time. 

If an augmenting path is found, the residual network is "augmented" with the minimum flow along the augmenting path. Then the maximum flow of the network is increased accordingly. 

The pseudocode for the Edmonds-Karp algorithm is as follows:
```
On input G the graph, s source vertex and t sink vertex

Endmonds-Karp(G, s, t)
	Initialize the flow f as zero
	Construct the residual network
	while(there exists a path P from s to t in the residual network) do:
		Find the minium flow available along the path
		Modify the residual network accordingly
		Increment f 
	return f
```

## Command line Parameters
The program accepts optional command line arguments to specify the edge weight type of the input graph as well as provide additional information about the partitioning of the st-cut.

For a usage breakdown you can run the program as follows
```
./main -h
```

By default (without any command line arguments), the program assumes real valued edge weights and prints only the maximum flow achievable by the input graph.
The default behaviour can be executed using the following command
```
./main
```

To specify an edge weight type explicitly, run the program with the "-i" option for integer edge weight or the "-r" for real valued edge weights.
Note that if both "-i" and "-r" are passed in the "-r" takes precedence and the graph will be initialized with real valued edge weights.
```
./main -r or ./main -i
```

To print the list of vertices in each partition of the st-cut, run the program with the "-print_partitions" option.
```
./main -print_partitions
```

## Input Format 

The program reads its input from standard in and expects it in the following format. Any deviation from this format may result in undefined behaviour.
The first line expects 3 integer values:
1. the number of vertices in the graph
2. the index of the source vertex 
3. the index of the sink vertex or default value 0
Note: If the source and sink vertices are set to 0 the values are defaulted to 0 and n-1 respectively where n is the number of vertices in the graph.

The program then expects a direct edge weighted graph in adjacency matrix format where the non-zero entry at row i and column j holds the weight of the directed edge going from vertex i to vertex j.

## Example Input

So a potential input to the program would be:
```
6 0 0
0 7 0 0 4 0
0 0 5 3 0 0 
0 0 0 0 0 8
0 0 3 0 0 5
0 3 0 2 0 0 
0 0 0 0 0 0
```
Running the program with this input using the "-i" and "-print_partitions" options yields the following output:
```
Partition 1:
    Vertex 0
    Vertex 1
    Vertex 4
Partition 2:
    Vertex 2
    Vertex 3
    Vertex 5
Maximum flow is 10
```

## Implementation

The implementation of this program is spread across 3 files:
1. app/main.cpp 
2. include/graph.hpp
3. include/maxflow_mincut.hpp

### main.cpp
This file is the primary executable of the program and relies on the contents of graph.hpp and maxflow_mincut.hpp to do its job.
The main function first parses command line arguments to determine the program requirements. Then initializes a DirWeightedGraph object templated with the desired edge weight type.
The main function uses the read_adjacency_matrix() function of the DirWeightedGraph class to read and the input graph from standard input. Then uses the get_residual_graph() function and the copy constructor of the DirWeightedGraph class to initialize the residual graph object.
Lastly, the main function calls the max_flow_min_cut() function in the maxmin namespace to calculate the maximum flow; and the rec_dfs() to get information about the st-cut partitions.
The main function then outputs the required information to standard out.

### graph.hpp
This file houses the DirWeightedGraph templated class definition. 
The DirWeighted class stores the graph internally as an adjacency list using a vector of size n, where n is the number of vertices in the graph; and index i of the vector stores a vector of pair objects representing the outgoing edges of vertex i. 
ie. a directed edge from vertex i to j with weight w in the graph is represented as a pair {i, w} at index i of the adjacency list vector.
This structure was chosen to reduce the space complexity on large sparse graphs and improve the runtime for certain operations.

### maxflow_mincut.hpp
This file contains the function used to determine the maximum flow of the graph and the partitions of the st-cut. The file contains 3 function definitions templated in the graph type used (ie. edge weight type of the graphs may differ)

#### maxflow_mincut()
Inputs:
- src - index of the source vertex in the residual graph
- sink - index of the sink vertex in the residual graph
- graph - reference to the residual graph object
Returns: The maximum flow of the graph

This function implements the Edmonds-Karp algorithm by first search for an augmenting path from src to sink in the residual graph; using the path vector to retrace the path; augmenting the edges along the path with the minimum flow value; then incrementing the overall flow accordingly.
Once there are no more augmenting paths in the residual graph the function exits the loop and returns the flow value.

#### get_augmenting_path()
Inputs:
- src - index of the source vertex in the residual graph
- sink - index of the sink vertex in the residual graph
- graph - reference to the residual graph object
- path - reference to a vector modified with the path information
Returns: True if a path exists from src to sink and False otherwise

This is a helper function for maxflow_mincut() and determines if an augmenting path exists in the graph. This done using the Breadth First Search approach where the visited vector internally tracks the visited vertices and the path vector is used to track the path from src to sink.

#### rec_dfs()
Inputs: 
- src - index of the source vertex in the residual graph
- graph - reference to the residual graph object
- reachable - reference to vector modified with the reachability information
Returns: void

This function is used by main to determine the contents of each partition of the st-cut. It uses a recursive Depth First Search algorithm to find all the vertices reachable from src in the residual graph after the graph has been optimized for maximum flow. All reachable vertices will be vertices in the S-partition of the st-cut.

## Scalability

Certain design choices were made to keep the program scalable. 
1. The logic to read an adjacency matrix was moved out of the constructor of DirWeightedGraph and encapsulated at a member function "read_adjacency_matrix" to allow for the implementation of other functions to read inputs in different formats (ie. adjacency list)
2. The "read_adjacency_list" function in DirWeightedGraph takes an std::istream object as a parameter therefore can be used to read input from multiple stream types(files, strings etc.)
3. The "print_graph" function in DirWeightGraph takes an std::ostream object as a parameter and therefore can be used with multiple stream types(files, strings etc.)
4. The templated DirWeightedGraph object can be used to create graphs with any real value type (integer, float, double, long double etc.) so the program can be scaled to allow for all these types.

## Sources

J. C. Blanchette and S. Merz, “Formalizing the Edmonds-Karp Algorithm,” in _Interactive Theorem Proving_, vol. 9807, Switzerland: Springer International Publishing AG, 2016, pp. 219–234. doi: 10.1007/978-3-319-43144-4_14.

Little, R. (2021). Algorithms and Data Structures II, Lecture 15-Maxflow-Mincut [PDF Slides].

Ford, L. R., Fulkerson, D. R., Ford, L. R., & Fulkerson, D. R. (2015). _Flows in Networks_. Princeton University Press,. https://doi.org/10.1515/9781400875184