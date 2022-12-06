#include "catch2/catch_test_macros.hpp"

#include "board.hpp"

namespace tic_tac_toe {

TEST_CASE("game/board")
{
    SECTION("a new board is empty")
    {
        const Board board;

        for (int row = 0; row < 3; ++row)
            for (int col = 0; col < 3; ++col)
                CHECK(board.is_empty_square(row, col));
    }
}

}  // namespace tic_tac_toe
