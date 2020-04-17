//
// Created by tommaso on 27/03/20.
//

#include <fstream>
#include "gtest/gtest.h"
#include "../src/core/ImageProcessor.h"

class TestImageProcessor : public ::testing::Test {
protected:
    Pixel kernelArray[9] = { 0, -1,  0,
                            -1,  5, -1,
                             0, -1,  0 };
    ImageProcessor *imgProc;

    virtual void SetUp() {
        imgProc = new ImageProcessor(kernelArray, 9);
    }

    virtual void TearDown() {
        delete imgProc;
    }

    void testImage(std::string orig, std::string deriv);
};

TEST_F(TestImageProcessor, testConvolution) {
    TestImageProcessor::testImage("Vd-Orig", "Vd-Sharp");
}

void TestImageProcessor::testImage(std::string orig, std::string deriv){
    std::ifstream origFile("../../test/testImage/" + orig +".ppm");
    std::ifstream derivFile("../../test/testImage/" + deriv + ".ppm");

    if(origFile.is_open() && derivFile.is_open()){
        try {
            Image origImg;
            origFile >> origImg;

            Image convolutionImg = imgProc->applyConvolution(origImg);

            Image origDerivImg;
            derivFile >> origDerivImg;

            ASSERT_EQ(convolutionImg, origDerivImg);

            origFile.close();
            derivFile.close();
        }catch(ImageException &e){
            cout << e.what() << "\nTerminated";
        }
    }
    else
        GTEST_FAIL();
}