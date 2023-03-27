#include "catch2/catch_test_macros.hpp"

#include "../src/game/player.hpp"

namespace tic_tac_toe {

TEST_CASE("game/player")
{
    SECTION("check if player is human")
    {
        PlayerInfo player_info{player1_id, PlayerType::human};

        CHECK(player_is_human(player_info) == true);
        CHECK(player_is_ai(player_info) == false);
    }

    SECTION("check if player is AI")
    {
        PlayerInfo player_info{player2_id, PlayerType::ai};

        CHECK(player_is_human(player_info) == false);
        CHECK(player_is_ai(player_info) == true);
    }

    SECTION("check if player id is valid")
    {
        CHECK(player_id_is_valid(player1_id) == true);
        CHECK(player_id_is_valid(player2_id) == true);
        CHECK(player_id_is_valid(no_player_id) == false);
    }
}

}  // namespace tic_tac_toe
