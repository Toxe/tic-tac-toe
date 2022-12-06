#pragma once

namespace tic_tac_toe {

using player_id = int;

class GameState {
public:
    [[nodiscard]] bool is_empty_cell(int row, int col) const;
    [[nodiscard]] player_id get_player_of_cell(int row, int col) const;

private:
};

}  // namespace tic_tac_toe
