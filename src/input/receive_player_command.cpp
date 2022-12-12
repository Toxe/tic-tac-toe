#include "receive_player_command.hpp"

#include "fmt/core.h"
#include "scn/all.h"

#include "eval_input.hpp"

namespace tic_tac_toe {

std::string read_input()
{
    std::string input;

    while (true) {
        if (scn::prompt("? ", "{}", input))
            break;

        fmt::print("invalid input\n");
    }

    return input;
}

Command receive_player_command(const Board& board)
{
    while (true) {
        const auto input = read_input();
        const auto command = eval_input(board, input);

        if (!command)
            fmt::print("invalid input\n");
        else
            return *command;
    }
}

}  // namespace tic_tac_toe
