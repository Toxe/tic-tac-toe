#pragma once

#include "player.hpp"

namespace tic_tac_toe {

class Board {
public:
    [[nodiscard]] bool is_empty_square(int row, int col) const;
    [[nodiscard]] player_id get_player_of_square(int row, int col) const;
};

}  // namespace tic_tac_toe
