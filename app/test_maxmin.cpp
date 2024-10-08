#define CATCH_CONFIG_MAIN
#define CHECK_THROWS_AS(expr, exceptionType) INTERNAL_CATCH_THROWS_AS("CHECK_THROWS_AS", exceptionType, Catch::ResultDisposition::ContinueOnFailure, expr)
#include <catch2/catch.hpp>
#include "maxflow_mincut.hpp"

// void print_path(const std::vector<int>& path){
//     for(int v = 0; v < path.size(); v++){
//         std::cout << v << " : " << path.at(v) << std::endl;
//     }
// }

// TEMPLATE_TEST_CASE("test BFS for existing path", "[interval]", int, double){
//     std::size_t graph_size = 6;

//     DirWeightedGraph<TestType> graph {graph_size};

//     std::istringstream input {
//         "0 7 0 0 4 0 0 0 5 3 0 0 0 0 0 0 0 8 0 0 3 0 0 5 0 3 0 2 0 0 0 0 0 0 0 0"
//     };

//     graph.read_adjacency_matrix(input);
    
//     std::vector<int> path;
//     path.resize(graph_size);
//     bool result = maxmin::get_augmenting_path(0, graph_size-1, graph, path);

//     CHECK(result); 
// }

// TEMPLATE_TEST_CASE("test BFS for non existing path", "[interval]", int, double){
//     std::size_t graph_size = 6;

//     DirWeightedGraph<TestType> graph {graph_size};

//     std::istringstream input {
//         "0 7 0 0 4 0 0 0 5 3 0 0 0 0 0 0 0 8 0 0 3 0 0 5 0 3 0 2 0 0 0 0 0 0 0 0"
//     };

//     graph.read_adjacency_matrix(input);
    
//     std::vector<int> path;
//     path.resize(graph_size);
//     bool result = maxmin::get_augmenting_path(graph_size-1, 0, graph, path);

//     CHECK(!result); 
// }

// TEMPLATE_TEST_CASE("inputs/graph_1 test case", "[interval]", int, double){
//     std::size_t graph_size = 6;
//     TestType expected = 10;
    
//     DirWeightedGraph<TestType> graph {graph_size};

//     std::istringstream input {
//         "0 7 0 0 4 0 0 0 5 3 0 0 0 0 0 0 0 8 0 0 3 0 0 5 0 3 0 2 0 0 0 0 0 0 0 0"
//     };

//     graph.read_adjacency_matrix(input);
    
//     std::vector<int> path;
//     path.resize(graph_size);
//     DirWeightedGraph<TestType> residual_graph {graph.get_residual_graph()};
//     TestType result = maxmin::maxflow_mincut(0, graph_size-1, residual_graph);

//     CHECK(result == expected); 
// }

// TEMPLATE_TEST_CASE("inputs/graph_2 test case", "[interval]", int, double){
//     std::size_t graph_size = 4;
//     TestType expected = 20;
    
//     DirWeightedGraph<TestType> graph {graph_size};

//     std::istringstream input {
//         "0 10 15 0 0 0 0 15 0 0 0 10 0 0 0 0"
//     };

//     graph.read_adjacency_matrix(input);

//     std::vector<int> path;
//     path.resize(graph_size);
//     DirWeightedGraph<TestType> residual_graph {graph.get_residual_graph()};
//     TestType result = maxmin::maxflow_mincut(0, graph_size-1, residual_graph);

//     CHECK(result == expected); 
// }

// TEMPLATE_TEST_CASE("inputs/graph_3 test case", "[interval]", int, double){
//     std::size_t graph_size = 2;
//     TestType expected = 10;

//     DirWeightedGraph<TestType> graph {graph_size};

//     std::istringstream input {
//         "0 10 0 0"
//     };

//     graph.read_adjacency_matrix(input);
    
//     std::vector<int> path;
//     path.resize(graph_size);
//     DirWeightedGraph<TestType> residual_graph {graph.get_residual_graph()};
//     TestType result = maxmin::maxflow_mincut(0, graph_size-1, residual_graph);

//     CHECK(result == expected); 
// }

// TEMPLATE_TEST_CASE("inputs/graph_4 test case", "[interval]", int, double){
//     std::size_t graph_size = 4;
//     TestType expected = 25;

