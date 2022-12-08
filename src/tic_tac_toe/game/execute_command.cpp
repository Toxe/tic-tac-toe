#include "execute_command.hpp"

#include <cassert>
#include <stdexcept>

namespace tic_tac_toe {

void execute_command(Board& board, const Command command)
{
    assert(command.player == human_player_id || command.player == ai_player_id);

    if (!board.empty_square(command.square))
        throw std::invalid_argument("square already occupied");

    board.change_owner_of_square(command.square, command.player);
}

}  // namespace tic_tac_toe
