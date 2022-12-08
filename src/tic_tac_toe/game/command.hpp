#pragma once

#include "player.hpp"
#include "square.hpp"

namespace tic_tac_toe {

struct Command {
    player_id player;
    Square square;
};

}  // namespace tic_tac_toe
