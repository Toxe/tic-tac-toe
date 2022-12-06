#pragma once

#include <array>

#include "player.hpp"

namespace tic_tac_toe {

class Board {
public:
    [[nodiscard]] player_id get_player_of_square(int row, int col) const;
    [[nodiscard]] bool empty_square(int row, int col) const;

    void change_owner_of_square(int row, int col, player_id player);

    [[nodiscard]] bool game_over() const;

private:
    std::array<std::array<player_id, 3>, 3> squares_;
};

}  // namespace tic_tac_toe
