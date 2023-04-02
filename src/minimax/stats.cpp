#include "stats.hpp"

#include <algorithm>

#include "fmt/core.h"

using namespace std::literals::chrono_literals;

namespace tic_tac_toe {

std::string format_duration(std::chrono::nanoseconds dur)
{
    if (dur < 10us)
        return fmt::format("{:.3f} us", std::chrono::duration_cast<std::chrono::duration<float, std::micro>>(dur).count());
    else
        return fmt::format("{:.3f} ms", std::chrono::duration_cast<std::chrono::duration<float, std::milli>>(dur).count());
}

void MinimaxStats::update(const int depth)
{
    ++calculations_;
    max_depth_ = std::max(max_depth_, depth);
}

std::string MinimaxStats::print() const
{
    return fmt::format("> calculated {} moves in {} (depth: {})\n", calculations_, format_duration(std::chrono::steady_clock::now() - begin_), max_depth_);
}

}  // namespace tic_tac_toe
