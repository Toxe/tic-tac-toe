#pragma once

#include "player.hpp"

namespace tic_tac_toe {

class GameState {
public:
    [[nodiscard]] player_id current_player() const { return current_player_; }

    void switch_players();

private:
    player_id current_player_ = human_player_id;
};

}  // namespace tic_tac_toe
