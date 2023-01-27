#include "commands.hpp"

#include <cassert>
#include <stdexcept>

#include "fmt/core.h"

#include "../board/board.hpp"
#include "../game/game_state.hpp"

namespace tic_tac_toe {

Command PlayerMoveCommand(GameState* game_state, Board* board, const player_id player, const Square square)
{
    assert(player == human_player_id || player == ai_player_id);

    return Command{
        .execute = [=]() {
            fmt::print("> player {} move: {}/{}\n", player, square.col, square.row);

            if (!board->empty_square(square))
                 throw std::invalid_argument("square already occupied");

            board->change_owner_of_square(square, player);
            game_state->switch_players(); },
        .undo = [=]() {
            fmt::print("> undo player {} move: {}/{}\n", player, square.col, square.row);

            if (board->player_of_square(square) != player)
                 throw std::invalid_argument("wrong owner of square");

            board->clear_owner_of_square(square);
            game_state->switch_players(); }};
}

}  // namespace tic_tac_toe
