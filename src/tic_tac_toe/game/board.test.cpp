#include "catch2/catch_test_macros.hpp"

#include "board.hpp"

namespace tic_tac_toe {

TEST_CASE("game/board")
{
    SECTION("a new board is empty")
    {
        const Board board{};

        for (int row = 0; row < 3; ++row)
            for (int col = 0; col < 3; ++col)
                CHECK(board.empty_square(row, col));
    }

    SECTION("a new board is not game over")
    {
        const Board board{};

        CHECK(board.game_over() == false);
    }

    SECTION("can change owners of squares")
    {
        Board board{};

        for (int row = 0; row < 3; ++row) {
            for (int col = 0; col < 3; ++col) {
                board.change_owner_of_square(row, col, 1);
                CHECK(board.get_player_of_square(row, col) == 1);

                board.change_owner_of_square(row, col, 2);
                CHECK(board.get_player_of_square(row, col) == 2);
            }
        }
    }

    SECTION("a game is over once all squares are owned by players")
    {
        Board board{};

        for (int row = 0; row < 3; ++row)
            for (int col = 0; col < 3; ++col)
                board.change_owner_of_square(row, col, 1);

        CHECK(board.game_over());
    }
}

}  // namespace tic_tac_toe
