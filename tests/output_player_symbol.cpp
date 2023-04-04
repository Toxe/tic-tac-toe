#include "catch2/catch_test_macros.hpp"

#include "../src/output/player_symbol.hpp"

namespace tic_tac_toe {

TEST_CASE("output/player_symbol")
{
    SECTION("player 1")
    {
        CHECK(player_symbol(Player::X) == 'X');
    }

    SECTION("player 2")
    {
        CHECK(player_symbol(Player::O) == 'O');
    }
}

}  // namespace tic_tac_toe
