#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <iostream>
#include <vector>
#include <array>
#include <exception>

template <class T>
class DirWeightedGraph {
public:
    using WeightType = T;
    using Index = std::size_t;
    using EdgeList = std::vector<std::pair<Index, WeightType>>;

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
        Adds a single edge to the graph if the edge does not already exist
        Returns true if the edge was added and false otherwise
        Precondition: weights are strictly greater than 0
    */
    bool add_edge(Index src, Index dest, WeightType weight) {
        if(get_edge_weight(src, dest) == -1){
            graph_.at(src).push_back({ dest, weight });
            return true;
        }
        return false;
    }

    /*
        input: n - index of the vertex
        Returns the edge list corresponding to the vertex
    */
    const EdgeList& get_edge_list(Index n) const {
        return graph_.at(n);
    }

    /*
        input: src - index of source vertex
               dest - index of destination vertex
        Returns the weight of the edge from src to dest if it exists
        otherwise returns -1
    */
    WeightType get_edge_weight(Index src, Index dest) const {
        for(auto& edge : graph_.at(src)){
            if(edge.first == dest)
                return edge.second;
        }
        return -1;        
    }

    /*
        input: src - index of source vertex
               dest - index of destination vertex
               new_weight - modified weight for edge from src to dest
        Changes the weight of the edge from src to dest to the new weight
        Throws an exception if the edge does not exist
    */
    void modify_edge_weight(Index src, Index dest, WeightType new_weight){
        if (get_edge_weight(src, dest) == -1)
            throw std::runtime_error("Edge does not exist");
        for(auto& edge : graph_.at(src)){
            if(edge.first == dest)
                edge.second = new_weight;
        }
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
    DirWeightedGraph get_residual_graph() const {
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
    void print_graph(std::ostream& output_stream) const {
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
    Index size() const {
        return size_;
    }

private:
    std::vector<EdgeList> graph_;
    Index size_;
};


#endif