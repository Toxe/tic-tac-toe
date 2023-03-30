#include "catch2/catch_test_macros.hpp"
#include "catch2/matchers/catch_matchers_string.hpp"

#include "../src/minimax/stats.hpp"

namespace tic_tac_toe {

TEST_CASE("minimax/stats")
{
    SECTION("update and print")
    {
        MinimaxStats stats;
        const MinimaxMove move{Square{1, 2}, 3};

        CHECK_THAT(stats.print(move), Catch::Matchers::Matches(R"(Minimax: \d+\.\d+ .s, max depth: \d+, calls: \d+, move: \d\/\d \(score -?\d+\)\s)"));
        CHECK_THAT(stats.print(move), Catch::Matchers::Matches(R"(Minimax: \d+\.\d+ .s, max depth: 0, calls: 0, move: 1\/2 \(score 3\)\s)"));

        stats.update(1);
        stats.update(1);
        stats.update(2);
        stats.update(2);
        stats.update(3);

        CHECK_THAT(stats.print(move), Catch::Matchers::Matches(R"(Minimax: \d+\.\d+ .s, max depth: \d+, calls: \d+, move: \d\/\d \(score -?\d+\)\s)"));
        CHECK_THAT(stats.print(move), Catch::Matchers::Matches(R"(Minimax: \d+\.\d+ .s, max depth: 3, calls: 5, move: 1\/2 \(score 3\)\s)"));
    }
}

}  // namespace tic_tac_toe
