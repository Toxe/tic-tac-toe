#include "catch2/catch_test_macros.hpp"

#include "../src/app/app_controller.hpp"
#include "../src/board/board.hpp"
#include "../src/game/commands.hpp"
#include "../src/game/game_state.hpp"

namespace tic_tac_toe {

TEST_CASE("game/commands")
{
    Board board{};
    GameState game_state{};
    AppController controller{};

    SECTION("PlayerMoveCommand")
    {
        SECTION("change owner of squares")
        {
            controller.execute(PlayerMoveCommand(&game_state, &board, human_player_id, Square{0, 1}));
            CHECK(board.player_of_square({0, 1}) == human_player_id);

            controller.execute(PlayerMoveCommand(&game_state, &board, ai_player_id, Square{1, 2}));
            CHECK(board.player_of_square({1, 2}) == ai_player_id);
        }

        SECTION("changing the owner of an already occupied square throws an exception")
        {
            controller.execute(PlayerMoveCommand(&game_state, &board, human_player_id, Square{1, 0}));
            CHECK_THROWS(controller.execute(PlayerMoveCommand(&game_state, &board, ai_player_id, Square{1, 0})));
        }

        SECTION("undo & redo")
        {
            controller.execute(PlayerMoveCommand(&game_state, &board, human_player_id, Square{0, 1}));
            controller.execute(PlayerMoveCommand(&game_state, &board, ai_player_id, Square{1, 2}));

            CHECK(board.player_of_square({0, 1}) == human_player_id);
            CHECK(board.player_of_square({1, 2}) == ai_player_id);

            controller.undo();
            CHECK(board.empty_square({1, 2}));

            controller.undo();
            CHECK(board.empty_square({0, 1}));

            controller.redo();
            CHECK(board.player_of_square({0, 1}) == human_player_id);

            controller.redo();
            CHECK(board.player_of_square({1, 2}) == ai_player_id);
        }
    }
}

}  // namespace tic_tac_toe
