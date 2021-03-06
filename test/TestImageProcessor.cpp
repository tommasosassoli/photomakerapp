//
// Created by tommaso on 27/03/20.
//

#include <fstream>
#include "gtest/gtest.h"
#include "../src/core/ImageProcessor.cpp"

class TestImageProcessor : public ::testing::Test {
protected:
    virtual void SetUp() {
        kernelMatrix = new KernelMatrix(kernelArray, 3);

        std::ifstream bridgeOrigFile("../../test/testImage/hsv-space/bridge-orig.ppm");
        if(bridgeOrigFile.is_open()) {
            bridgeOrigFile >> bridgeOrig;
        }
    }
    virtual void TearDown() {
        delete kernelMatrix;
    }

    double kernelArray[9] = {  0, -1,  0,
                              -1,  5, -1,
                               0, -1,  0 };
    KernelMatrix *kernelMatrix;

    Image<HSVPixel> bridgeOrig;

    void testRGBImage(std::string orig, std::string deriv);

    void testHSVImage(std::string orig, std::string deriv);

    void testRGBImage(std::string orig, std::string deriv, int x1, int y1, int x2, int y2);

    void testHue(const std::string& deriv, double delta);

    void testHue(const std::string& deriv, double delta, int x1, int y1, int x2, int y2);

    void testSaturation(const std::string& deriv, double delta);

    void testSaturation(const std::string& deriv, double delta, int x1, int y1, int x2, int y2);

    void testBrightness(const std::string& deriv, double delta);

    void testBrightness(const std::string& deriv, double delta, int x1, int y1, int x2, int y2);
};

TEST_F(TestImageProcessor, testRGBConvolution) {
    TestImageProcessor::testRGBImage("Vd-Orig", "Vd-Sharp");
}

TEST_F(TestImageProcessor, testHSVConvolution) {
    TestImageProcessor::testHSVImage("Vd-Orig", "Vd-Sharp");
}

TEST_F(TestImageProcessor, testRGBSubImageConvolution) {
    TestImageProcessor::testRGBImage("Vd-Orig", "Vd-Sharp-Sub-center", 10, 20, 90, 75);
    TestImageProcessor::testRGBImage("Vd-Orig", "Vd-Sharp-Sub-right", 80, 0, 100, 100);
    TestImageProcessor::testRGBImage("Vd-Orig", "Vd-Sharp-Sub-bottom", 0, 80, 100, 100);
    TestImageProcessor::testRGBImage("Vd-Orig", "Vd-Sharp-Sub-left", 0, 0, 40, 100);
    TestImageProcessor::testRGBImage("Vd-Orig", "Vd-Sharp-Sub-top", 0, 0, 100, 40);
}

TEST_F(TestImageProcessor, testHue){
    testHue("bridge-h180", 180);
    testHue("bridge-h330", 330);
    testHue("bridge-h35", 35);
}

TEST_F(TestImageProcessor, testHueSubImage){
    testHue("bridge-h", 180, 30, 100, 200, 150);
}

TEST_F(TestImageProcessor, testSaturation){
    testSaturation("bridge-s-100", -1);
    testSaturation("bridge-s100", 1);
    testSaturation("bridge-s50", 0.50);
}

TEST_F(TestImageProcessor, testSaturationSubImage){
    testSaturation("bridge-s", -1, 30, 100, 200, 150);
}

TEST_F(TestImageProcessor, testBrightness){
    testBrightness("bridge-v-100", -1);
    testBrightness("bridge-v100", 1);
    testBrightness("bridge-v50", 0.5);
}

TEST_F(TestImageProcessor, testBrightnessSubImage){
    testBrightness("bridge-v", -0.5, 30, 100, 200, 150);
}

TEST_F(TestImageProcessor, testCut){
    std::ifstream origFile("../../test/testImage/crop/leo.ppm");
    std::ifstream derivFile("../../test/testImage/crop/leo-crop.ppm");

    if(origFile.is_open() && derivFile.is_open()){
        try {
            Image<> origImg;
            origFile >> origImg;

            Image<> cutImg = ImageProcessor::crop(origImg, 5, 210, 250, 520);

            Image<> origDerivImg;
            derivFile >> origDerivImg;

            if(cutImg == origDerivImg)
                GTEST_SUCCEED();
            else
                GTEST_FAIL();

            origFile.close();
            derivFile.close();
        }catch(ImageException &e){
            cout << e.what() << "\nTerminated";
            GTEST_FAIL();
        }
    }
    else
        GTEST_FAIL();
}

TEST_F(TestImageProcessor, testFlip){
    std::ifstream origFile("../../test/testImage/crop/leo.ppm");
    std::ifstream derivFile("../../test/testImage/crop/leo-flip.ppm");

    if(origFile.is_open() && derivFile.is_open()){
        try {
            Image<> origImg;
            origFile >> origImg;

            Image<> rotateImg = ImageProcessor::flip(origImg);

            Image<> origDerivImg;
            derivFile >> origDerivImg;

            if(rotateImg == origDerivImg)
                GTEST_SUCCEED();
            else
                GTEST_FAIL();

            origFile.close();
            derivFile.close();
        }catch(ImageException &e){
            cout << e.what() << "\nTerminated";
            GTEST_FAIL();
        }
    }
    else
        GTEST_FAIL();
}

