#pragma once

namespace tic_tac_toe {

enum class Player {
    none = 0,
    X = 1,
    O = 2
};

enum class PlayerType {
    human,
    ai
};

struct PlayerInfo {
    Player player;
    PlayerType type;
};

bool player_is_human(const PlayerInfo& player_info);
bool player_is_ai(const PlayerInfo& player_info);
bool player_is_valid(Player player);

}  // namespace tic_tac_toe
