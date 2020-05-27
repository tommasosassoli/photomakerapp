//
// Created by tommaso on 25/05/20.
//

#include "CommandHandler.h"

void CommandHandler::registerAndExecute(shared_ptr<Command> cmd) {
    if(cmd != nullptr) {
        clearRedoStack();
        cmd->execute();
        undoCommands.push(std::move(cmd));
    }
}

bool CommandHandler::isUndoPossible() {
    return !undoCommands.empty();
}

shared_ptr<Command> CommandHandler::undo() {
    if(!undoCommands.empty()) {
        shared_ptr<Command> c = undoCommands.top();
        undoCommands.pop();
        return c;
    }
    return nullptr;
}

bool CommandHandler::isRedoPossible() {
    return !redoCommands.empty();
}

shared_ptr<Command> CommandHandler::redo() {
    if(!redoCommands.empty()){
        shared_ptr<Command> c = redoCommands.top();
        redoCommands.pop();
        undoCommands.push(std::move(c));
        return c;
    }
    return nullptr;
}

void CommandHandler::clearRedoStack() {
    while(!redoCommands.empty()) {
        redoCommands.pop();
    }
}

CommandHandler::~CommandHandler() {
    while(!redoCommands.empty()) {
        redoCommands.pop();
    }
    while(!undoCommands.empty()) {
        undoCommands.pop();
    }
}


