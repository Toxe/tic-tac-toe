#pragma once

#include <string>

#include "../game/game_state.hpp"

namespace tic_tac_toe::detail {

std::string generate_output(const GameState& game_state);

}  // namespace tic_tac_toe::detail
