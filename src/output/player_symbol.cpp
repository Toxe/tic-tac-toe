#include "player_symbol.hpp"

#include <cassert>

namespace tic_tac_toe {

char player_symbol(const player_id player)
{
    assert(player_id_is_valid(player));

    return player == player1_id ? 'X' : 'O';
}

}  // namespace tic_tac_toe
