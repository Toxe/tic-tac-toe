#include "eval_input.hpp"

#include <cassert>

namespace tic_tac_toe {

std::optional<int> eval_input(const Board& board, const std::string& input)
{
    if (input.empty() || input.size() > 2)
        return std::nullopt;

    if (!is_valid_input_digit(input[0]) || !is_valid_input_digit(input[1]))
        return std::nullopt;

    const Square square{convert_input_digit_to_square_coord(input[0]), convert_input_digit_to_square_coord(input[1])};

    if (!board.empty_square(square))
        return std::nullopt;

    return 1;
}

bool is_valid_input_digit(const char c)
{
    return c >= '1' && c <= '3';
}

int convert_input_digit_to_square_coord(const char c)
{
    assert(c >= '1' && c <= '3');

    return c - '1';  // convert '1'..'3' to 0..2
}

}  // namespace tic_tac_toe
