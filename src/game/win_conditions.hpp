#pragma once

#include "board.hpp"

namespace tic_tac_toe {

enum class WinCondition {
    none,
    draw,
    human_player_won,
    ai_player_won,
};

[[nodiscard]] bool game_over(const Board& board);
[[nodiscard]] WinCondition get_win_condition(const Board& board);
[[nodiscard]] bool check_player_victory(const Board& board, player_id player);

}  // namespace tic_tac_toe
