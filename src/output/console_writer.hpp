#pragma once

#include <string>

namespace tic_tac_toe {

class ConsoleWriter {
public:
    ConsoleWriter(const bool write_output = true) : write_output_to_console_{write_output} { }

    void write(const std::string& text) const;

private:
    bool write_output_to_console_;
};

}  // namespace tic_tac_toe
