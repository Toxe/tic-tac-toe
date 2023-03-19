#include "catch2/catch_test_macros.hpp"

#include "../src/board/board.hpp"

namespace tic_tac_toe {

TEST_CASE("game/board")
{
    SECTION("a new Board is empty")
    {
        const Board board;

        for (int row = 0; row < board.rows(); ++row)
            for (int col = 0; col < board.cols(); ++col)
                CHECK(board.empty_square({col, row}));
    }

    SECTION("can create Board with data")
    {
        const auto board = Board::with_data({
            std::array{'X', 'O', 'X'},
            std::array{'X', 'O', 'X'},
            std::array{'O', '-', '-'},
        });

        CHECK(board.player_of_square({0, 0}) == human_player_id);
        CHECK(board.player_of_square({1, 0}) == ai_player_id);
        CHECK(board.player_of_square({2, 0}) == human_player_id);
        CHECK(board.player_of_square({0, 1}) == human_player_id);
        CHECK(board.player_of_square({1, 1}) == ai_player_id);
        CHECK(board.player_of_square({2, 1}) == human_player_id);
        CHECK(board.player_of_square({0, 2}) == ai_player_id);
        CHECK(board.player_of_square({1, 2}) == no_player_id);
        CHECK(board.player_of_square({2, 2}) == no_player_id);
    }

    SECTION("cols() returns the number of columns")
    {
        CHECK(Board{}.cols() == 3);
    }

    SECTION("rows() returns the number of rows")
    {
        CHECK(Board{}.rows() == 3);
    }

    SECTION("can change owners of squares")
    {
        Board board;

        for (int row = 0; row < board.rows(); ++row) {
            for (int col = 0; col < board.cols(); ++col) {
                board.change_owner_of_square({col, row}, human_player_id);
                CHECK(board.player_of_square({col, row}) == human_player_id);

                board.change_owner_of_square({col, row}, ai_player_id);
                CHECK(board.player_of_square({col, row}) == ai_player_id);
            }
        }
    }

    SECTION("can clear owners of squares")
    {
        auto board = Board::with_data({
            std::array{'X', 'O', 'X'},
            std::array{'X', 'O', 'X'},
            std::array{'O', 'X', 'O'},
        });

        for (int row = 0; row < board.rows(); ++row) {
            for (int col = 0; col < board.cols(); ++col) {
                board.clear_owner_of_square({col, row});
                CHECK(board.empty_square({col, row}));
            }
        }
    }

    SECTION("a new Board has empty squares")
    {
        const Board board;

        CHECK(board.has_empty_squares());
    }

    SECTION("a partially filled Board has empty squares")
    {
        Board board;

        board.change_owner_of_square({0, 1}, human_player_id);
        board.change_owner_of_square({1, 2}, ai_player_id);

        CHECK(board.has_empty_squares());
    }

    SECTION("a full Board does not have empty squares")
    {
        const auto board = Board::with_data({
            std::array{'X', 'O', 'X'},
            std::array{'X', 'O', 'X'},
            std::array{'O', 'X', 'O'},
        });

        CHECK(board.has_empty_squares() == false);
    }

    SECTION("all_squares_in_col_belong_to()")
    {
        const auto board = Board::with_data({
            std::array{'X', 'O', 'X'},
            std::array{'X', 'O', 'O'},
            std::array{'X', 'O', '-'},
        });

        CHECK(board.all_squares_in_col_belong_to(0, human_player_id));
        CHECK(board.all_squares_in_col_belong_to(1, ai_player_id));

        CHECK(board.all_squares_in_col_belong_to(0, no_player_id) == false);
        CHECK(board.all_squares_in_col_belong_to(1, no_player_id) == false);

        CHECK(board.all_squares_in_col_belong_to(2, human_player_id) == false);
        CHECK(board.all_squares_in_col_belong_to(2, ai_player_id) == false);
        CHECK(board.all_squares_in_col_belong_to(2, no_player_id) == false);
    }

    SECTION("all_squares_in_row_belong_to()")
    {
        const auto board = Board::with_data({
            std::array{'X', 'X', 'X'},
            std::array{'O', 'O', 'O'},
            std::array{'X', 'O', '-'},
        });

        CHECK(board.all_squares_in_row_belong_to(0, human_player_id));
        CHECK(board.all_squares_in_row_belong_to(1, ai_player_id));

        CHECK(board.all_squares_in_row_belong_to(0, no_player_id) == false);
        CHECK(board.all_squares_in_row_belong_to(1, no_player_id) == false);

        CHECK(board.all_squares_in_row_belong_to(2, human_player_id) == false);
        CHECK(board.all_squares_in_row_belong_to(2, ai_player_id) == false);
        CHECK(board.all_squares_in_row_belong_to(2, no_player_id) == false);
    }
}

}  // namespace tic_tac_toe
