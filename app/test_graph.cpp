#define CATCH_CONFIG_MAIN
#define CHECK_THROWS_AS(expr, exceptionType) INTERNAL_CATCH_THROWS_AS("CHECK_THROWS_AS", exceptionType, Catch::ResultDisposition::ContinueOnFailure, expr)
#include <catch2/catch.hpp>
#include <sstream>
#include "graph.hpp"

TEMPLATE_TEST_CASE("get edge weight edge exists", "[interval]", float, double, long double){
    DirWeightedGraph<TestType> graph {6};

    std::istringstream input {
        "0 7 0 0 4 0 0 0 5 3 0 0 0 0 0 0 0 8 0 0 3 0 0 5 0 3 0 2 0 0 0 0 0 0 0 0"
    };

    graph.read_adjacency_matrix(input);
    
    CHECK(graph.get_edge_weight(1, 2) == 5);
    CHECK(graph.get_edge_weight(0, 4) == 4);
    CHECK(graph.get_edge_weight(3, 5) == 5);
}

TEMPLATE_TEST_CASE("get edge weight edge does not exists", "[interval]", float, double, long double){
    DirWeightedGraph<TestType> graph {6};

    std::istringstream input {
        "0 7 0 0 4 0 0 0 5 3 0 0 0 0 0 0 0 8 0 0 3 0 0 5 0 3 0 2 0 0 0 0 0 0 0 0"
    };

    graph.read_adjacency_matrix(input);
    
    CHECK(graph.get_edge_weight(1, 4) == -1);
    CHECK(graph.get_edge_weight(0, 3) == -1);
    CHECK(graph.get_edge_weight(5, 2) == -1);
}

TEMPLATE_TEST_CASE("modify edge weight", "[interval]", float, double, long double){
    DirWeightedGraph<TestType> graph {6};

    std::istringstream input {
        "0 7 0 0 4 0 0 0 5 3 0 0 0 0 0 0 0 8 0 0 3 0 0 5 0 3 0 2 0 0 0 0 0 0 0 0"
    };

    graph.read_adjacency_matrix(input);
    
    CHECK(graph.get_edge_weight(1, 2) == 5);
    CHECK(graph.get_edge_weight(0, 4) == 4);
    CHECK(graph.get_edge_weight(3, 5) == 5);

    graph.modify_edge_weight(1, 2, 3);
    graph.modify_edge_weight(0, 4, 3);
    graph.modify_edge_weight(3, 5, 3);

    CHECK(graph.get_edge_weight(1, 2) == 3);
    CHECK(graph.get_edge_weight(0, 4) == 3);
    CHECK(graph.get_edge_weight(3, 5) == 3);
}

TEMPLATE_TEST_CASE("modify edge weight edge does not exist", "[interval]", float, double, long double){
    DirWeightedGraph<TestType> graph {6};

    std::istringstream input {
        "0 7 0 0 4 0 0 0 5 3 0 0 0 0 0 0 0 8 0 0 3 0 0 5 0 3 0 2 0 0 0 0 0 0 0 0"
    };

    graph.read_adjacency_matrix(input);
    
    CHECK(graph.get_edge_weight(1, 4) == -1);
    CHECK(graph.get_edge_weight(0, 3) == -1);
    CHECK(graph.get_edge_weight(5, 2) == -1);

    CHECK_THROWS_AS(graph.modify_edge_weight(1, 4, 2), std::runtime_error);
    CHECK_THROWS_AS(graph.modify_edge_weight(0, 3, 2), std::runtime_error);
    CHECK_THROWS_AS(graph.modify_edge_weight(5, 2, 2), std::runtime_error);
}