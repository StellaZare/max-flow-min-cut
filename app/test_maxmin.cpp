#define CATCH_CONFIG_MAIN
#define CHECK_THROWS_AS(expr, exceptionType) INTERNAL_CATCH_THROWS_AS("CHECK_THROWS_AS", exceptionType, Catch::ResultDisposition::ContinueOnFailure, expr)
#include <catch2/catch.hpp>
#include "maxflow_mincut.hpp"

