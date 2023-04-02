#include "print_square.hpp"

#include <cassert>

namespace tic_tac_toe {

std::string print_square(const Square square)
{
    assert(square.col() >= 0 && square.col() < 3);
    assert(square.row() >= 0 && square.row() < 3);

    return std::string{static_cast<char>('A' + square.col()), static_cast<char>('1' + square.row())};
}

}  // namespace tic_tac_toe
