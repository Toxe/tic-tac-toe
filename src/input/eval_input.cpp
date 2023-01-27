#include "eval_input.hpp"

#include <cassert>

#include "../app/commands.hpp"
#include "../game/commands.hpp"

namespace tic_tac_toe {

std::optional<Command> check_keyword_commands(AppController& app_controller, const std::string& input)
{
    if (input == "?" || input == "h" || input == "help")
        return HelpCommand();
    else if (input == "q" || input == "quit" || input == "exit")
        return QuitCommand();
    else if (input == "u" || input == "undo")
        return UndoCommand(&app_controller);
    else if (input == "r" || input == "redo")
        return RedoCommand(&app_controller);

    return {};
}

std::optional<Command> eval_input(GameState& game_state, Board& board, AppController& app_controller, const std::string& input)
{
    // check for simple keyword commands
    if (auto command = check_keyword_commands(app_controller, input))
        return command;

    // check for player move commands
    if (input.size() != 2)
        return {};

    Square square;

    if (is_valid_alphabetic_input_character(input[0]) && is_valid_numeric_input_character(input[1]))
        square = Square{convert_input_character_to_square_coord(input[1]), convert_input_character_to_square_coord(input[0])};
    else if (is_valid_alphabetic_input_character(input[1]) && is_valid_numeric_input_character(input[0]))
        square = Square{convert_input_character_to_square_coord(input[0]), convert_input_character_to_square_coord(input[1])};
    else
        return {};

    if (!board.empty_square(square))
        return {};

    return PlayerMoveCommand(&game_state, &board, human_player_id, square);
}

bool is_valid_alphabetic_input_character(const char c)
{
    return (c >= 'a' && c <= 'c') || (c >= 'A' && c <= 'C');
}

bool is_valid_numeric_input_character(const char c)
{
    return (c >= '1' && c <= '3');
}

bool is_valid_input_character(const char c)
{
    return is_valid_alphabetic_input_character(c) || is_valid_numeric_input_character(c);
}

int convert_input_character_to_square_coord(const char c)
{
    assert(is_valid_input_character(c));

    if (is_valid_numeric_input_character(c))
        return c - '1';  // convert '1'..'3' to 0..2

    return (c >= 'a' && c <= 'c') ? c - 'a' : c - 'A';  // convert 'a'..'c' or 'A'..'C' to 0..2
}

}  // namespace tic_tac_toe
