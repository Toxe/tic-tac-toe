#include "catch2/catch_test_macros.hpp"

#include "../src/output/player_symbol.hpp"

namespace tic_tac_toe {

TEST_CASE("output/player_symbol")
{
    SECTION("player 1")
    {
        CHECK(player_symbol(player1_id) == 'X');
    }

    SECTION("player 2")
    {
        CHECK(player_symbol(player2_id) == 'O');
    }
}

}  // namespace tic_tac_toe
