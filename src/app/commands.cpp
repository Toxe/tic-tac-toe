#include "commands.hpp"

#include <cstdlib>
#include <string>

#include "../app/app_controller.hpp"
#include "../output/console_writer.hpp"

namespace tic_tac_toe {

Command HelpCommand(ConsoleWriter* console_writer)
{
    return Command{
        [=]() {
            const std::string output = R"(Enter moves like "c2" or "2c".

"?", "h", "help": show help
"q", "quit", "exit": quit program
"u", "undo": undo last command
"r", "redo": redo last undo
)";

            console_writer->write(output);
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
