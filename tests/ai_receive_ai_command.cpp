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

std::optional<Square> find_non_empty_square(const Board& board)
{
    for (int row = 0; row < board.rows(); ++row)
        for (int col = 0; col < board.cols(); ++col)
            if (!board.empty_square({col, row}))
                return Square{col, row};

    return {};
}

TEST_CASE("ai/receive_ai_command")
{
    GameState game_state;
    AppController controller;
    ConsoleWriter console_writer{false};

    SECTION("picks a square that is empty")
    {
        for (int i = 0; i < 3 * 3; ++i) {
            Board empty_board;
            CommandFactory command_factory{empty_board, game_state, controller, console_writer};

            auto command = receive_ai_command(empty_board, command_factory);
            controller.execute(std::move(command));

            CHECK(empty_board.player_of_square(*find_non_empty_square(empty_board)) == ai_player_id);
        }
    }

    SECTION("picks the last remaining empty square")
    {
        // board with one empty square
        auto board = Board::with_data({
            std::array{'X', 'O', 'X'},
            std::array{'X', '-', 'X'},
            std::array{'O', 'X', 'O'},
        });
        CommandFactory command_factory{board, game_state, controller, console_writer};

        auto command = receive_ai_command(board, command_factory);
        controller.execute(std::move(command));

        CHECK(board.player_of_square({1, 1}) == ai_player_id);
    }

    SECTION("throws exception if there are no more empty squares")
    {
        // filled board
        auto board = Board::with_data({
            std::array{'X', 'X', 'X'},
            std::array{'X', 'X', 'X'},
            std::array{'X', 'X', 'X'},
        });
        CommandFactory command_factory{board, game_state, controller, console_writer};

        CHECK_THROWS(receive_ai_command(board, command_factory));
    }
}

}  // namespace tic_tac_toe
