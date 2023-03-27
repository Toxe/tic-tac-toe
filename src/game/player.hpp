#pragma once

namespace tic_tac_toe {

using player_id = int;

constexpr player_id no_player_id = 0;
constexpr player_id player1_id = 1;
constexpr player_id player2_id = 2;

enum class PlayerType {
    human,
    ai
};

struct PlayerInfo {
    player_id id;
    PlayerType type;
};

bool player_is_human(const PlayerInfo& player_info);
bool player_is_ai(const PlayerInfo& player_info);
bool player_id_is_valid(player_id player);

}  // namespace tic_tac_toe
