#include <iostream>
#include <vector>
#include <array>
#include <queue>
#include <limits.h>
#include "graph.hpp"

namespace maxmin {

    /*
        input: src - the starting vertex
               sink - the vertex we are trying to reach
               residual_graph - the graph as a DirWeightedGraph object
               path - the vector modified by the function to store the order of vertices in the path from src to sink
        Finds the shortest path from src to sink in the graph using BFS
        Modifes the path vector to store the order of vertices in the path
        Returns true if a valid path exists and false otherwise
    */
    template <class GraphType>
    bool get_augmenting_path(typename GraphType::Index src, typename GraphType::Index sink, GraphType residual_graph, std::vector<int>& path){
        // To keep track of visited vertices
        std::vector<bool> visited {};
        visited.resize(residual_graph.size());
        
        // To keep track of the path taken
        path.clear();
        path.resize(residual_graph.size());
        
        // To keep track of vertices with unvisited neighbours
        std::queue<std::size_t> to_visit; 

        to_visit.push(src);
        visited.at(src) = true;
        path.at(src) = -1;

        while(!to_visit.empty()){
            std::size_t next_visit = to_visit.front();
            to_visit.pop();

            typename GraphType::EdgeList edge_list = residual_graph.get_edge_list(next_visit);
            for(auto& edge : edge_list){
                if(visited.at(edge.first) == false && edge.second > 0){
                    visited.at(edge.first) = true;
                    to_visit.push(edge.first);
                    path.at(edge.first) = next_visit;
                    
                }
            }
        }
        // Check if sink was visted 
        return visited.at(sink);
    }

    /*
        input: src - index of the starting vertex
               sink - index of the ending vertex
               graph - the original graph 
        Creates the residual graph then calculates the max_flow_min_cut 

    */
    template <class GraphType>
    typename GraphType::WeightType max_flow_min_cut(typename GraphType::Index src, typename GraphType::Index sink, GraphType graph){
        GraphType residual_graph = graph.get_residual_graph();
        std::vector <int> parent_path;
        
        typename GraphType::WeightType max_flow = 0;

        while(get_augmenting_path(src, sink, residual_graph, parent_path)){
            typename GraphType::WeightType current_flow = residual_graph.get_edge_weight(parent_path.at(sink), sink);

            // Find the minimum capacity along the path
            for(typename GraphType::Index vertex = parent_path.at(sink); vertex != src; vertex = parent_path.at(vertex)){
                typename GraphType::Index parent = parent_path.at(vertex);
                current_flow = std::min(current_flow, residual_graph.get_edge_weight(parent, vertex));
            }

            max_flow += current_flow;

            for(typename GraphType::Index vertex = sink; vertex != src; vertex = parent_path.at(vertex)){
                typename GraphType::Index parent = parent_path.at(vertex);
                
                // Substract the current_flow from the forward path
                typename GraphType::WeightType prev_weight = residual_graph.get_edge_weight(parent, vertex);
                residual_graph.modify_edge_weight(parent, vertex, prev_weight-current_flow);
                // Add the current_flow to the backward path
                prev_weight = residual_graph.get_edge_weight(vertex, parent);
                residual_graph.modify_edge_weight(vertex, parent, prev_weight+current_flow);
            }
        }

        return max_flow;
    }

}