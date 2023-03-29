#include "receive_ai_command.hpp"

#include <stdexcept>

#include "../board/board.hpp"
#include "../command/command_factory.hpp"
#include "../minimax/minimax.hpp"
#include "../minimax/stats.hpp"
#include "../output/console_writer.hpp"

namespace tic_tac_toe {

Command receive_ai_command(const player_id player, const Board& board, CommandFactory& command_factory, ConsoleWriter& console_writer)
{
    if (!board.has_empty_squares())
        throw std::runtime_error("board is full");

    MinimaxStats stats;
    auto move = minimax(0, 10, board, {0, 0}, player == player1_id, stats);

    console_writer.write(stats.print(move));

    return command_factory.create_player_move_command(player, move.square);
}

}  // namespace tic_tac_toe
