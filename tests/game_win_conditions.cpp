#include "catch2/catch_test_macros.hpp"

#include "../src/game/win_conditions.hpp"

namespace tic_tac_toe {

TEST_CASE("game/win_conditions")
{
    SECTION("a new board is not game over")
    {
        CHECK(game_over(Board{}) == false);
    }

    SECTION("a draw is a full board without a winning player")
    {
        const auto board = Board::with_data({
            std::array{'X', 'O', 'X'},
            std::array{'X', 'O', 'X'},
            std::array{'O', 'X', 'O'},
        });

        CHECK(get_win_condition(board) == WinCondition::draw);
    }

    SECTION("a game is over if it is either a draw or a player has won")
    {
        const auto draw_board = Board::with_data({
            std::array{'X', 'O', 'X'},
            std::array{'X', 'O', 'X'},
            std::array{'O', 'X', 'O'},
        });

        const auto player1_won_board = Board::with_data({
            std::array{'O', 'X', 'O'},
            std::array{'X', 'X', 'X'},
            std::array{'X', 'O', 'O'},
        });

        const auto player2_won_board = Board::with_data({
            std::array{'X', 'O', 'X'},
            std::array{'O', 'O', 'O'},
            std::array{'O', 'X', 'X'},
        });

        CHECK(game_over(Board{}) == false);
        CHECK(game_over(draw_board));
        CHECK(game_over(player1_won_board));
        CHECK(game_over(player2_won_board));
    }

    SECTION("check rows")
    {
        const auto board1 = Board::with_data({
            std::array{'X', 'X', 'X'},
            std::array{'X', 'O', 'X'},
            std::array{'O', 'X', 'O'},
        });

        const auto board2 = Board::with_data({
            std::array{'X', 'O', 'X'},
            std::array{'X', 'X', 'X'},
            std::array{'O', 'X', 'O'},
        });

        const auto board3 = Board::with_data({
            std::array{'O', 'X', 'O'},
            std::array{'X', 'O', 'X'},
            std::array{'X', 'X', 'X'},
        });

        CHECK(check_player_victory(board1, player1_id));
        CHECK(check_player_victory(board2, player1_id));
        CHECK(check_player_victory(board3, player1_id));
        CHECK(check_player_victory(board1, player2_id) == false);
        CHECK(check_player_victory(board2, player2_id) == false);
        CHECK(check_player_victory(board3, player2_id) == false);
    }

    SECTION("check columns")
    {
        const auto board1 = Board::with_data({
            std::array{'X', 'X', 'O'},
            std::array{'X', 'O', 'X'},
            std::array{'X', 'X', 'O'},
        });

        const auto board2 = Board::with_data({
            std::array{'X', 'X', 'O'},
            std::array{'O', 'X', 'X'},
            std::array{'X', 'X', 'O'},
        });

        const auto board3 = Board::with_data({
            std::array{'O', 'X', 'X'},
            std::array{'X', 'O', 'X'},
            std::array{'O', 'X', 'X'},
        });

        CHECK(check_player_victory(board1, player1_id));
        CHECK(check_player_victory(board2, player1_id));
        CHECK(check_player_victory(board3, player1_id));
        CHECK(check_player_victory(board1, player2_id) == false);
        CHECK(check_player_victory(board2, player2_id) == false);
        CHECK(check_player_victory(board3, player2_id) == false);
    }

    SECTION("check diagonals")
    {
        const auto board1 = Board::with_data({
            std::array{'X', 'O', 'O'},
            std::array{'O', 'X', 'O'},
            std::array{'O', 'O', 'X'},
        });

        const auto board2 = Board::with_data({
            std::array{'O', 'O', 'X'},
            std::array{'O', 'X', 'O'},
            std::array{'X', 'O', 'O'},
        });

        CHECK(check_player_victory(board1, player1_id));
        CHECK(check_player_victory(board2, player1_id));
        CHECK(check_player_victory(board1, player2_id) == false);
        CHECK(check_player_victory(board2, player2_id) == false);
    }
}

}  // namespace tic_tac_toe
