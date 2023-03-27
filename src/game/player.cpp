#include "player.hpp"

#include <cassert>

namespace tic_tac_toe {

bool player_is_human(const PlayerInfo& player_info)
{
    assert(player_id_is_valid(player_info.id));

    return player_info.type == PlayerType::human;
}

bool player_is_ai(const PlayerInfo& player_info)
{
    assert(player_id_is_valid(player_info.id));

    return player_info.type == PlayerType::ai;
}

bool player_id_is_valid(const player_id player)
{
    return player == player1_id || player == player2_id;
}

}  // namespace tic_tac_toe
