#include <utility>

#include "ai/receive_ai_command.hpp"
#include "app/app_controller.hpp"
#include "board/board.hpp"
#include "command/command_factory.hpp"
#include "game/game_players.hpp"
#include "game/win_conditions.hpp"
#include "input/receive_player_command.hpp"
#include "output/console_writer.hpp"
#include "output/show_board.hpp"
#include "output/show_game_over.hpp"

using namespace tic_tac_toe;

int main()
{
    Board board;
    GamePlayers game_players{PlayerType::human, PlayerType::ai};
    AppController controller;
    ConsoleWriter console_writer;
    const CommandFactory command_factory{board, game_players, controller, console_writer};

    while (!game_over(get_win_condition(board))) {
        const Player player = game_players.current_player();
        const bool is_human_player = player_is_human(game_players.player_info(player));

        console_writer.write(show_board(board));

        auto command = is_human_player ? receive_player_command(player, board, console_writer, command_factory) : receive_ai_command(player, board, command_factory, console_writer);
        controller.execute(std::move(command));
    }

    console_writer.write(show_board(board));
    console_writer.write(show_game_over(get_win_condition(board)));
}
