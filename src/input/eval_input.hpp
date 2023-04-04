#pragma once

#include <optional>
#include <string>

#include "../command/command.hpp"
#include "../game/player.hpp"

namespace tic_tac_toe {

class Board;
class CommandFactory;

std::optional<Command> eval_input(Player player, Board& board, CommandFactory& command_factory, const std::string& input);

bool is_valid_alphabetic_input_character(char c);
bool is_valid_numeric_input_character(char c);
bool is_valid_input_character(char c);

int convert_input_character_to_square_coord(char c);

}  // namespace tic_tac_toe
