#include "receive_player_command.hpp"

#include "fmt/core.h"
#include "scn/all.h"

#include "../output/console_writer.hpp"
#include "eval_input.hpp"

namespace tic_tac_toe {

std::string read_input(const player_id player, ConsoleWriter& console_writer)
{
    std::string input;

    while (true) {
        if (scn::prompt(fmt::format("Player {}, your move? (type \"?\" for help) ", player).c_str(), "{}", input))
            break;

        console_writer.write("invalid input\n");
    }

    return input;
}

Command receive_player_command(const player_id player, Board& board, ConsoleWriter& console_writer, CommandFactory& command_factory)
{
    while (true) {
        const auto input = read_input(player, console_writer);
        const auto command = eval_input(player, board, command_factory, input);

        if (!command)
            console_writer.write("invalid input\n");
        else
            return *command;
    }
}

}  // namespace tic_tac_toe
