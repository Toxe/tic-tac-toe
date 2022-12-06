#include "catch2/catch_test_macros.hpp"
#include "catch2/matchers/catch_matchers_string.hpp"

#include "generate_output.hpp"

namespace tic_tac_toe {

TEST_CASE("output/generate_output")
{
    SECTION("empty board")
    {
        const std::string s = "+---+---+---+\n"
                              "| 1 | 2 | 3 |\n"
                              "+---+---+---+\n"
                              "| 4 | 5 | 6 |\n"
                              "+---+---+---+\n"
                              "| 7 | 8 | 9 |\n"
                              "+---+---+---+\n";

        const Board board;

        CHECK_THAT(generate_output(board), Catch::Matchers::Equals(s));
    }
}

}  // namespace tic_tac_toe
