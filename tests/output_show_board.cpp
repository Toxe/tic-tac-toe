#include "catch2/catch_test_macros.hpp"
#include "catch2/matchers/catch_matchers_string.hpp"

#include "../src/output/show_board.hpp"

namespace tic_tac_toe {

TEST_CASE("output/show_board")
{
    SECTION("empty board")
    {
        const std::string s = "\n"
                              "+---+---+---+\n"
                              "|   |   |   | 1\n"
                              "+---+---+---+\n"
                              "|   |   |   | 2\n"
                              "+---+---+---+\n"
                              "|   |   |   | 3\n"
                              "+---+---+---+\n"
                              "  A   B   C\n"
                              "\n";

        const Board board;

        CHECK_THAT(show_board(board), Catch::Matchers::Equals(s));
    }

    SECTION("board with occupied squares")
    {
        const std::string s = "\n"
                              "+---+---+---+\n"
                              "| X | O |   | 1\n"
                              "+---+---+---+\n"
                              "|   |   | X | 2\n"
                              "+---+---+---+\n"
                              "| O |   |   | 3\n"
                              "+---+---+---+\n"
                              "  A   B   C\n"
                              "\n";

        Board board;

        board.change_owner_of_square(Square{0, 0}, Player::X);
        board.change_owner_of_square(Square{2, 1}, Player::X);
        board.change_owner_of_square(Square{1, 0}, Player::O);
        board.change_owner_of_square(Square{0, 2}, Player::O);

        CHECK_THAT(show_board(board), Catch::Matchers::Equals(s));
    }
}

}  // namespace tic_tac_toe
