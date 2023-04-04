#include "game_players.hpp"

#include <algorithm>
#include <cassert>

namespace tic_tac_toe {

GamePlayers::GamePlayers(const PlayerType player1_type, const PlayerType player2_type)
{
    players_[0] = PlayerInfo{Player::X, player1_type};
    players_[1] = PlayerInfo{Player::O, player2_type};
}

const PlayerInfo& GamePlayers::current_player() const
{
    assert(player_is_valid(current_player_));

    return players_[static_cast<std::size_t>(current_player_) - 1];
}

bool GamePlayers::playing_against_ai() const
{
    return std::count_if(players_.begin(), players_.end(), [](const auto& player_info) { return player_info.type == PlayerType::human; }) == 1;
}

void GamePlayers::switch_players()
{
    assert(player_is_valid(current_player_));

    current_player_ = current_player_ == Player::X ? Player ::O : Player::X;
}

}  // namespace tic_tac_toe
