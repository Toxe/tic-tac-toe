#include "game/execute_command.hpp"
#include "game/game_state.hpp"
#include "input/read_command.hpp"
#include "output/show_output.hpp"

int main()
{
    tic_tac_toe::GameState game_state;

    while (true) {
        tic_tac_toe::show_output(game_state);
        const auto command = tic_tac_toe::read_command();
        tic_tac_toe::execute_command(game_state, command);
    }
}
