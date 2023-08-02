#include <string>
#include <cstdint>
#include "graph.hpp"
#include "maxflow_mincut.hpp"

enum WeightType {
    integer = 0,
    real
};

int main(int argc, char* argv[]){

    // Parse command line arguments
    if(argc != 2){
        std::cout << "Usage: " << argv[0] << " <-i/-f>" << std::endl;
        return -1;
    }

    std::string input_type {argv[1]};
    if(input_type != "-i" && input_type != "-f"){
        std::cout << "Usage: " << argv[0] << " <-i/-f>" << std::endl;
        return -1;
    }
    const WeightType weight_type = (input_type == "-f") ? WeightType::real : WeightType::integer;

    // Read first line of input
    std::size_t num_vertices {};
    std::cin >> num_vertices;

    if(weight_type == WeightType::integer){
        DirWeightedGraph<uint32_t> graph {num_vertices};
        graph.read_adjacency_matrix(std::cin);
        uint32_t max_flow = maxmin::max_flow_min_cut(0, num_vertices-1, graph);
        std::cout << "interger maxium flow: " << max_flow << std::endl;
    }else{
        DirWeightedGraph<double> graph {num_vertices};
        graph.read_adjacency_matrix(std::cin);
        double max_flow = maxmin::max_flow_min_cut(0, num_vertices-1, graph);
        std::cout << "double maxium flow: " << max_flow << std::endl;
    }

}