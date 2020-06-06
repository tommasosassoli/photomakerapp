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
        redoCommands.push(c);
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
        undoCommands.push(c);
        return c;
    }
    return nullptr;
}

void CommandHandler::clearRedoStack() {
    while(!redoCommands.empty()) {
        redoCommands.pop();
    }
}

void CommandHandler::resetAll() {
    // clear the stacks
    while(!redoCommands.empty()) {
        redoCommands.pop();
    }
    while(!undoCommands.empty()) {
        undoCommands.pop();
    }
}

CommandHandler::~CommandHandler() {
    resetAll();
}

shared_ptr<Command> CommandHandler::getUndoTop() const {
    return undoCommands.top();
}

shared_ptr<Command> CommandHandler::getRedoTop() const {
    return redoCommands.top();
}
