//
// Created by tommaso on 27/03/20.
//

#include <fstream>
#include "gtest/gtest.h"
#include "../src/core/ImageProcessor.h"

class TestImageProcessor : public ::testing::Test {
protected:
    virtual void SetUp() {
        kernelMatrix = new KernelMatrix(kernelArray, 3);
    }
    virtual void TearDown() {
        delete kernelMatrix;
    }

    double kernelArray[9] = {  0, -1,  0,
                              -1,  5, -1,
                               0, -1,  0 };
    KernelMatrix *kernelMatrix;

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
            Image<> origImg;
            origFile >> origImg;

            Image<> convolutionImg = ImageProcessor::computeConvolution(origImg, *kernelMatrix);

            Image<> origDerivImg;
            derivFile >> origDerivImg;

            if(convolutionImg == origDerivImg)
                GTEST_SUCCEED();
            else
                GTEST_FAIL();

            origFile.close();
            derivFile.close();
        }catch(ImageException &e){
            cout << e.what() << "\nTerminated";
        }
    }
    else
        GTEST_FAIL();
}