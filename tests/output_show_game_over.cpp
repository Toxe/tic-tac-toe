#include "catch2/catch_test_macros.hpp"
#include "catch2/matchers/catch_matchers_string.hpp"

#include "../src/output/show_game_over.hpp"

namespace tic_tac_toe {

TEST_CASE("output/show_game_over")
{
    SECTION("game is not over")
    {
        CHECK_THAT(show_game_over(WinCondition::none), Catch::Matchers::Equals("The game is not over yet."));
    }

    SECTION("draw")
    {
        CHECK_THAT(show_game_over(WinCondition::draw), Catch::Matchers::Equals("Draw!"));
    }

    SECTION("human player won")
    {
        CHECK_THAT(show_game_over(WinCondition::human_player_won), Catch::Matchers::Equals("You won!"));
    }

    SECTION("AI player won")
    {
        CHECK_THAT(show_game_over(WinCondition::ai_player_won), Catch::Matchers::Equals("You lost!"));
    }
}

}  // namespace tic_tac_toe
