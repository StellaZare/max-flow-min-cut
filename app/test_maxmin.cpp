#define CATCH_CONFIG_MAIN
#define CHECK_THROWS_AS(expr, exceptionType) INTERNAL_CATCH_THROWS_AS("CHECK_THROWS_AS", exceptionType, Catch::ResultDisposition::ContinueOnFailure, expr)
#include <catch2/catch.hpp>
#include "maxflow_mincut.hpp"

void print_path(const std::vector<int>& path){
    for(int v = 0; v < path.size(); v++){
        std::cout << v << " : " << path.at(v) << std::endl;
    }
}

TEMPLATE_TEST_CASE("test BFS for existing path", "[interval]", int, double){
    DirWeightedGraph<TestType> graph {6};

    std::istringstream input {
        "0 7 0 0 4 0 0 0 5 3 0 0 0 0 0 0 0 8 0 0 3 0 0 5 0 3 0 2 0 0 0 0 0 0 0 0"
    };

    graph.read_adjacency_matrix(input);
    
    std::vector<int> path;
    path.resize(6);
    bool result = maxmin::get_augmenting_path(0, 5, graph, path);

    CHECK(result); 
}

TEMPLATE_TEST_CASE("test BFS for non existing path", "[interval]", int, double){
    DirWeightedGraph<TestType> graph {6};

    std::istringstream input {
        "0 7 0 0 4 0 0 0 5 3 0 0 0 0 0 0 0 8 0 0 3 0 0 5 0 3 0 2 0 0 0 0 0 0 0 0"
    };

    graph.read_adjacency_matrix(input);
    
    std::vector<int> path;
    path.resize(6);
    bool result = maxmin::get_augmenting_path(5, 0, graph, path);

    CHECK(!result); 
}

TEMPLATE_TEST_CASE("inputs/graph_1 test case", "[interval]", int, double){
    DirWeightedGraph<TestType> graph {6};

    std::istringstream input {
        "0 7 0 0 4 0 0 0 5 3 0 0 0 0 0 0 0 8 0 0 3 0 0 5 0 3 0 2 0 0 0 0 0 0 0 0"
    };

    graph.read_adjacency_matrix(input);
    
    std::vector<int> path;
    path.resize(6);
    TestType result = maxmin::max_flow_min_cut(0, 5, graph);

    CHECK(result == 10); 
}

TEMPLATE_TEST_CASE("inputs/graph_2 test case", "[interval]", int, double){
    DirWeightedGraph<TestType> graph {4};

    std::istringstream input {
        "0 10 15 0 0 0 0 15 0 0 0 10 0 0 0 0"
    };

    graph.read_adjacency_matrix(input);
    
    std::vector<int> path;
    path.resize(4);
    TestType result = maxmin::max_flow_min_cut(0, 3, graph);

    CHECK(result == 20); 
}