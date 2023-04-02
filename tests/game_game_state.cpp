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

    SECTION("check if a human player is playing against AI")
    {
        CHECK(GameState{PlayerType::human, PlayerType::ai}.playing_against_ai() == true);
        CHECK(GameState{PlayerType::ai, PlayerType::human}.playing_against_ai() == true);
        CHECK(GameState{PlayerType::human, PlayerType::human}.playing_against_ai() == false);
        CHECK(GameState{PlayerType::ai, PlayerType::ai}.playing_against_ai() == false);
    }
}

}  // namespace tic_tac_toe
