#include "game_state.hpp"

#include <algorithm>
#include <cassert>

namespace tic_tac_toe {

GameState::GameState(const PlayerType player1_type, const PlayerType player2_type)
{
    players_[0] = PlayerInfo{player1_id, player1_type};
    players_[1] = PlayerInfo{player2_id, player2_type};
}

const PlayerInfo& GameState::current_player() const
{
    assert(player_id_is_valid(current_player_id_));

    return players_[static_cast<std::size_t>(current_player_id_ - 1)];
}

bool GameState::playing_against_ai() const
{
    return std::count_if(players_.begin(), players_.end(), [](const auto& player_info) { return player_info.type == PlayerType::human; }) == 1;
}

void GameState::switch_players()
{
    assert(player_id_is_valid(current_player_id_));

    current_player_id_ = current_player_id_ == player1_id ? player2_id : player1_id;
}

}  // namespace tic_tac_toe
