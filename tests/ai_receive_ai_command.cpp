#include <optional>
#include <utility>

#include "catch2/catch_test_macros.hpp"

#include "../src/ai/receive_ai_command.hpp"
#include "../src/app/app_controller.hpp"
#include "../src/board/board.hpp"
#include "../src/command/command_factory.hpp"
#include "../src/game/game_state.hpp"
#include "../src/output/console_writer.hpp"

namespace tic_tac_toe {

TEST_CASE("ai/receive_ai_command")
{
    GameState game_state{PlayerType::human, PlayerType::ai};
    AppController controller;
    ConsoleWriter console_writer{false};

    SECTION("picks the last remaining empty square")
    {
        // board with one empty square
        auto board = Board{
            "XOX",
            "X-X",
            "OXO",
        };
        CommandFactory command_factory{board, game_state, controller, console_writer};

        auto command = receive_ai_command(player2_id, board, command_factory, console_writer);
        controller.execute(std::move(command));

        CHECK(board.player_of_square({1, 1}) == player2_id);
    }

    SECTION("can receive commands for player 1 and 2")
    {
        for (player_id player = player1_id; player <= player2_id; ++player) {
            // board with one empty square
            auto board = Board{
                "XOX",
                "X-X",
                "OXO",
            };
            CommandFactory command_factory{board, game_state, controller, console_writer};

            auto command = receive_ai_command(player, board, command_factory, console_writer);
            controller.execute(std::move(command));

            CHECK(board.player_of_square({1, 1}) == player);
        }
    }

    SECTION("throws exception if there are no more empty squares")
    {
        // filled board
        auto board = Board{
            "XXX",
            "XXX",
            "XXX",
        };
        CommandFactory command_factory{board, game_state, controller, console_writer};

        CHECK_THROWS(receive_ai_command(player2_id, board, command_factory, console_writer));
    }
}

}  // namespace tic_tac_toe
