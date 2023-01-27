#pragma once

#include "../board/square.hpp"
#include "../command/command.hpp"
#include "../game/player.hpp"

namespace tic_tac_toe {

class Board;
class GameState;

Command PlayerMoveCommand(GameState* game_state, Board* board, player_id player, Square square);

}  // namespace tic_tac_toe
