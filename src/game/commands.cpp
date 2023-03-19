#include "commands.hpp"

#include <cassert>
#include <stdexcept>

#include "fmt/core.h"

#include "../board/board.hpp"
#include "../game/game_state.hpp"
#include "../output/console_writer.hpp"

namespace tic_tac_toe {

Command PlayerMoveCommand(GameState* game_state, Board* board, ConsoleWriter* console_writer, const player_id player, const Square square)
{
    assert(player_id_is_valid(player));

    return Command{
        .execute = [=]() {
            console_writer->write(fmt::format("> player {} move: {}/{}\n", player, square.col(), square.row()));

            if (!board->empty_square(square))
                 throw std::invalid_argument("square already occupied");

            board->change_owner_of_square(square, player);
            game_state->switch_players(); },
        .undo = [=]() {
            console_writer->write(fmt::format("> undo player {} move: {}/{}\n", player, square.col(), square.row()));

            if (board->player_of_square(square) != player)
                 throw std::invalid_argument("wrong owner of square");

            board->clear_owner_of_square(square);
            game_state->switch_players(); }};
}

}  // namespace tic_tac_toe
