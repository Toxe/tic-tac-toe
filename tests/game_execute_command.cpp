#include "catch2/catch_test_macros.hpp"

#include "../src/game/execute_command.hpp"

namespace tic_tac_toe {

TEST_CASE("game/execute_command")
{
    SECTION("change owner of squares")
    {
        Board board{};

        execute_command(board, Command{human_player_id, {0, 1}});
        CHECK(board.player_of_square({0, 1}) == human_player_id);

        execute_command(board, Command{ai_player_id, {1, 2}});
        CHECK(board.player_of_square({1, 2}) == ai_player_id);
    }

    SECTION("changing the owner of an already occupied square throws an exception")
    {
        Board board{};

        execute_command(board, Command{human_player_id, Square{1, 2}});
        CHECK_THROWS(execute_command(board, Command{human_player_id, Square{1, 2}}));
    }
}

}  // namespace tic_tac_toe
