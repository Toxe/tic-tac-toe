#include <optional>
#include <utility>

#include "catch2/catch_test_macros.hpp"

#include "../src/ai/receive_ai_command.hpp"
#include "../src/app/app_controller.hpp"
#include "../src/output/console_writer.hpp"

namespace tic_tac_toe {

std::optional<Square> find_non_empty_square(const Board& board)
{
    for (int row = 0; row < 3; ++row)
        for (int col = 0; col < 3; ++col)
            if (!board.empty_square({row, col}))
                return Square{row, col};

    return {};
}

TEST_CASE("ai/receive_ai_command")
{
    GameState game_state{};
    AppController controller{};
    ConsoleWriter console_writer{false};

    SECTION("picks a square that is empty")
    {
        for (int i = 0; i < 3 * 3; ++i) {
            Board empty_board{};

            auto command = receive_ai_command(game_state, empty_board, console_writer);
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

        auto command = receive_ai_command(game_state, board, console_writer);
        controller.execute(std::move(command));

        CHECK(board.player_of_square({1, 1}) == ai_player_id);
    }

    SECTION("throws exception if there are no more empty squares")
    {
        Board board{};

        for (int row = 0; row < 3; ++row)
            for (int col = 0; col < 3; ++col)
                board.change_owner_of_square({row, col}, human_player_id);

        CHECK_THROWS(receive_ai_command(game_state, board, console_writer));
    }
}

}  // namespace tic_tac_toe
