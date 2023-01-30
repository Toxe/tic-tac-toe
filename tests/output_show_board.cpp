#include "catch2/catch_test_macros.hpp"
#include "catch2/matchers/catch_matchers_string.hpp"

#include "../src/output/show_board.hpp"

namespace tic_tac_toe {

TEST_CASE("output/show_board")
{
    SECTION("empty board")
    {
        const std::string s = "+---+---+---+\n"
                              "|   |   |   | 1\n"
                              "+---+---+---+\n"
                              "|   |   |   | 2\n"
                              "+---+---+---+\n"
                              "|   |   |   | 3\n"
                              "+---+---+---+\n"
                              "  A   B   C\n";

        const Board board;

        CHECK_THAT(show_board(board), Catch::Matchers::Equals(s));
    }

    SECTION("board with occupied squares")
    {
        const std::string s = "+---+---+---+\n"
                              "| X | O |   | 1\n"
                              "+---+---+---+\n"
                              "|   |   | X | 2\n"
                              "+---+---+---+\n"
                              "| O |   |   | 3\n"
                              "+---+---+---+\n"
                              "  A   B   C\n";

        Board board;

        board.change_owner_of_square(Square{0, 0}, human_player_id);
        board.change_owner_of_square(Square{1, 2}, human_player_id);
        board.change_owner_of_square(Square{0, 1}, ai_player_id);
        board.change_owner_of_square(Square{2, 0}, ai_player_id);

        CHECK_THAT(show_board(board), Catch::Matchers::Equals(s));
    }
}

}  // namespace tic_tac_toe
