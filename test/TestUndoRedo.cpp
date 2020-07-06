//
// Created by tommaso on 18/06/20.
//

#include "gtest/gtest.h"
#include <fstream>
#include "../src/command/CommandHandler.h"
#include "../src/command/CommandHandler.cpp"
#include "../src/command/FlipCommand.h"
#include "../src/command/MirrorCommand.h"

class TestUndoRedo : public ::testing::Test {
protected:
    virtual void SetUp() {
        std::ifstream imgFile("../../test/testImage/convolution/Vd-Orig.ppm");
        if(imgFile.is_open()) {
            Image<> img;
            imgFile >> img;
            testImg = std::make_shared<Image<>>(img);
        } else
            GTEST_FATAL_FAILURE_("Cannot load the test image");
    }

    shared_ptr<Image<>> testImg; //TODO controllo dell'immagine
    CommandHandler cmdHandler;
};

TEST_F(TestUndoRedo, RegisterCmd) {
    shared_ptr<FlipCommand> flipCmd = std::make_shared<FlipCommand>(testImg);
    cmdHandler.registerAndExecute(flipCmd);

    shared_ptr<MirrorCommand> mirrorCmd = std::make_shared<MirrorCommand>(testImg);
    cmdHandler.registerAndExecute(mirrorCmd);

    // get top of undo
    Command *cmd = cmdHandler.getUndoTop().get();
    MirrorCommand *mirror = dynamic_cast<MirrorCommand*>(cmd);
    if(mirror == nullptr)
        GTEST_FAIL();
}

TEST_F(TestUndoRedo, UndoCmd) {
    shared_ptr<FlipCommand> flipCmd = std::make_shared<FlipCommand>(testImg);
    cmdHandler.registerAndExecute(flipCmd);

    if(cmdHandler.isUndoPossible()) {
        cmdHandler.undo();

        if(cmdHandler.isUndoPossible())
            GTEST_FAIL();

        // get top of redo
        Command *cmdr = cmdHandler.getRedoTop().get();
        FlipCommand *mirror = dynamic_cast<FlipCommand*>(cmdr);
        if(mirror == nullptr)
            GTEST_FAIL();

    } else
        GTEST_FAIL();
}

TEST_F(TestUndoRedo, RedoCmd) {
    shared_ptr<FlipCommand> flipCmd = std::make_shared<FlipCommand>(testImg);
    cmdHandler.registerAndExecute(flipCmd);
    cmdHandler.undo();

    if(cmdHandler.isRedoPossible()) {
        cmdHandler.redo();

        if(cmdHandler.isRedoPossible())
            GTEST_FAIL();

        // get top of undo
        Command *cmd = cmdHandler.getUndoTop().get();
        FlipCommand *mirror = dynamic_cast<FlipCommand*>(cmd);
        if(mirror == nullptr)
            GTEST_FAIL();
    } else
        GTEST_FAIL();
}

TEST_F(TestUndoRedo, UndoAndRegister) {
    shared_ptr<FlipCommand> flipCmd = std::make_shared<FlipCommand>(testImg);
    cmdHandler.registerAndExecute(flipCmd);
    shared_ptr<FlipCommand> flipCmd1 = std::make_shared<FlipCommand>(testImg);
    cmdHandler.registerAndExecute(flipCmd1);
    cmdHandler.undo();

    if(cmdHandler.isRedoPossible()) {
        // get top of redo
        Command *cmd = cmdHandler.getRedoTop().get();
        FlipCommand *flip = dynamic_cast<FlipCommand*>(cmd);
        if(flip == nullptr)
            GTEST_FAIL();

        shared_ptr<MirrorCommand> mirrorCmd = std::make_shared<MirrorCommand>(testImg);
        cmdHandler.registerAndExecute(mirrorCmd);

        // now the redo stack should be empty
        if(cmdHandler.isRedoPossible())
            GTEST_FAIL();

        // get top of undo
        Command *cmd1 = cmdHandler.getUndoTop().get();
        MirrorCommand *mirror = dynamic_cast<MirrorCommand*>(cmd1);
        if(mirror == nullptr)
            GTEST_FAIL();

    } else
        GTEST_FAIL();
}
