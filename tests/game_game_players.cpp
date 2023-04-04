#include "catch2/catch_test_macros.hpp"

#include "../src/game/game_players.hpp"

namespace tic_tac_toe {

TEST_CASE("game/game_players")
{
    SECTION("first player is player 1")
    {
        const GamePlayers game_players{PlayerType::human, PlayerType::ai};

        CHECK(game_players.current_player().player == Player::X);
    }

    SECTION("can switch between the players")
    {
        GamePlayers game_players{PlayerType::human, PlayerType::ai};

        game_players.switch_players();
        CHECK(game_players.current_player().player == Player::O);

        game_players.switch_players();
        CHECK(game_players.current_player().player == Player::X);

        game_players.switch_players();
        CHECK(game_players.current_player().player == Player::O);
    }

    SECTION("check if a human player is playing against AI")
    {
        CHECK(GamePlayers{PlayerType::human, PlayerType::ai}.playing_against_ai() == true);
        CHECK(GamePlayers{PlayerType::ai, PlayerType::human}.playing_against_ai() == true);
        CHECK(GamePlayers{PlayerType::human, PlayerType::human}.playing_against_ai() == false);
        CHECK(GamePlayers{PlayerType::ai, PlayerType::ai}.playing_against_ai() == false);
    }
}

}  // namespace tic_tac_toe
