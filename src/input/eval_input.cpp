#include "eval_input.hpp"

#include <cassert>

#include "../board/board.hpp"
#include "../command/command_factory.hpp"

namespace tic_tac_toe {

std::optional<Command> check_keyword_commands(CommandFactory& command_factory, const std::string& input)
{
    if (input == "?" || input == "h" || input == "help")
        return command_factory.create_help_command();
    else if (input == "q" || input == "quit" || input == "exit")
        return command_factory.create_quit_command();
    else if (input == "u" || input == "undo")
        return command_factory.create_undo_command();
    else if (input == "r" || input == "redo")
        return command_factory.create_redo_command();

    return {};
}

std::optional<Command> eval_input(const Player player, Board& board, CommandFactory& command_factory, const std::string& input)
{
    // check for simple keyword commands
    if (auto command = check_keyword_commands(command_factory, input))
        return command;

    // check for player move commands
    if (input.size() != 2)
        return {};

    Square square;

    if (is_valid_alphabetic_input_character(input[0]) && is_valid_numeric_input_character(input[1]))
        square = Square{convert_input_character_to_square_coord(input[0]), convert_input_character_to_square_coord(input[1])};
    else if (is_valid_alphabetic_input_character(input[1]) && is_valid_numeric_input_character(input[0]))
        square = Square{convert_input_character_to_square_coord(input[1]), convert_input_character_to_square_coord(input[0])};
    else
        return {};

    if (!board.empty_square(square))
        return {};

    return command_factory.create_player_move_command(player, square);
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
