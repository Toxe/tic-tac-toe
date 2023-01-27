#include <utility>

#include "ai/receive_ai_command.hpp"
#include "app/app_controller.hpp"
#include "board/board.hpp"
#include "game/game_state.hpp"
#include "game/win_conditions.hpp"
#include "input/receive_player_command.hpp"
#include "output/console_output.hpp"
#include "output/show_board.hpp"
#include "output/show_game_over.hpp"

using namespace tic_tac_toe;

int main()
{
    GameState game_state{};
    Board board{};
    AppController controller{};

    while (!game_over(board)) {
        if (game_state.current_player() == human_player_id)
            console_output(show_board(board));

        auto command = (player_is_human(game_state.current_player())) ? receive_player_command(game_state, board, controller) : receive_ai_command(game_state, board);
        controller.execute(std::move(command));
    }

    console_output(show_board(board));
    console_output(show_game_over(get_win_condition(board)));
}