TEST_F(TestImageProcessor, testMirror){
    std::ifstream origFile("../../test/testImage/crop/leo.ppm");
    std::ifstream derivFile("../../test/testImage/crop/leo-mirror.ppm");

    if(origFile.is_open() && derivFile.is_open()){
        try {
            Image<> origImg;
            origFile >> origImg;

            Image<> rotateImg = ImageProcessor::mirror(origImg);

            Image<> origDerivImg;
            derivFile >> origDerivImg;

            if(rotateImg == origDerivImg)
                GTEST_SUCCEED();
            else
                GTEST_FAIL();

            origFile.close();
            derivFile.close();
        }catch(ImageException &e){
            cout << e.what() << "\nTerminated";
            GTEST_FAIL();
        }
    }
    else
        GTEST_FAIL();
}

void TestImageProcessor::testRGBImage(std::string orig, std::string deriv){
    std::ifstream origFile("../../test/testImage/convolution/" + orig +".ppm");
    std::ifstream derivFile("../../test/testImage/convolution/" + deriv + ".ppm");

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

void TestImageProcessor::testHSVImage(std::string orig, std::string deriv){
    std::ifstream origFile("../../test/testImage/convolution/" + orig +".ppm");
    std::ifstream derivFile("../../test/testImage/convolution/" + deriv + ".ppm");

    if(origFile.is_open() && derivFile.is_open()){
        try {
            Image<HSVPixel> origImg;
            origFile >> origImg;

            Image<HSVPixel> convolutionImg = ImageProcessor::computeConvolution(origImg, *kernelMatrix);

            Image<HSVPixel> origDerivImg;
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

void TestImageProcessor::testRGBImage(std::string orig, std::string deriv, int x1, int y1, int x2, int y2){
    std::ifstream origFile("../../test/testImage/convolution/" + orig +".ppm");
    std::ifstream derivFile("../../test/testImage/convolution/" + deriv + ".ppm");

    if(origFile.is_open() && derivFile.is_open()){
        try {
            Image<> origImg;
            origFile >> origImg;

            Image<> convolutionImg = ImageProcessor::computeConvolution(origImg, *kernelMatrix, x1, y1, x2, y2);

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

void TestImageProcessor::testHue(const std::string& deriv, const double delta) {
    std::ifstream derivFile("../../test/testImage/hsv-space/" + deriv + ".ppm");
    if(derivFile.is_open()) {
        Image<RGBPixel> origDerivImg;
        derivFile >> origDerivImg;

        Image<HSVPixel> derivImg = ImageProcessor::adjustHue(bridgeOrig, delta);

        if(derivImg.convert<RGBPixel>() == origDerivImg)
            GTEST_SUCCEED();
        else
            GTEST_FAIL();
    }
    else
        GTEST_FAIL();
}

void TestImageProcessor::testHue(const std::string& deriv, const double delta, int x1, int y1, int x2, int y2) {
    std::ifstream derivFile("../../test/testImage/hsv-space/sub-image/" + deriv + ".ppm");
    if(derivFile.is_open()) {
        Image<RGBPixel> origDerivImg;
        derivFile >> origDerivImg;

        Image<HSVPixel> derivImg = ImageProcessor::adjustHue(bridgeOrig, delta, x1, y1 ,x2, y2);

        if(derivImg.convert<RGBPixel>() == origDerivImg)
            GTEST_SUCCEED();
        else
            GTEST_FAIL();
    }
    else
        GTEST_FAIL();
}

void TestImageProcessor::testSaturation(const std::string& deriv, const double delta) {
    std::ifstream derivFile("../../test/testImage/hsv-space/" + deriv + ".ppm");
    if(derivFile.is_open()) {
        Image<RGBPixel> origDerivImg;
        derivFile >> origDerivImg;

        Image<HSVPixel> derivImg = ImageProcessor::adjustSaturation(bridgeOrig, delta);

        if(derivImg.convert<RGBPixel>() == origDerivImg)
            GTEST_SUCCEED();
        else
            GTEST_FAIL();
    }
    else
        GTEST_FAIL();
}

void TestImageProcessor::testSaturation(const std::string& deriv, const double delta, int x1, int y1, int x2, int y2) {
    std::ifstream derivFile("../../test/testImage/hsv-space/sub-image/" + deriv + ".ppm");
    if(derivFile.is_open()) {
        Image<RGBPixel> origDerivImg;
        derivFile >> origDerivImg;

        Image<HSVPixel> derivImg = ImageProcessor::adjustSaturation(bridgeOrig, delta, x1, y1, x2, y2);

        if(derivImg.convert<RGBPixel>() == origDerivImg)
            GTEST_SUCCEED();
        else
            GTEST_FAIL();
    }
    else
        GTEST_FAIL();
}

void TestImageProcessor::testBrightness(const std::string& deriv, const double delta) {
    std::ifstream derivFile("../../test/testImage/hsv-space/" + deriv + ".ppm");
    if(derivFile.is_open()) {
        Image<RGBPixel> origDerivImg;
        derivFile >> origDerivImg;

        Image<HSVPixel> derivImg = ImageProcessor::adjustValue(bridgeOrig, delta);

        if(derivImg.convert<RGBPixel>() == origDerivImg)
            GTEST_SUCCEED();
        else
            GTEST_FAIL();
    }
    else
        GTEST_FAIL();
}

void TestImageProcessor::testBrightness(const std::string& deriv, const double delta, int x1, int y1, int x2, int y2) {
    std::ifstream derivFile("../../test/testImage/hsv-space/sub-image/" + deriv + ".ppm");
    if(derivFile.is_open()) {
        Image<RGBPixel> origDerivImg;
        derivFile >> origDerivImg;

        Image<HSVPixel> derivImg = ImageProcessor::adjustValue(bridgeOrig, delta, x1, y1, x2, y2);

        if(derivImg.convert<RGBPixel>() == origDerivImg)
            GTEST_SUCCEED();
        else
            GTEST_FAIL();
    }
    else
        GTEST_FAIL();
}