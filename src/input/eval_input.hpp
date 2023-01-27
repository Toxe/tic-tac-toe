#pragma once

#include <optional>
#include <string>

#include "../app/app_controller.hpp"
#include "../board/board.hpp"
#include "../command/command.hpp"
#include "../game/game_state.hpp"
#include "../output/console_writer.hpp"

namespace tic_tac_toe {

std::optional<Command> eval_input(GameState& game_state, Board& board, AppController& app_controller, ConsoleWriter& console_writer, const std::string& input);

bool is_valid_alphabetic_input_character(char c);
bool is_valid_numeric_input_character(char c);
bool is_valid_input_character(char c);

int convert_input_character_to_square_coord(char c);

}  // namespace tic_tac_toe
