#include <utility>

#include "ai/receive_ai_command.hpp"
#include "app/app_controller.hpp"
#include "board/board.hpp"
#include "command/command_factory.hpp"
#include "game/game_state.hpp"
#include "game/win_conditions.hpp"
#include "input/receive_player_command.hpp"
#include "output/console_writer.hpp"
#include "output/show_board.hpp"
#include "output/show_game_over.hpp"

using namespace tic_tac_toe;

int main()
{
    Board board;
    GameState game_state{PlayerType::human, PlayerType::ai};
    AppController controller;
    ConsoleWriter console_writer;
    CommandFactory command_factory{board, game_state, controller, console_writer};

    while (!game_over(board)) {
        const PlayerInfo player = game_state.current_player();

        if (player_is_human(player))
            console_writer.write(show_board(board));

        auto command = (player_is_human(player)) ? receive_player_command(player.id, board, console_writer, command_factory) : receive_ai_command(player.id, board, command_factory, console_writer);
        controller.execute(std::move(command));
    }

    console_writer.write(show_board(board));
    console_writer.write(show_game_over(get_win_condition(board)));
}
