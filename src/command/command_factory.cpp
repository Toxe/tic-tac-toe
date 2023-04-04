#include "command_factory.hpp"

#include "../app/commands.hpp"
#include "../game/commands.hpp"

namespace tic_tac_toe {

Command CommandFactory::create_player_move_command(const Player player, const Square square)
{
    return PlayerMoveCommand(game_players_, board_, console_writer_, player, square);
}

Command CommandFactory::create_help_command()
{
    return HelpCommand(console_writer_);
}

Command CommandFactory::create_quit_command()
{
    return QuitCommand();
}

Command CommandFactory::create_undo_command()
{
    return UndoCommand(controller_, game_players_);
}

Command CommandFactory::create_redo_command()
{
    return RedoCommand(controller_, game_players_);
}

}  // namespace tic_tac_toe
