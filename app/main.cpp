#include <string>
#include <cstring>
#include <cstdint>
#include "graph.hpp"
#include "maxflow_mincut.hpp"

enum WeightType {
    integer = 0,
    real
};

int main(int argc, char* argv[]){
    
    // Parse command line arguments
    bool integer {};
    bool real_value {};
    bool print_partitions {};
    for(std::size_t idx = 0; idx < argc; idx++){
        
        if(strcmp(argv[idx], "-i") == 0){
            integer = true;
        }else if(strcmp(argv[idx], "-r") == 0){
            real_value = true;
        }else if(strcmp(argv[idx], "-print_partitions") == 0){
            print_partitions = true;
        }else if (idx != 0|| strcmp(argv[idx], "-h") == 0){
            std::cout << "Usage: " << argv[0] << " <-i/-r/-print_partitions>" << std::endl;
            std::cout << "-i    for integer edge weights" << std::endl;
            std::cout << "-r    for real valued edge weights (default)" << std::endl;
            std::cout << "-print_partitions    to print the two partitions of the st-cut" << std::endl;
            return 0; 
        }
    }
    
    // if both -f and -i were entered real value takes precedence 
    const WeightType weight_type = ((!real_value && !integer) || real_value) ? WeightType::real : WeightType::integer;

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

    std::vector<bool> reachable {};
    reachable.resize(num_vertices);

    if(weight_type == WeightType::integer){
        std::cout << "Integer edge weights used" << std::endl;
        // Initialize graph and read from input stream
        DirWeightedGraph<uint32_t> graph {num_vertices};
        graph.read_adjacency_matrix(std::cin);

        // Initialize residual graph
        DirWeightedGraph<uint32_t> residual_graph {graph.get_residual_graph()};

        max_flow = maxmin::maxflow_mincut(src_vertex, sink_vertex, residual_graph);
        maxmin::rec_dfs(src_vertex, residual_graph, reachable);
    }else{
        std::cout << "Real value edge weights used" << std::endl;
        // Initialize graph and read from input stream
        DirWeightedGraph<double> graph {num_vertices};
        graph.read_adjacency_matrix(std::cin);

        // Initialize residual graph
        DirWeightedGraph<double> residual_graph {graph.get_residual_graph()};

        max_flow = maxmin::maxflow_mincut(src_vertex, sink_vertex, residual_graph);
        maxmin::rec_dfs(src_vertex, residual_graph, reachable);
    }

    if(print_partitions){
        std::vector<std::size_t> partition_s {};
        std::vector<std::size_t> partition_t {};
        for(std::size_t v = 0; v < num_vertices; v++){
            if(reachable.at(v))
                partition_s.push_back(v);
            else
                partition_t.push_back(v);
        }

        std::cout << "Partition 1:" << std::endl;
        for(auto& v : partition_s){
            std::cout << "\tVertex " << v << std::endl;
        }
        std::cout << "Partition 2:" << std::endl;
        for(auto& v : partition_t){
            std::cout << "\tVertex " << v << std::endl;
        }
    }
    std::cout << "Maximum flow is " << max_flow << std::endl;

    return 0;
}