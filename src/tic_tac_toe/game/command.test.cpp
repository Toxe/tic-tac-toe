#include "catch2/catch_test_macros.hpp"

#include "command.hpp"

namespace tic_tac_toe {

TEST_CASE("game/command")
{
    SECTION("construct")
    {
        const Command command{1, Square{1, 2}};

        CHECK(command.player == 1);
        CHECK(command.square == Square{1, 2});
    }
}

}  // namespace tic_tac_toe
