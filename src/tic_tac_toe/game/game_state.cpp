#include "game_state.hpp"

namespace tic_tac_toe {

bool GameState::is_empty_cell(const int row, const int col) const
{
    return true;
}

player_id GameState::get_player_of_cell(const int row, const int col) const
{
    return 1;
}

}  // namespace tic_tac_toe
