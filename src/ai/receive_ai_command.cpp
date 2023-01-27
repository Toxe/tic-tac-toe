#include "receive_ai_command.hpp"

#include <cassert>
#include <random>
#include <stdexcept>
#include <vector>

#include "../game/commands.hpp"

namespace tic_tac_toe {

std::vector<Square> get_all_empty_squares(const Board& board)
{
    std::vector<Square> all_empty_squares;

    for (int row = 0; row < 3; ++row)
        for (int col = 0; col < 3; ++col)
            if (board.empty_square({row, col}))
                all_empty_squares.emplace_back(row, col);

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

Command receive_ai_command(GameState& game_state, Board& board, ConsoleWriter& console_writer)
{
    const auto all_empty_squares = get_all_empty_squares(board);

    if (all_empty_squares.empty())
        throw std::invalid_argument("invalid row or column");

    return PlayerMoveCommand(&game_state, &board, &console_writer, ai_player_id, pick_random_empty_square(all_empty_squares));
}

}  // namespace tic_tac_toe
