#include "catch2/catch_test_macros.hpp"
#include "catch2/matchers/catch_matchers_string.hpp"

#include "../src/minimax/stats.hpp"

namespace tic_tac_toe {

TEST_CASE("minimax/stats")
{
    SECTION("update and print")
    {
        MinimaxStats stats;

        CHECK_THAT(stats.print(), Catch::Matchers::Matches(R"(> calculated 0 moves in \d+\.\d+ .s \(depth: 0\)\s)"));

        stats.update(1);
        stats.update(1);
        stats.update(2);
        stats.update(2);
        stats.update(3);

        CHECK_THAT(stats.print(), Catch::Matchers::Matches(R"(> calculated 5 moves in \d+\.\d+ .s \(depth: 3\)\s)"));
    }
}

}  // namespace tic_tac_toe
