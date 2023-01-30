#include "catch2/catch_test_macros.hpp"

#include "../src/app/app_controller.hpp"
#include "../src/app/commands.hpp"

namespace tic_tac_toe {

TEST_CASE("app/commands")
{
    AppController controller;

    int value = 0;
    auto command = Command{
        .execute = [&] { ++value; },
        .undo = [&] { --value; }};

    SECTION("UndoCommand")
    {
        controller.execute(command);
        controller.execute(command);
        CHECK(value == 2);

        controller.execute(UndoCommand(&controller));
        CHECK(value == 0);
    }

    SECTION("RedoCommand")
    {
        controller.execute(command);
        controller.execute(command);
        controller.undo();
        controller.undo();
        CHECK(value == 0);

        controller.execute(RedoCommand(&controller));
        CHECK(value == 2);
    }
}

}  // namespace tic_tac_toe
