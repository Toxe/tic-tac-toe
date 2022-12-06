#include "player.hpp"

#include <cassert>

namespace tic_tac_toe {

bool player_is_human(player_id player)
{
    assert(player == 1 || player == 2);

    return player == 1;
}

bool player_is_ai(player_id player)
{
    assert(player == 1 || player == 2);

    return player == 2;
}

}  // namespace tic_tac_toe
