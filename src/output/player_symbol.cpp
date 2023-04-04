#include "player_symbol.hpp"

#include <cassert>

namespace tic_tac_toe {

char player_symbol(const Player player)
{
    assert(player_is_valid(player));

    return player == Player::X ? 'X' : 'O';
}

}  // namespace tic_tac_toe
