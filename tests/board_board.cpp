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
        const auto board = Board{
            "XOX",
            "XOX",
            "O--",
        };

        CHECK(board.player_of_square({0, 0}) == Player::X);
        CHECK(board.player_of_square({1, 0}) == Player::O);
        CHECK(board.player_of_square({2, 0}) == Player::X);
        CHECK(board.player_of_square({0, 1}) == Player::X);
        CHECK(board.player_of_square({1, 1}) == Player::O);
        CHECK(board.player_of_square({2, 1}) == Player::X);
        CHECK(board.player_of_square({0, 2}) == Player::O);
        CHECK(board.player_of_square({1, 2}) == Player::none);
        CHECK(board.player_of_square({2, 2}) == Player::none);
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
                board.change_owner_of_square({col, row}, Player::X);
                CHECK(board.player_of_square({col, row}) == Player::X);

                board.change_owner_of_square({col, row}, Player::O);
                CHECK(board.player_of_square({col, row}) == Player::O);
            }
        }
    }

    SECTION("can clear owners of squares")
    {
        auto board = Board{
            "XOX",
            "XOX",
            "OXO",
        };

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

        board.change_owner_of_square({0, 1}, Player::X);
        board.change_owner_of_square({1, 2}, Player::O);

        CHECK(board.has_empty_squares());
    }

    SECTION("a full Board does not have empty squares")
    {
        const auto board = Board{
            "XOX",
            "XOX",
            "OXO",
        };

        CHECK(board.has_empty_squares() == false);
    }

    SECTION("all_squares_in_col_belong_to()")
    {
        const auto board = Board{
            "XOX",
            "XOO",
            "XO-",
        };

        CHECK(board.all_squares_in_col_belong_to(0, Player::X));
        CHECK(board.all_squares_in_col_belong_to(1, Player::O));

        CHECK(board.all_squares_in_col_belong_to(0, Player::none) == false);
        CHECK(board.all_squares_in_col_belong_to(1, Player::none) == false);

        CHECK(board.all_squares_in_col_belong_to(2, Player::X) == false);
        CHECK(board.all_squares_in_col_belong_to(2, Player::O) == false);
        CHECK(board.all_squares_in_col_belong_to(2, Player::none) == false);
    }

    SECTION("all_squares_in_row_belong_to()")
    {
        const auto board = Board{
            "XXX",
            "OOO",
            "XO-",
        };

        CHECK(board.all_squares_in_row_belong_to(0, Player::X));
        CHECK(board.all_squares_in_row_belong_to(1, Player::O));

        CHECK(board.all_squares_in_row_belong_to(0, Player::none) == false);
        CHECK(board.all_squares_in_row_belong_to(1, Player::none) == false);

        CHECK(board.all_squares_in_row_belong_to(2, Player::X) == false);
        CHECK(board.all_squares_in_row_belong_to(2, Player::O) == false);
        CHECK(board.all_squares_in_row_belong_to(2, Player::none) == false);
    }
}

}  // namespace tic_tac_toe
