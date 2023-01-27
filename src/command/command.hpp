#pragma once

#include <functional>

namespace tic_tac_toe {

struct Command {
    std::function<void()> execute;
    std::function<void()> undo = nullptr;

    bool has_undo() const { return undo != nullptr; }
};

}  // namespace tic_tac_toe
