#include "catch2/catch_test_macros.hpp"

#include "game_state.hpp"

namespace tic_tac_toe {

TEST_CASE("game/game_state")
{
    SECTION("first player is the human player")
    {
        const GameState game_state;

        CHECK(game_state.current_player() == human_player_id);
    }

    SECTION("can switch between the players")
    {
        GameState game_state;

        CHECK(game_state.current_player() == human_player_id);

        game_state.switch_players();
        CHECK(game_state.current_player() == ai_player_id);

        game_state.switch_players();
        CHECK(game_state.current_player() == human_player_id);

        game_state.switch_players();
        CHECK(game_state.current_player() == ai_player_id);
    }
}

}  // namespace tic_tac_toe
