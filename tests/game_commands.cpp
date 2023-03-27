#include "catch2/catch_test_macros.hpp"

#include "../src/app/app_controller.hpp"
#include "../src/board/board.hpp"
#include "../src/game/commands.hpp"
#include "../src/game/game_state.hpp"
#include "../src/output/console_writer.hpp"

namespace tic_tac_toe {

TEST_CASE("game/commands")
{
    Board board;
    GameState game_state{PlayerType::human, PlayerType::ai};
    AppController controller;
    ConsoleWriter console_writer{false};

    SECTION("PlayerMoveCommand")
    {
        SECTION("change owner of squares")
        {
            controller.execute(PlayerMoveCommand(&game_state, &board, &console_writer, player1_id, Square{0, 1}));
            CHECK(board.player_of_square({0, 1}) == player1_id);

            controller.execute(PlayerMoveCommand(&game_state, &board, &console_writer, player2_id, Square{1, 2}));
            CHECK(board.player_of_square({1, 2}) == player2_id);
        }

        SECTION("changing the owner of an already occupied square throws an exception")
        {
            controller.execute(PlayerMoveCommand(&game_state, &board, &console_writer, player1_id, Square{1, 0}));
            CHECK_THROWS(controller.execute(PlayerMoveCommand(&game_state, &board, &console_writer, player2_id, Square{1, 0})));
        }

        SECTION("undo & redo")
        {
            controller.execute(PlayerMoveCommand(&game_state, &board, &console_writer, player1_id, Square{0, 1}));
            controller.execute(PlayerMoveCommand(&game_state, &board, &console_writer, player2_id, Square{1, 2}));

            CHECK(board.player_of_square({0, 1}) == player1_id);
            CHECK(board.player_of_square({1, 2}) == player2_id);

            controller.undo();
            CHECK(board.empty_square({1, 2}));

            controller.undo();
            CHECK(board.empty_square({0, 1}));

            controller.redo();
            CHECK(board.player_of_square({0, 1}) == player1_id);

            controller.redo();
            CHECK(board.player_of_square({1, 2}) == player2_id);
        }
    }
}

}  // namespace tic_tac_toe
