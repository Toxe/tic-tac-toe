#include "receive_player_command.hpp"

#include "fmt/core.h"
#include "scn/all.h"

#include "eval_input.hpp"

namespace tic_tac_toe {

Command receive_player_command(const Board& board)
{
    while (true) {
        std::string input;

        scn::prompt("? ", "{}", input);

        const auto command = eval_input(board, input);

        if (!command)
            fmt::print("invalid input\n");
        else
            return *command;
    }
}

}  // namespace tic_tac_toe
