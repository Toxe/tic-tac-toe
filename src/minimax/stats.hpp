#pragma once

#include <chrono>
#include <string>

#include "minimax.hpp"

namespace tic_tac_toe {

class MinimaxStats {
public:
    void update(int depth);
    std::string print(const MinimaxMove& move) const;

private:
    std::chrono::steady_clock::time_point begin_ = std::chrono::steady_clock::now();
    int calls_ = 0;
    int max_depth_ = 0;
};

}  // namespace tic_tac_toe
