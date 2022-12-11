#include "eval_input.hpp"

#include <cassert>

namespace tic_tac_toe {

std::optional<Command> eval_input(const Board& board, const std::string& input)
{
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

    return Command{human_player_id, square};
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
