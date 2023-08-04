#include <string>
#include <cstdint>
#include "graph.hpp"
#include "maxflow_mincut.hpp"

enum WeightType {
    integer = 0,
    real
};

int main(int argc, char* argv[]){

    std::string input_type {};
    
    // Parse command line arguments
    if(argc == 1){
        input_type = "-f";
    }else if(argc == 2){
        input_type = argv[1];
        if(input_type != "-i" && input_type != "-f"){
            std::cout << "Usage: " << argv[0] << " <-i/-f>" << std::endl;
            return -1;
        }
    }else{
        std::cout << "Usage: " << argv[0] << " <-i/-f>" << std::endl;
        return -1; 
    }
    const WeightType weight_type = (input_type == "-f") ? WeightType::real : WeightType::integer;

    // Specify the number of vertices in the graph n
    std::size_t num_vertices {};
    std::cin >> num_vertices;
    // Specify the source vertex in graph default = 0
    std::size_t src_vertex {};
    std::cin >> src_vertex;
    // Specify the sink vertex in graph default = n-1
    std::size_t sink_vertex {};
    std::cin >> sink_vertex;
    sink_vertex = (sink_vertex == 0) ? num_vertices-1 : sink_vertex;

    // Max flow can always be exactly represented using a double
    double max_flow {};

    if(weight_type == WeightType::integer){
        DirWeightedGraph<uint32_t> graph {num_vertices};
        graph.read_adjacency_matrix(std::cin);
        max_flow = maxmin::max_flow_min_cut(src_vertex, sink_vertex, graph);
    }else{
        DirWeightedGraph<double> graph {num_vertices};
        graph.read_adjacency_matrix(std::cin);
        max_flow = maxmin::max_flow_min_cut(src_vertex, sink_vertex, graph);
    }

    std::cout << "Maximum flow is " << max_flow << std::endl;

    return 0;
}