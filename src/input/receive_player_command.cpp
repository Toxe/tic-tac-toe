#include "receive_player_command.hpp"

#include "scn/all.h"

#include "../output/console_writer.hpp"
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

Command receive_player_command(Board& board, ConsoleWriter& console_writer, CommandFactory& command_factory)
{
    while (true) {
        const auto input = read_input(console_writer);
        const auto command = eval_input(board, command_factory, input);

        if (!command)
            console_writer.write("invalid input\n");
        else
            return *command;
    }
}

}  // namespace tic_tac_toe
