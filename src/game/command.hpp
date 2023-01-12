#pragma once

#include "../board/square.hpp"
#include "player.hpp"

namespace tic_tac_toe {

struct Command {
    player_id player;
    Square square;
};

}  // namespace tic_tac_toe
