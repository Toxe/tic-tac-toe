#include "player.hpp"

#include <cassert>

namespace tic_tac_toe {

bool player_is_human(const player_id player)
{
    return player == human_player_id;
}

bool player_is_ai(const player_id player)
{
    return player == ai_player_id;
}

bool player_id_is_valid(const player_id player)
{
    return player_is_human(player) || player_is_ai(player);
}

}  // namespace tic_tac_toe