//     DirWeightedGraph<TestType> graph {graph_size};

//     std::istringstream input {
//         "0 15 10 0 0 0 5 10 0 0 0 15 0 0 0 0"
//     };

//     graph.read_adjacency_matrix(input);
    
//     std::vector<int> path;
//     path.resize(graph_size);
//     DirWeightedGraph<TestType> residual_graph {graph.get_residual_graph()};
//     TestType result = maxmin::maxflow_mincut(0, graph_size-1, residual_graph);

//     CHECK(result == expected); 
// }

// TEMPLATE_TEST_CASE("inputs/graph_1 test case src=1 sink=5", "[interval]", int, double){
//     std::size_t graph_size = 6;
//     TestType expected = 8;
    
//     DirWeightedGraph<TestType> graph {graph_size};

//     std::istringstream input {
//         "0 7 0 0 4 0 0 0 5 3 0 0 0 0 0 0 0 8 0 0 3 0 0 5 0 3 0 2 0 0 0 0 0 0 0 0"
//     };

//     graph.read_adjacency_matrix(input);
    
//     std::vector<int> path;
//     path.resize(graph_size);
//     DirWeightedGraph<TestType> residual_graph {graph.get_residual_graph()};
//     TestType result = maxmin::maxflow_mincut(1, graph_size-1, residual_graph);

//     CHECK(result == expected); 
// }

// TEMPLATE_TEST_CASE("inputs/graph_1 test case src=0 sink=2", "[interval]", int, double){
//     std::size_t graph_size = 6;
//     TestType expected = 8;
    
//     DirWeightedGraph<TestType> graph {graph_size};

//     std::istringstream input {
//         "0 7 0 0 4 0 0 0 5 3 0 0 0 0 0 0 0 8 0 0 3 0 0 5 0 3 0 2 0 0 0 0 0 0 0 0"
//     };

//     graph.read_adjacency_matrix(input);
    
//     std::vector<int> path;
//     path.resize(graph_size);
//     DirWeightedGraph<TestType> residual_graph {graph.get_residual_graph()};
//     TestType result = maxmin::maxflow_mincut(0, 2, residual_graph);

//     CHECK(result == expected); 
// }

// TEMPLATE_TEST_CASE("double case 1", "[interval]", float, double){
//     std::size_t graph_size = 2;
//     TestType expected = 0.5;
    
//     DirWeightedGraph<TestType> graph {graph_size};

//     std::istringstream input {
//         "0 0.5 0 0"
//     };

//     graph.read_adjacency_matrix(input);
    
//     std::vector<int> path;
//     path.resize(graph_size);
//     DirWeightedGraph<TestType> residual_graph {graph.get_residual_graph()};
//     TestType result = maxmin::maxflow_mincut(0, 1, residual_graph);

//     CHECK(result == expected); 
// }

TEMPLATE_TEST_CASE("double case 2", "[interval]", float, double){
    std::size_t graph_size = 4;
    TestType expected = 0.75;
    
    DirWeightedGraph<TestType> graph {graph_size};

    std::istringstream input {
        "0 0.25 0.75 0 0 0 0 0.75 0 0 0 0.5 0 0 0 0"
    };

    graph.read_adjacency_matrix(input);
    
    std::vector<int> path;
    path.resize(graph_size);
    DirWeightedGraph<TestType> residual_graph {graph.get_residual_graph()};
    TestType result = maxmin::maxflow_mincut(0, 3, residual_graph);

    CHECK(result == expected); 
}

TEMPLATE_TEST_CASE("double case 3", "[interval]", float, double){
    std::size_t graph_size = 6;
    TestType expected = 1;
    
    DirWeightedGraph<TestType> graph {graph_size};

    std::istringstream input {
        "0 0.7 0 0 0.4 0 0 0 0.5 0.3 0 0 0 0 0 0 0 0.8 0 0 0.3 0 0 0.5 0 0.3 0 0.2 0 0  0 0 0 0 0 0"
    };

    graph.read_adjacency_matrix(input);
    
    std::vector<int> path;
    path.resize(graph_size);
    DirWeightedGraph<TestType> residual_graph {graph.get_residual_graph()};
    TestType result = maxmin::maxflow_mincut(0, 5, residual_graph);

    CHECK(result == expected); 
}
