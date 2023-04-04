#pragma once

#include <array>

#include "player.hpp"

namespace tic_tac_toe {

class GamePlayers {
public:
    GamePlayers(PlayerType player1_type, PlayerType player2_type);

    [[nodiscard]] const PlayerInfo& current_player() const;
    [[nodiscard]] bool playing_against_ai() const;

    void switch_players();

private:
    std::array<PlayerInfo, 2> players_;
    Player current_player_ = Player::X;
};

}  // namespace tic_tac_toe
