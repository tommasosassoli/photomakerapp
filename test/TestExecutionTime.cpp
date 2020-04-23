//
// Created by tommaso on 14/04/20.
//

#include <fstream>
#include "gtest/gtest.h"
#include "../src/core/Image.h"
#include "../src/core/ImageProcessor.h"
#include "../src/core/KernelTemplate.h"

class DISABLED_TestExecutionTime : public ::testing::Test {
protected:
    std::ifstream bigImgFile;       //ferrari.ppm (2005 x 1254)
    Image<> img;

    virtual void SetUp() {
        try {
            bigImgFile.open("../../test/testImage/ferrari.ppm");
            if (bigImgFile.is_open())
                bigImgFile >> img;

            //proc = new ImageProcessor(KernelTemplate::laplatian8, 9);
        }catch (ImageException &e){
            GTEST_FATAL_FAILURE_(e.what());
        }
    }

    virtual void TearDown() {
        if(bigImgFile.is_open())
            bigImgFile.close();
    }
};


TEST_F(DISABLED_TestExecutionTime, executionTime) {
    //proc->applyConvolution(img);
}
