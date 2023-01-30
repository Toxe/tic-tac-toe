#include "game_state.hpp"

#include <cassert>

namespace tic_tac_toe {

void GameState::switch_players()
{
    assert(player_id_is_valid(current_player_));

    current_player_ = current_player_ == human_player_id ? ai_player_id : human_player_id;
}

}  // namespace tic_tac_toe
