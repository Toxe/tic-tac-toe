#include <utility>

#include "catch2/catch_test_macros.hpp"
#include "catch2/generators/catch_generators.hpp"
#include "fmt/core.h"
#include "fmt/format.h"

#include "../src/ai/receive_ai_command.hpp"
#include "../src/app/app_controller.hpp"
#include "../src/board/board.hpp"
#include "../src/command/command_factory.hpp"
#include "../src/game/game_state.hpp"
#include "../src/game/win_conditions.hpp"
#include "../src/minimax/minimax.hpp"
#include "../src/minimax/stats.hpp"
#include "../src/output/console_writer.hpp"
#include "../src/output/show_board.hpp"
#include "../src/output/show_game_over.hpp"

namespace tic_tac_toe {

std::ostream& operator<<(std::ostream& os, const Square& square) { return os << fmt::format("({}/{})", square.x, square.y); }

WinCondition check_match(Board& board, const player_id first_player)
{
    GameState game_state{PlayerType::ai, PlayerType::ai};
    AppController controller;
    ConsoleWriter console_writer;
    CommandFactory command_factory{board, game_state, controller, console_writer};

    if (game_state.current_player().id != first_player)
        game_state.switch_players();

    while (!game_over(get_win_condition(board))) {
        console_writer.write(show_board(board));
        controller.execute(receive_ai_command(game_state.current_player().id, board, command_factory, console_writer));
    }

    console_writer.write(show_board(board));
    console_writer.write(show_game_over(get_win_condition(board)));

    return get_win_condition(board);
}

TEST_CASE("minimax/minimax")
{
    SECTION("X picks the winning move")
    {
        // clang-format off
        auto [move_square, board] = GENERATE(
            std::pair{Square{0, 2}, Board{"XXO",
                                          "XOX",
                                          "-O-"}},

            std::pair{Square{2, 2}, Board{"OXX",
                                          "XOX",
                                          "-O-"}},

            std::pair{Square{2, 2}, Board{"OX-",
                                          "XOO",
                                          "XX-"}},

            std::pair{Square{2, 0}, Board{"XX-",
                                          "XOO",
                                          "OX-"}},

            std::pair{Square{0, 2}, Board{"XXO",
                                          "XO-",
                                          "-O-"}},

            std::pair{Square{2, 2}, Board{"OXX",
                                          "-OX",
                                          "-O-"}},

            std::pair{Square{2, 2}, Board{"O--",
                                          "XOO",
                                          "XX-"}},

            std::pair{Square{2, 0}, Board{"XX-",
                                          "XOO",
                                          "O--"}},

            std::pair{Square{0, 0}, Board{"-XX",
                                          "-O-",
                                          "-O-"}},

            std::pair{Square{2, 0}, Board{"XX-",
                                          "-O-",
                                          "-O-"}},

            std::pair{Square{0, 2}, Board{"-O-",
                                          "-O-",
                                          "-XX"}},

            std::pair{Square{2, 2}, Board{"-O-",
                                          "-O-",
                                          "XX-"}},

            std::pair{Square{0, 0}, Board{"-XX",
                                          "-O-",
                                          "-O-"}},

            std::pair{Square{1, 0}, Board{"--O",
                                          "OX-",
                                          "-X-"}},

            std::pair{Square{1, 2}, Board{"-XO",
                                          "OX-",
                                          "---"}},

            std::pair{Square{1, 1}, Board{"X-O",
                                          "---",
                                          "O-X"}},

            std::pair{Square{1, 1}, Board{"O-X",
                                          "---",
                                          "X-O"}},

            std::pair{Square{1, 0}, Board{"X-X",
                                          "O-O",
                                          "---"}},

            std::pair{Square{1, 2}, Board{"---",
                                          "O-O",
                                          "X-X"}},

            std::pair{Square{2, 0}, Board{"O--",
                                          "OX-",
                                          "X-O"}}
        );
        // clang-format on

        MinimaxStats stats;
        const auto move = minimax(board, {0, 0}, 0, 10, MinimaxStrategy::maximizing, stats);

        CHECK(move.score >= 1);
        CHECK(move.square == move_square);

        if (move.score < 1 || move.square != move_square)
            CHECK(check_match(board, player1_id) == WinCondition::player1_won);
    }
}

}  // namespace tic_tac_toe
