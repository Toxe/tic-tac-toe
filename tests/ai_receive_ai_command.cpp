#include <optional>
#include <utility>

#include "catch2/catch_test_macros.hpp"

#include "../src/ai/receive_ai_command.hpp"
#include "../src/app/app_controller.hpp"
#include "../src/board/board.hpp"
#include "../src/command/command_factory.hpp"
#include "../src/game/game_players.hpp"
#include "../src/output/console_writer.hpp"

namespace tic_tac_toe {

TEST_CASE("ai/receive_ai_command")
{
    GamePlayers game_players{PlayerType::human, PlayerType::ai};
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
        const CommandFactory command_factory{board, game_players, controller, console_writer};

        auto command = receive_ai_command(Player::O, board, command_factory, console_writer);
        controller.execute(std::move(command));

        CHECK(board.player_of_square({1, 1}) == Player::O);
    }

    SECTION("can receive commands for player 1 and 2")
    {
        for (const auto player : {Player::X, Player::O}) {
            // board with one empty square
            auto board = Board{
                "XOX",
                "X-X",
                "OXO",
            };
            const CommandFactory command_factory{board, game_players, controller, console_writer};

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
        const CommandFactory command_factory{board, game_players, controller, console_writer};

        CHECK_THROWS(receive_ai_command(Player::O, board, command_factory, console_writer));
    }
}

}  // namespace tic_tac_toe
