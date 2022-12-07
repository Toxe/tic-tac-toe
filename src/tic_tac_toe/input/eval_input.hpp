#pragma once

#include <optional>
#include <string>

#include "../game/board.hpp"

namespace tic_tac_toe {

std::optional<int> eval_input(const Board& board, const std::string& input);

bool is_valid_input_digit(char c);
int convert_input_digit_to_square_coord(char c);

}  // namespace tic_tac_toe