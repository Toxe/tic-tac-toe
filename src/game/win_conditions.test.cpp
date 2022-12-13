#include "catch2/catch_test_macros.hpp"

#include "win_conditions.hpp"

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
            std::array{'x', '-', 'x'},
            std::array{'x', '-', 'x'},
            std::array{'-', 'x', '-'},
        });

        CHECK(get_win_condition(board) == WinCondition::draw);
    }

    SECTION("a game is over if it is either a draw or a player has won")
    {
        const auto draw_board = Board::with_data({
            std::array{'x', '-', 'x'},
            std::array{'x', '-', 'x'},
            std::array{'-', 'x', '-'},
        });

        const auto human_player_won_board = Board::with_data({
            std::array{'-', 'x', '-'},
            std::array{'x', 'x', 'x'},
            std::array{'x', '-', '-'},
        });

        const auto ai_player_won_board = Board::with_data({
            std::array{'x', '-', 'x'},
            std::array{'-', '-', '-'},
            std::array{'-', 'x', 'x'},
        });

        CHECK(game_over(Board{}) == false);
        CHECK(game_over(draw_board));
        CHECK(game_over(human_player_won_board));
        CHECK(game_over(ai_player_won_board));
    }

    SECTION("check rows")
    {
        const auto board1 = Board::with_data({
            std::array{'x', 'x', 'x'},
            std::array{'x', '-', 'x'},
            std::array{'-', 'x', '-'},
        });

        const auto board2 = Board::with_data({
            std::array{'x', '-', 'x'},
            std::array{'x', 'x', 'x'},
            std::array{'-', 'x', '-'},
        });

        const auto board3 = Board::with_data({
            std::array{'-', 'x', '-'},
            std::array{'x', '-', 'x'},
            std::array{'x', 'x', 'x'},
        });

        CHECK(check_player_victory(board1, human_player_id));
        CHECK(check_player_victory(board2, human_player_id));
        CHECK(check_player_victory(board3, human_player_id));
        CHECK(check_player_victory(board1, ai_player_id) == false);
        CHECK(check_player_victory(board2, ai_player_id) == false);
        CHECK(check_player_victory(board3, ai_player_id) == false);
    }

    SECTION("check columns")
    {
        const auto board1 = Board::with_data({
            std::array{'x', 'x', '-'},
            std::array{'x', '-', 'x'},
            std::array{'x', 'x', '-'},
        });

        const auto board2 = Board::with_data({
            std::array{'x', 'x', '-'},
            std::array{'-', 'x', 'x'},
            std::array{'x', 'x', '-'},
        });

        const auto board3 = Board::with_data({
            std::array{'-', 'x', 'x'},
            std::array{'x', '-', 'x'},
            std::array{'-', 'x', 'x'},
        });

        CHECK(check_player_victory(board1, human_player_id));
        CHECK(check_player_victory(board2, human_player_id));
        CHECK(check_player_victory(board3, human_player_id));
        CHECK(check_player_victory(board1, ai_player_id) == false);
        CHECK(check_player_victory(board2, ai_player_id) == false);
        CHECK(check_player_victory(board3, ai_player_id) == false);
    }

    SECTION("check diagonals")
    {
        const auto board1 = Board::with_data({
            std::array{'x', '-', '-'},
            std::array{'-', 'x', '-'},
            std::array{'-', '-', 'x'},
        });

        const auto board2 = Board::with_data({
            std::array{'-', '-', 'x'},
            std::array{'-', 'x', '-'},
            std::array{'x', '-', '-'},
        });

        CHECK(check_player_victory(board1, human_player_id));
        CHECK(check_player_victory(board2, human_player_id));
        CHECK(check_player_victory(board1, ai_player_id) == false);
        CHECK(check_player_victory(board2, ai_player_id) == false);
    }
}

}  // namespace tic_tac_toe
