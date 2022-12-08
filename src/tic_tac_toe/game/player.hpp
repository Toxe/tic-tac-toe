#pragma once

namespace tic_tac_toe {

using player_id = int;

constexpr player_id human_player_id = 1;
constexpr player_id ai_player_id = 2;

bool player_is_human(player_id player);
bool player_is_ai(player_id player);

}  // namespace tic_tac_toe
