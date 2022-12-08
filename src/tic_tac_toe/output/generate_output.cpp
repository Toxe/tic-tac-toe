#include "generate_output.hpp"

#include <cassert>
#include <sstream>

namespace tic_tac_toe {

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

void generate_row_number(std::stringstream& out, const int row)
{
    out << ' ' << (row + 1) << '\n';
}

void generate_column_numbers(std::stringstream& out)
{
    out << "  1   2   3\n";
}

void generate_cell(std::stringstream& out, const Board& board, const Square square)
{
    if (board.empty_square(square))
        out << "   ";
    else
        out << ' ' << player_symbol(board.get_player_of_square(square)) << ' ';
}

void generate_row(std::stringstream& out, const Board& board, const int row)
{
    for (int col = 0; col < 3; ++col) {
        generate_vertical_line(out);
        generate_cell(out, board, {row, col});
    }

    generate_vertical_line(out);
    generate_row_number(out, row);
}

std::string generate_output(const Board& board)
{
    std::stringstream out;

    for (int row = 0; row < 3; ++row) {
        generate_horizontal_line(out);
        generate_row(out, board, row);
    }

    generate_horizontal_line(out);
    generate_column_numbers(out);

    return out.str();
}

}  // namespace tic_tac_toe
