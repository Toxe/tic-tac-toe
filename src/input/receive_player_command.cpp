#include "receive_player_command.hpp"

#include "scn/all.h"

#include "eval_input.hpp"

namespace tic_tac_toe {

std::string read_input(ConsoleWriter& console_writer)
{
    std::string input;

    while (true) {
        if (scn::prompt("Your move? (type \"?\" for help) ", "{}", input))
            break;

        console_writer.write("invalid input\n");
    }

    return input;
}

Command receive_player_command(GameState& game_state, Board& board, AppController& app_controller, ConsoleWriter& console_writer)
{
    while (true) {
        const auto input = read_input(console_writer);
        const auto command = eval_input(game_state, board, app_controller, console_writer, input);

        if (!command)
            console_writer.write("invalid input\n");
        else
            return *command;
    }
}

}  // namespace tic_tac_toe
