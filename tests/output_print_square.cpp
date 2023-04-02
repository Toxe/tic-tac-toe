#include "catch2/catch_test_macros.hpp"
#include "catch2/matchers/catch_matchers_string.hpp"

#include "../src/output/print_square.hpp"

namespace tic_tac_toe {

TEST_CASE("output/print_square")
{
    SECTION("print_square()")
    {
        CHECK_THAT(print_square({0, 0}), Catch::Matchers::Equals("A1"));
        CHECK_THAT(print_square({0, 1}), Catch::Matchers::Equals("A2"));
        CHECK_THAT(print_square({0, 2}), Catch::Matchers::Equals("A3"));
        CHECK_THAT(print_square({1, 0}), Catch::Matchers::Equals("B1"));
        CHECK_THAT(print_square({1, 1}), Catch::Matchers::Equals("B2"));
        CHECK_THAT(print_square({1, 2}), Catch::Matchers::Equals("B3"));
        CHECK_THAT(print_square({2, 0}), Catch::Matchers::Equals("C1"));
        CHECK_THAT(print_square({2, 1}), Catch::Matchers::Equals("C2"));
        CHECK_THAT(print_square({2, 2}), Catch::Matchers::Equals("C3"));
    }
}

}  // namespace tic_tac_toe
