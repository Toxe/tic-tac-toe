#include "catch2/catch_test_macros.hpp"

#include "../src/command/command.hpp"

namespace tic_tac_toe {

TEST_CASE("command/command")
{
    SECTION("supports undo")
    {
        const auto command_with_undo = Command{
            .execute = [] { return 1; },
            .undo = [] { return 2; }};

        const auto command_without_undo1 = Command{
            .execute = [] { return 1; },
            .undo = nullptr};

        const auto command_without_undo2 = Command{
            .execute = [] { return 1; }};

        CHECK(command_with_undo.has_undo() == true);
        CHECK(command_without_undo1.has_undo() == false);
        CHECK(command_without_undo2.has_undo() == false);
    }
}

}  // namespace tic_tac_toe
