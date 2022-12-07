#include "catch2/catch_test_macros.hpp"

#include "game_state.hpp"

namespace tic_tac_toe {

TEST_CASE("game/game_state")
{
    SECTION("first player is player 1")
    {
        const GameState game_state;

        CHECK(game_state.current_player() == 1);
    }

    SECTION("can switch between the players")
    {
        GameState game_state;

        CHECK(game_state.current_player() == 1);

        game_state.switch_players();
        CHECK(game_state.current_player() == 2);

        game_state.switch_players();
        CHECK(game_state.current_player() == 1);
    }
}

}  // namespace tic_tac_toe
