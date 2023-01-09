#include "catch2/catch_test_macros.hpp"

#include "../src/ai/receive_ai_command.hpp"

namespace tic_tac_toe {

TEST_CASE("ai/receive_ai_command")
{
    SECTION("picks a square that is not empty")
    {
        const Board board{};

        for (int i = 0; i < 10; ++i) {
            const auto command = receive_ai_command(board);
            CHECK(board.empty_square(command.square));
        }
    }

    SECTION("picks the last remaining empty square")
    {
        Board board{};

        // fill all but one square
        for (int row = 0; row < 3; ++row)
            for (int col = 0; col < 3; ++col)
                if (!(row == 1 && col == 1))
                    board.change_owner_of_square({row, col}, human_player_id);

        const auto command = receive_ai_command(board);

        CHECK(command.square == Square{1, 1});
    }

    SECTION("throws exception if there are no more empty squares")
    {
        Board board{};

        for (int row = 0; row < 3; ++row)
            for (int col = 0; col < 3; ++col)
                board.change_owner_of_square({row, col}, human_player_id);

        CHECK_THROWS(receive_ai_command(board));
    }

    SECTION("command belongs to the AI player")
    {
        const Board board{};
        const auto command = receive_ai_command(board);

        CHECK(command.player == ai_player_id);
    }
}

}  // namespace tic_tac_toe
