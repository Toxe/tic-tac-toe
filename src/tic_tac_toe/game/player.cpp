#include "player.hpp"

#include <cassert>

namespace tic_tac_toe {

bool player_is_human(player_id player)
{
    assert(player == human_player_id || player == ai_player_id);

    return player == human_player_id;
}

bool player_is_ai(player_id player)
{
    assert(player == human_player_id || player == ai_player_id);

    return player == ai_player_id;
}

}  // namespace tic_tac_toe
