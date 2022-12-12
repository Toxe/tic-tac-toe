#include "console_output.hpp"

#include "fmt/core.h"

namespace tic_tac_toe {

void console_output(const std::string& output)
{
    fmt::print("{}", output);
}

}  // namespace tic_tac_toe
