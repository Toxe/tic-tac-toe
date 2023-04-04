#include "game_players.hpp"

#include <algorithm>
#include <cassert>

namespace tic_tac_toe {

const PlayerInfo& GamePlayers::player_info(const Player player) const
{
    assert(player_is_valid(player));

    return players_[static_cast<std::size_t>(player) - 1];
}

bool GamePlayers::playing_against_ai() const
{
    return std::count_if(players_.begin(), players_.end(), [](const auto& player_info) { return player_info.type == PlayerType::human; }) == 1;
}

void GamePlayers::switch_players()
{
    assert(player_is_valid(current_player_));

    current_player_ = current_player_ == Player::X ? Player::O : Player::X;
}

}  // namespace tic_tac_toe
