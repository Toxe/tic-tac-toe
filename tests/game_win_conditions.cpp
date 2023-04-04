#include "catch2/catch_test_macros.hpp"

#include "../src/game/win_conditions.hpp"

namespace tic_tac_toe {

TEST_CASE("game/win_conditions")
{
    SECTION("a new board is not game over")
    {
        CHECK(game_over(get_win_condition(Board{})) == false);
    }

    SECTION("a draw is a full board without a winning player")
    {
        const auto board = Board{
            "XOX",
            "XOX",
            "OXO",
        };

        CHECK(get_win_condition(board) == WinCondition::draw);
    }

    SECTION("a game is over if it is either a draw or a player has won")
    {
        const auto draw_board = Board{
            "XOX",
            "XOX",
            "OXO",
        };

        const auto player1_won_board = Board{
            "OXO",
            "XXX",
            "XOO",
        };

        const auto player2_won_board = Board{
            "XOX",
            "OOO",
            "OXX",
        };

        CHECK(game_over(get_win_condition(Board{})) == false);
        CHECK(game_over(get_win_condition(draw_board)));
        CHECK(game_over(get_win_condition(player1_won_board)));
        CHECK(game_over(get_win_condition(player2_won_board)));
    }

    SECTION("check rows")
    {
        const auto board1 = Board{
            "XXX",
            "XOX",
            "OXO",
        };

        const auto board2 = Board{
            "XOX",
            "XXX",
            "OXO",
        };

        const auto board3 = Board{
            "OXO",
            "XOX",
            "XXX",
        };

        CHECK(check_player_victory(board1, Player::X));
        CHECK(check_player_victory(board2, Player::X));
        CHECK(check_player_victory(board3, Player::X));
        CHECK(check_player_victory(board1, Player::O) == false);
        CHECK(check_player_victory(board2, Player::O) == false);
        CHECK(check_player_victory(board3, Player::O) == false);
    }

    SECTION("check columns")
    {
        const auto board1 = Board{
            "XXO",
            "XOX",
            "XXO",
        };

        const auto board2 = Board{
            "XXO",
            "OXX",
            "XXO",
        };

        const auto board3 = Board{
            "OXX",
            "XOX",
            "OXX",
        };

        CHECK(check_player_victory(board1, Player::X));
        CHECK(check_player_victory(board2, Player::X));
        CHECK(check_player_victory(board3, Player::X));
        CHECK(check_player_victory(board1, Player::O) == false);
        CHECK(check_player_victory(board2, Player::O) == false);
        CHECK(check_player_victory(board3, Player::O) == false);
    }

    SECTION("check diagonals")
    {
        const auto board1 = Board{
            "XOO",
            "OXO",
            "OOX",
        };

        const auto board2 = Board{
            "OOX",
            "OXO",
            "XOO",
        };

        CHECK(check_player_victory(board1, Player::X));
        CHECK(check_player_victory(board2, Player::X));
        CHECK(check_player_victory(board1, Player::O) == false);
        CHECK(check_player_victory(board2, Player::O) == false);
    }
}

}  // namespace tic_tac_toe
