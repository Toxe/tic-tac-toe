#include "console_writer.hpp"

#include "fmt/core.h"

namespace tic_tac_toe {

void ConsoleWriter::write(const std::string& text) const
{
    if (write_output_to_console_)
        fmt::print("{}", text);
}

}  // namespace tic_tac_toe
