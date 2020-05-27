//
// Created by tommaso on 25/05/20.
//

#ifndef PHOTOMAKERAPP_COMMANDHANDLER_H
#define PHOTOMAKERAPP_COMMANDHANDLER_H

#include <stack>
#include <memory>
#include "Command.h"

class CommandHandler {
public:
    ~CommandHandler();

    void registerAndExecute(shared_ptr<Command> cmd);

    bool isUndoPossible();

    shared_ptr<Command> undo();

    bool isRedoPossible();

    shared_ptr<Command> redo();

private:
    std::stack<shared_ptr<Command>> undoCommands;

    std::stack<shared_ptr<Command>> redoCommands;

    void clearRedoStack();
};


#endif //PHOTOMAKERAPP_COMMANDHANDLER_H
