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
    DirWeightedGraph(Index size) : size_{size}, graph_{size} {}

    // Move and Copy constructors
    DirWeightedGraph(const DirWeightedGraph&) = default;
    DirWeightedGraph(DirWeightedGraph&&) = default;
    DirWeightedGraph& operator=(const DirWeightedGraph&) = default;

    /*
        input: src - index of source vertex
               dest - indext of destination vertex
               weight - the weight of the edge src --> dest
        Adds a single edge to the graph

        Precondition: weights are strictly greater than 0
    */
    void add_edge(Index src, Index dest, WeightType weight) {
        graph_.at(src).push_back({ dest, weight });
    }

    /*
        input: input_stream - stream to read from
        Adds edges to the graph by reading an adjacnecy matrix from input_stream

        Precondition: weights are strictly greater than 0
    */
    void read_adjacency_matrix(std::istream& input_stream){
        for (Index src = 0; src < size_; src++) {
            for (Index dest = 0; dest < size_; dest++) {
                WeightType weight; 
                input_stream >> weight;
                if (weight != 0) {
                    add_edge(src, dest, weight);
                }
            }
        }
    }
    /*
        Returns the residual graph obtained from the original graph
        where the for each edge (u, v, w) in the original graph 
        edges (u, v, w) and (v, u, 0) are in the residual graph
    */
    DirWeightedGraph get_residual_graph(){
        DirWeightedGraph residual {size_};
        for (Index src = 0; src < size_; src++) {
            for (auto& edge : graph_.at(src)) {
                Index dest = edge.first;
                WeightType weight = edge.second;

                // Add original edge
                residual.add_edge(src, dest, weight);
                // Add backwards edge
                residual.add_edge(dest, src, 0);
            }
        }
        return residual;
    }

    /*
        input: output_stream - stream to write in to
        Outputs a human readable representation of the graph to the specified stream 
    */
    void print_graph(std::ostream& output_stream) {
        for (Index i = 0; i < size_; i++) {
            output_stream << "Vertex " << i << ":" << std::endl;
            for (const auto& edge : graph_.at(i)) {
                output_stream << "    Vertex " << edge.first << " with weight " << edge.second << std::endl;
            }
        }
    }

    /*
        Returns the number of vertices in the graph
    */
    Index size(){
        return size_;
    }

private:
    std::vector<std::vector<std::pair<Index, WeightType>>> graph_;
    Index size_;
};


#endif