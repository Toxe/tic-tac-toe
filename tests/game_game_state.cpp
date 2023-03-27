#include "catch2/catch_test_macros.hpp"

#include "../src/game/game_state.hpp"

namespace tic_tac_toe {

TEST_CASE("game/game_state")
{
    SECTION("first player is player 1")
    {
        const GameState game_state{PlayerType::human, PlayerType::ai};

        CHECK(game_state.current_player().id == player1_id);
    }

    SECTION("can switch between the players")
    {
        GameState game_state{PlayerType::human, PlayerType::ai};

        game_state.switch_players();
        CHECK(game_state.current_player().id == player2_id);

        game_state.switch_players();
        CHECK(game_state.current_player().id == player1_id);

        game_state.switch_players();
        CHECK(game_state.current_player().id == player2_id);
    }
}

}  // namespace tic_tac_toe
