#include "show_game_over.hpp"

#include <stdexcept>

namespace tic_tac_toe {

std::string generate_ongoing_game()
{
    return "The game is not over yet.";
}

std::string generate_draw()
{
    return "Draw!";
}

std::string generate_human_player_victory()
{
    return "You won!";
}

std::string generate_ai_player_victory()
{
    return "You lost!";
}

std::string show_game_over(const WinCondition win_condition)
{
    switch (win_condition) {
        case WinCondition::none: return generate_ongoing_game();
        case WinCondition::draw: return generate_draw();
        case WinCondition::human_player_won: return generate_human_player_victory();
        case WinCondition::ai_player_won: return generate_ai_player_victory();
        default:
            throw std::runtime_error{"invalid win condition"};
    }
}

}  // namespace tic_tac_toe
