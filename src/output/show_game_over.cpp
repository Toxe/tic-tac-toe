#include "show_game_over.hpp"

#include <stdexcept>

#include "fmt/core.h"

#include "player_symbol.hpp"

namespace tic_tac_toe {

std::string generate_ongoing_game()
{
    return "The game is not over yet.";
}

std::string generate_draw()
{
    return "Draw!";
}

std::string generate_player_victory(const Player player)
{
    return fmt::format("Player {} won!", player_symbol(player));
}

std::string show_game_over(const WinCondition win_condition)
{
    switch (win_condition) {
        case WinCondition::none: return generate_ongoing_game();
        case WinCondition::draw: return generate_draw();
        case WinCondition::player1_won: return generate_player_victory(Player::X);
        case WinCondition::player2_won: return generate_player_victory(Player::O);
        default:
            throw std::runtime_error{"invalid win condition"};
    }
}

}  // namespace tic_tac_toe
