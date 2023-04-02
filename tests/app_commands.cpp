#include "catch2/catch_test_macros.hpp"

#include "../src/app/app_controller.hpp"
#include "../src/app/commands.hpp"
#include "../src/game/game_state.hpp"

namespace tic_tac_toe {

TEST_CASE("app/commands")
{
    AppController controller;

    int value = 0;
    auto command = Command{
        .execute = [&] { ++value; },
        .undo = [&] { --value; }};

    SECTION("human vs. human")
    {
        const GameState game_state{PlayerType::human, PlayerType::human};

        SECTION("UndoCommand")
        {
            controller.execute(command);
            controller.execute(command);
            CHECK(value == 2);

            controller.execute(UndoCommand(&controller, &game_state));
            CHECK(value == 1);

            controller.execute(UndoCommand(&controller, &game_state));
            CHECK(value == 0);
        }

        SECTION("RedoCommand")
        {
            controller.execute(command);
            controller.execute(command);
            controller.undo();
            controller.undo();
            CHECK(value == 0);

            controller.execute(RedoCommand(&controller, &game_state));
            CHECK(value == 1);

            controller.execute(RedoCommand(&controller, &game_state));
            CHECK(value == 2);
        }
    }

    SECTION("human vs. AI")
    {
        const GameState game_state{PlayerType::human, PlayerType::ai};

        SECTION("UndoCommand")
        {
            controller.execute(command);
            controller.execute(command);
            CHECK(value == 2);

            controller.execute(UndoCommand(&controller, &game_state));
            CHECK(value == 0);
        }

        SECTION("RedoCommand")
        {
            controller.execute(command);
            controller.execute(command);
            controller.undo();
            controller.undo();
            CHECK(value == 0);

            controller.execute(RedoCommand(&controller, &game_state));
            CHECK(value == 2);
        }
    }
}

}  // namespace tic_tac_toe
