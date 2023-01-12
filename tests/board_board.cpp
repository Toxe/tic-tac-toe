#include "catch2/catch_test_macros.hpp"

#include "../src/board/board.hpp"

namespace tic_tac_toe {

TEST_CASE("game/board")
{
    SECTION("a new Board is empty")
    {
        const Board board{};

        for (int row = 0; row < 3; ++row)
            for (int col = 0; col < 3; ++col)
                CHECK(board.empty_square({row, col}));
    }

    SECTION("can change owners of squares")
    {
        Board board{};

        for (int row = 0; row < 3; ++row) {
            for (int col = 0; col < 3; ++col) {
                board.change_owner_of_square({row, col}, human_player_id);
                CHECK(board.player_of_square({row, col}) == human_player_id);

                board.change_owner_of_square({row, col}, ai_player_id);
                CHECK(board.player_of_square({row, col}) == ai_player_id);
            }
        }
    }

    SECTION("a new Board has empty squares")
    {
        const Board board{};

        CHECK(board.has_empty_squares());
    }

    SECTION("a partially filled Board has empty squares")
    {
        Board board{};

        board.change_owner_of_square({0, 1}, human_player_id);
        board.change_owner_of_square({1, 2}, ai_player_id);

        CHECK(board.has_empty_squares());
    }

    SECTION("a full Board does not have empty squares")
    {
        const auto board = Board::with_data({
            std::array{'x', '-', 'x'},
            std::array{'x', '-', 'x'},
            std::array{'-', 'x', '-'},
        });

        CHECK(board.has_empty_squares() == false);
    }

    SECTION("can create Board with data")
    {
        const auto board = Board::with_data({
            std::array{'x', '-', 'x'},
            std::array{'x', '-', 'x'},
            std::array{'-', 'x', '-'},
        });

        CHECK(board.player_of_square(Square{0, 0}) == human_player_id);
        CHECK(board.player_of_square(Square{0, 1}) == ai_player_id);
        CHECK(board.player_of_square(Square{0, 2}) == human_player_id);
        CHECK(board.player_of_square(Square{1, 0}) == human_player_id);
        CHECK(board.player_of_square(Square{1, 1}) == ai_player_id);
        CHECK(board.player_of_square(Square{1, 2}) == human_player_id);
        CHECK(board.player_of_square(Square{2, 0}) == ai_player_id);
        CHECK(board.player_of_square(Square{2, 1}) == human_player_id);
        CHECK(board.player_of_square(Square{2, 2}) == ai_player_id);
    }
}

}  // namespace tic_tac_toe
