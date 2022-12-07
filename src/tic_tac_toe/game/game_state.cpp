#include "game_state.hpp"

#include <cassert>

namespace tic_tac_toe {

void GameState::switch_players()
{
    assert(current_player_ == 1 || current_player_ == 2);

    current_player_ = current_player_ == 1 ? 2 : 1;
}

}  // namespace tic_tac_toe
