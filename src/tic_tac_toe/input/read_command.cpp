#include "read_command.hpp"

#include "scn/all.h"

namespace tic_tac_toe {

int read_command()
{
    int command{};

    scn::prompt("? ", "{}", command);

    return command;
}

}  // namespace tic_tac_toe
