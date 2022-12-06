#include "generate_output.hpp"

#include <cassert>
#include <sstream>

namespace tic_tac_toe::detail {

char player_symbol(player_id player)
{
    assert(player == 1 || player == 2);

    return player == 1 ? 'X' : 'O';
}

void generate_horizontal_line(std::stringstream& out)
{
    out << "+---+---+---+\n";
}

void generate_vertical_line(std::stringstream& out)
{
    out << '|';
}

void generate_newline(std::stringstream& out)
{
    out << '\n';
}

void generate_cell(std::stringstream& out, const GameState& game_state, const int row, const int col)
{
    if (game_state.is_empty_cell(row, col))
        out << ' ' << (row * 3 + col + 1) << ' ';
    else
        out << ' ' << player_symbol(game_state.get_player_of_cell(row, col)) << ' ';
}

void generate_row(std::stringstream& out, const GameState& game_state, const int row)
{
    for (int col = 0; col < 3; ++col) {
        generate_vertical_line(out);
        generate_cell(out, game_state, row, col);
    }

    generate_vertical_line(out);
    generate_newline(out);
}

std::string generate_output(const GameState& game_state)
{
    std::stringstream out;

    for (int row = 0; row < 3; ++row) {
        generate_horizontal_line(out);
        generate_row(out, game_state, row);
    }

    generate_horizontal_line(out);

    return out.str();
}

}  // namespace tic_tac_toe::detail
