#include "receive_ai_command.hpp"

#include <cassert>
#include <random>
#include <stdexcept>
#include <vector>

#include "../board/board.hpp"
#include "../command/command_factory.hpp"

namespace tic_tac_toe {

std::vector<Square> get_all_empty_squares(const Board& board)
{
    std::vector<Square> all_empty_squares;

    for (int row = 0; row < board.rows(); ++row)
        for (int col = 0; col < board.cols(); ++col)
            if (board.empty_square({col, row}))
                all_empty_squares.emplace_back(col, row);

    return all_empty_squares;
}

Square pick_random_empty_square(const std::vector<Square>& all_empty_squares)
{
    assert(!all_empty_squares.empty());

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<std::size_t> dist(0, all_empty_squares.size() - 1);

    return all_empty_squares[dist(gen)];
}

Command receive_ai_command(const player_id player, const Board& board, CommandFactory& command_factory)
{
    const auto all_empty_squares = get_all_empty_squares(board);

    if (all_empty_squares.empty())
        throw std::invalid_argument("invalid row or column");

    return command_factory.create_player_move_command(player, pick_random_empty_square(all_empty_squares));
}

}  // namespace tic_tac_toe
