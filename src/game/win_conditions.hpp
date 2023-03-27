#pragma once

#include "../board/board.hpp"

namespace tic_tac_toe {

enum class WinCondition {
    none,
    draw,
    player1_won,
    player2_won,
};

[[nodiscard]] bool game_over(const Board& board);
[[nodiscard]] WinCondition get_win_condition(const Board& board);
[[nodiscard]] bool check_player_victory(const Board& board, player_id player);

}  // namespace tic_tac_toe
