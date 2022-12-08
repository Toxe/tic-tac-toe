#include "ai/receive_ai_command.hpp"
#include "game/board.hpp"
#include "game/execute_command.hpp"
#include "game/game_state.hpp"
#include "input/receive_player_command.hpp"
#include "output/show_output.hpp"

using namespace tic_tac_toe;

int main()
{
    GameState game_state{};
    Board board{};

    while (!board.game_over()) {
        show_output(board);

        const auto command = (player_is_human(game_state.current_player())) ? receive_player_command(board) : receive_ai_command(board);
        execute_command(board, command);

        game_state.switch_players();
    }
}
