#pragma once

#include <array>

#include "player.hpp"
#include "square.hpp"

namespace tic_tac_toe {

class Board {
public:
    static Board with_data(const std::array<std::array<char, 3>, 3>& data);

    [[nodiscard]] player_id player_of_square(Square square) const;
    [[nodiscard]] bool empty_square(Square square) const;

    void change_owner_of_square(Square square, player_id player);

private:
    std::array<std::array<player_id, 3>, 3> squares_;
};

}  // namespace tic_tac_toe
