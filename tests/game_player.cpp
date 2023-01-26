#include "catch2/catch_test_macros.hpp"

#include "../src/game/player.hpp"

namespace tic_tac_toe {

TEST_CASE("game/player")
{
    SECTION("check if player is human")
    {
        CHECK(player_is_human(human_player_id) == true);
        CHECK(player_is_ai(human_player_id) == false);
    }

    SECTION("check if player is AI")
    {
        CHECK(player_is_human(ai_player_id) == false);
        CHECK(player_is_ai(ai_player_id) == true);
    }

    SECTION("no player id")
    {
        CHECK(player_is_human(no_player_id) == false);
        CHECK(player_is_ai(no_player_id) == false);
    }
}

}  // namespace tic_tac_toe
