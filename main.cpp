#include <string>
#include <cstdint>
#include "graph.hpp"

enum WeightType {
    integer = 0,
    real
};

int main(int argc, char* argv[]){

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

    std::size_t num_vertices {};
    std::cin >> num_vertices;

    if(weight_type == WeightType::integer){
        Graph<uint32_t> graph {num_vertices};
        graph.print_graph();
    }else{
        Graph<double> graph {num_vertices};
        graph.print_graph();
    }

}