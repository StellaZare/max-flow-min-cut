#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <iostream>
#include <vector>
#include <array>

template <class T>
class DirWeightedGraph {
public:
    using WeightType = T;
    using Index = std::size_t;

    // This object is not default constructable 
    DirWeightedGraph() = delete;
    
    /*
        input: size - number of vertices in the graph
        Creates a graph of specified size with no edges

        Precondition: size is strictly greater than 0
    */
    DirWeightedGraph(Index size) : graph{size} {}

    // This object is not copyable or movable
    DirWeightedGraph(const DirWeightedGraph&) = delete;
    DirWeightedGraph(DirWeightedGraph&&) = delete;
    DirWeightedGraph& operator=(const DirWeightedGraph&) = delete;

    /*
        input: src - index of source vertex
               dest - indext of destination vertex
               weight - the weight of the edge src --> dest
        Adds a single edge to the graph

        Precondition: weights are strictly greater than 0
    */
    void add_edge(Index src, Index dest, WeightType weight) {
        graph.at(src).push_back({ dest, weight });
    }

    /*
        input: input_stream - stream to read from
        Adds edges to the graph by reading an adjacnecy matrix from input_stream

        Precondition: weights are strictly greater than 0
    */
    void read_adjacency_matrix(std::istream& input_stream){
        Index size = graph.size();
        for (Index src = 0; src < size; src++) {
            for (Index dest = 0; dest < size; dest++) {
                WeightType weight; 
                input_stream >> weight;
                if (weight != 0) {
                    add_edge(src, dest, weight);
                }
            }
        }
    }

    /*
        input: output_stream - stream to write in to
        Outputs a human readable representation of the graph to the specified stream 
    */
    void print_graph(std::ostream& output_stream) {
        for (Index i = 0; i < graph.size(); i++) {
            output_stream << "Vertex " << i << ":" << std::endl;
            for (const auto& edge : graph.at(i)) {
                output_stream << "    Vertex " << edge.first << " with weight " << edge.second << std::endl;
            }
        }
    }

private:
    std::vector<std::vector<std::pair<Index, WeightType>>> graph;
};


#endif