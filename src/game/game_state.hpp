#pragma once

#include <array>

#include "player.hpp"

namespace tic_tac_toe {

class GameState {
public:
    GameState(PlayerType player1_type, PlayerType player2_type);

    [[nodiscard]] const PlayerInfo& current_player() const;

    void switch_players();

private:
    std::array<PlayerInfo, 2> players_;
    player_id current_player_id_ = player1_id;
};

}  // namespace tic_tac_toe
