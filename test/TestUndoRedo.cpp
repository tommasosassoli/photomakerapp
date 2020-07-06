//
// Created by tommaso on 18/06/20.
//

#include "gtest/gtest.h"
#include <fstream>
#include "../src/command/CommandHandler.h"
#include "../src/command/CommandHandler.cpp"
#include "../src/command/FlipCommand.h"
#include "../src/command/MirrorCommand.h"
#include "../src/view/ImageWrapper.h"
#include "../src/view/ImageWrapper.cpp"

class TestUndoRedo : public ::testing::Test, public Observer {
public:
    void update() override {
        testImg = imgWrapper->getImage();
    }

protected:
    virtual void SetUp() {
        std::ifstream imgFile("../../test/testImage/convolution/Vd-Orig.ppm");
        if(imgFile.is_open()) {
            Image<> img;
            imgFile >> img;
            origTestImg = std::make_shared<Image<>>(img);

            imgWrapper = new ImageWrapper();
            imgWrapper->addObserver(this);
        } else
            GTEST_FATAL_FAILURE_("Cannot load the test image");
    }

    virtual void TearDown() {
        if(imgWrapper != nullptr) {
            imgWrapper->removeObserver(this);
            delete imgWrapper;
        }
    }

    shared_ptr<Image<>> origTestImg;
    shared_ptr<Image<>> testImg;
    CommandHandler cmdHandler;
    ImageWrapper* imgWrapper {nullptr};
};


TEST_F(TestUndoRedo, RegisterCmd) {
    testImg.reset();

    shared_ptr<FlipCommand> flipCmd = std::make_shared<FlipCommand>(origTestImg);
    cmdHandler.registerAndExecute(flipCmd);
    imgWrapper->setImage(flipCmd->getParsedImage());

    shared_ptr<MirrorCommand> mirrorCmd = std::make_shared<MirrorCommand>(origTestImg);
    cmdHandler.registerAndExecute(mirrorCmd);
    imgWrapper->setImage(mirrorCmd->getParsedImage());

    // get top of undo
    Command *cmd = cmdHandler.getUndoTop().get();
    MirrorCommand *mirror = dynamic_cast<MirrorCommand*>(cmd);
    if(mirror == nullptr)
        GTEST_FAIL();

    if(!(testImg == mirrorCmd->getParsedImage()))
        GTEST_FAIL();
}

TEST_F(TestUndoRedo, UndoCmd) {
    testImg.reset();

    shared_ptr<FlipCommand> flipCmd = std::make_shared<FlipCommand>(origTestImg);
    cmdHandler.registerAndExecute(flipCmd);
    imgWrapper->setImage(flipCmd->getParsedImage());

    if(cmdHandler.isUndoPossible()) {
        shared_ptr<Command> undoCmd = cmdHandler.undo();
        imgWrapper->setImage(undoCmd->getPreviousImage());

        if(cmdHandler.isUndoPossible())
            GTEST_FAIL();

        // get top of redo
        Command *cmdr = cmdHandler.getRedoTop().get();
        FlipCommand *flip = dynamic_cast<FlipCommand*>(cmdr);
        if(flip == nullptr)
            GTEST_FAIL();

        if(!(testImg == undoCmd->getPreviousImage()))
            GTEST_FAIL();

    } else
        GTEST_FAIL();
}

TEST_F(TestUndoRedo, RedoCmd) {
    testImg.reset();

    shared_ptr<FlipCommand> flipCmd = std::make_shared<FlipCommand>(origTestImg);
    cmdHandler.registerAndExecute(flipCmd);
    imgWrapper->setImage(flipCmd->getParsedImage());
    cmdHandler.undo();
    imgWrapper->setImage(flipCmd->getPreviousImage());

    if(cmdHandler.isRedoPossible()) {
        shared_ptr<Command> redoCmd = cmdHandler.redo();
        imgWrapper->setImage(redoCmd->getParsedImage());

        if(cmdHandler.isRedoPossible())
            GTEST_FAIL();

        // get top of undo
        Command *cmd = cmdHandler.getUndoTop().get();
        FlipCommand *mirror = dynamic_cast<FlipCommand*>(cmd);
        if(mirror == nullptr)
            GTEST_FAIL();

        if(!(testImg == redoCmd->getParsedImage()))
            GTEST_FAIL();

    } else
        GTEST_FAIL();
}

TEST_F(TestUndoRedo, UndoAndRegister) {
    testImg.reset();

    shared_ptr<FlipCommand> flipCmd = std::make_shared<FlipCommand>(origTestImg);
    cmdHandler.registerAndExecute(flipCmd);
    imgWrapper->setImage(flipCmd->getParsedImage());
    shared_ptr<FlipCommand> flipCmd1 = std::make_shared<FlipCommand>(origTestImg);
    cmdHandler.registerAndExecute(flipCmd1);
    imgWrapper->setImage(flipCmd1->getParsedImage());

    shared_ptr<Command> undoCmd = cmdHandler.undo();
    imgWrapper->setImage(undoCmd->getPreviousImage());

    if(cmdHandler.isRedoPossible()) {
        // get top of redo
        Command *cmd = cmdHandler.getRedoTop().get();
        FlipCommand *flip = dynamic_cast<FlipCommand*>(cmd);
        if(flip == nullptr)
            GTEST_FAIL();

        if(!(testImg == undoCmd->getPreviousImage()))
            GTEST_FAIL();

        shared_ptr<MirrorCommand> mirrorCmd = std::make_shared<MirrorCommand>(origTestImg);
        cmdHandler.registerAndExecute(mirrorCmd);
        imgWrapper->setImage(mirrorCmd->getParsedImage());

        // now the redo stack should be empty
        if(cmdHandler.isRedoPossible())
            GTEST_FAIL();

        // get top of undo
        Command *cmd1 = cmdHandler.getUndoTop().get();
        MirrorCommand *mirror = dynamic_cast<MirrorCommand*>(cmd1);
        if(mirror == nullptr)
            GTEST_FAIL();

        if(!(testImg == mirrorCmd->getParsedImage()))
            GTEST_FAIL();

    } else
        GTEST_FAIL();
}
