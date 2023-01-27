#include "commands.hpp"

#include <cstdlib>

#include "fmt/core.h"

#include "../app/app_controller.hpp"

namespace tic_tac_toe {

Command HelpCommand()
{
    return Command{
        []() {
            fmt::print("Enter moves like \"c2\" or \"2c\".\n\n");
            fmt::print("\"?\", \"h\", \"help\": show help\n");
            fmt::print("\"q\", \"quit\", \"exit\": quit program\n");
            fmt::print("\"u\", \"undo\": undo last command\n");
            fmt::print("\"r\", \"redo\": redo last undo\n");
        }};
}

Command QuitCommand()
{
    return Command{
        []() {
            std::exit(0);
        }};
}

Command UndoCommand(AppController* controller)
{
    return Command{
        [=]() {
            controller->undo();  // undo AI turn
            controller->undo();  // undo player turn
        }};
}

Command RedoCommand(AppController* controller)
{
    return Command{
        [=]() {
            controller->redo();  // redo player turn
            controller->redo();  // redo AI turn
        }};
}

}  // namespace tic_tac_toe
