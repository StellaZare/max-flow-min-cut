#define CATCH_CONFIG_MAIN
#define CHECK_THROWS_AS(expr, exceptionType) INTERNAL_CATCH_THROWS_AS("CHECK_THROWS_AS", exceptionType, Catch::ResultDisposition::ContinueOnFailure, expr)
#include <catch2/catch.hpp>
#include "graph.hpp"

TEMPLATE_TEST_CASE("constructor", "[interval]", float, double, long double){
    DirWeightedGraph<TestType> graph{6};
}