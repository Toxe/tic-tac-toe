#include "receive_ai_command.hpp"

namespace tic_tac_toe {

Command receive_ai_command(const Board& board)
{
    return Command{ai_player_id, Square{0, 0}};
}

}  // namespace tic_tac_toe
