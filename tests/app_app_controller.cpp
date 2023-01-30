#include "catch2/catch_test_macros.hpp"

#include "../src/app/app_controller.hpp"
#include "../src/command/command.hpp"

namespace tic_tac_toe {

Command make_command(int* value, const int add)
{
    return Command{
        .execute = [=] { *value += add; },
        .undo = [=] { *value -= add; }};
}

TEST_CASE("app/app_controller")
{
    AppController controller;
    int value = 0;

    SECTION("execute, undo and redo")
    {
        // execute
        controller.execute(make_command(&value, 3));
        CHECK(value == 3);

        controller.execute(make_command(&value, 2));
        CHECK(value == 5);

        controller.execute(make_command(&value, 4));
        CHECK(value == 9);

        // undo
        controller.undo();
        CHECK(value == 5);

        controller.undo();
        CHECK(value == 3);

        controller.undo();
        CHECK(value == 0);

        // redo
        controller.redo();
        CHECK(value == 3);

        controller.redo();
        CHECK(value == 5);

        controller.redo();
        CHECK(value == 9);
    }

    SECTION("empty undo and redo stacks")
    {
        controller.execute(make_command(&value, 1));
        controller.execute(make_command(&value, 2));
        controller.execute(make_command(&value, 3));
        CHECK(value == 6);

        // undo
        controller.undo();
        controller.undo();
        controller.undo();
        CHECK(value == 0);

        // empty undo stack
        controller.undo();
        CHECK(value == 0);

        controller.undo();
        CHECK(value == 0);

        // redo
        controller.redo();
        controller.redo();
        controller.redo();
        CHECK(value == 6);

        // empty redo stack
        controller.redo();
        CHECK(value == 6);

        controller.redo();
        CHECK(value == 6);
    }

    SECTION("clear redo stack after executing new commands")
    {
        controller.execute(make_command(&value, 1));
        controller.execute(make_command(&value, 2));
        controller.execute(make_command(&value, 3));
        CHECK(value == 6);

        controller.undo();
        controller.undo();
        CHECK(value == 1);

        controller.execute(make_command(&value, 10));
        CHECK(value == 11);

        // empty redo stack
        controller.redo();
        CHECK(value == 11);
    }
}

}  // namespace tic_tac_toe
