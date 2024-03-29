#include "catch2/catch_test_macros.hpp"

#include "../src/app/app_controller.hpp"
#include "../src/board/board.hpp"
#include "../src/game/commands.hpp"
#include "../src/game/game_players.hpp"
#include "../src/output/console_writer.hpp"

namespace tic_tac_toe {

TEST_CASE("game/commands")
{
    Board board;
    GamePlayers game_players{PlayerType::human, PlayerType::ai};
    AppController controller;
    ConsoleWriter console_writer{false};

    SECTION("PlayerMoveCommand")
    {
        SECTION("change owner of squares")
        {
            controller.execute(PlayerMoveCommand(&game_players, &board, &console_writer, Player::X, Square{0, 1}));
            CHECK(board.player_of_square({0, 1}) == Player::X);

            controller.execute(PlayerMoveCommand(&game_players, &board, &console_writer, Player::O, Square{1, 2}));
            CHECK(board.player_of_square({1, 2}) == Player::O);
        }

        SECTION("changing the owner of an already occupied square throws an exception")
        {
            controller.execute(PlayerMoveCommand(&game_players, &board, &console_writer, Player::X, Square{1, 0}));
            CHECK_THROWS(controller.execute(PlayerMoveCommand(&game_players, &board, &console_writer, Player::O, Square{1, 0})));
        }

        SECTION("undo & redo")
        {
            controller.execute(PlayerMoveCommand(&game_players, &board, &console_writer, Player::X, Square{0, 1}));
            controller.execute(PlayerMoveCommand(&game_players, &board, &console_writer, Player::O, Square{1, 2}));

            CHECK(board.player_of_square({0, 1}) == Player::X);
            CHECK(board.player_of_square({1, 2}) == Player::O);

            controller.undo();
            CHECK(board.empty_square({1, 2}));

            controller.undo();
            CHECK(board.empty_square({0, 1}));

            controller.redo();
            CHECK(board.player_of_square({0, 1}) == Player::X);

            controller.redo();
            CHECK(board.player_of_square({1, 2}) == Player::O);
        }
    }
}

}  // namespace tic_tac_toe
