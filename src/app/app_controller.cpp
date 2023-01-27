#include "app_controller.hpp"

#include <utility>

namespace tic_tac_toe {

void AppController::execute(Command command)
{
    command.execute();

    if (command.has_undo()) {
        undo_stack_.push(std::move(command));
        redo_stack_ = {};
    }
}

void AppController::undo()
{
    if (undo_stack_.empty())
        return;

    auto command = std::move(undo_stack_.top());
    undo_stack_.pop();

    command.undo();

    redo_stack_.push(std::move(command));
}

void AppController::redo()
{
    if (redo_stack_.empty())
        return;

    auto command = std::move(redo_stack_.top());
    redo_stack_.pop();

    command.execute();

    undo_stack_.push(std::move(command));
}

}  // namespace tic_tac_toe
