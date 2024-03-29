#include "show_board.hpp"

#include <cassert>
#include <sstream>

#include "player_symbol.hpp"

namespace tic_tac_toe {

void generate_empty_line(std::stringstream& out)
{
    out << '\n';
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
    out << "  A   B   C\n";
}

void generate_cell(std::stringstream& out, const Board& board, const Square square)
{
    if (board.empty_square(square))
        out << "   ";
    else
        out << ' ' << player_symbol(board.player_of_square(square)) << ' ';
}

void generate_row(std::stringstream& out, const Board& board, const int row)
{
    for (int col = 0; col < board.cols(); ++col) {
        generate_vertical_line(out);
        generate_cell(out, board, {col, row});
    }

    generate_vertical_line(out);
    generate_row_number(out, row);
}

std::string show_board(const Board& board)
{
    std::stringstream out;

    generate_empty_line(out);

    for (int row = 0; row < board.rows(); ++row) {
        generate_horizontal_line(out);
        generate_row(out, board, row);
    }

    generate_horizontal_line(out);
    generate_column_numbers(out);
    generate_empty_line(out);

    return out.str();
}

}  // namespace tic_tac_toe
