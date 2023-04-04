#include "player.hpp"

#include <cassert>

namespace tic_tac_toe {

bool player_is_human(const PlayerInfo& player_info)
{
    assert(player_is_valid(player_info.player));

    return player_info.type == PlayerType::human;
}

bool player_is_ai(const PlayerInfo& player_info)
{
    assert(player_is_valid(player_info.player));

    return player_info.type == PlayerType::ai;
}

bool player_is_valid(const Player player)
{
    return player == Player::X || player == Player::O;
}

}  // namespace tic_tac_toe
