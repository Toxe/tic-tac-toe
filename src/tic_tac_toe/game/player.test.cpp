#include "catch2/catch_test_macros.hpp"

#include "player.hpp"

namespace tic_tac_toe {

TEST_CASE("game/player")
{
    SECTION("player 1 is human")
    {
        CHECK(player_is_human(1) == true);
        CHECK(player_is_ai(1) == false);
    }

    SECTION("player 2 is AI")
    {
        CHECK(player_is_human(2) == false);
        CHECK(player_is_ai(2) == true);
    }
}

}  // namespace tic_tac_toe
