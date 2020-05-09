//
// Created by tommaso on 18/04/20.
//

#include <fstream>
#include "gtest/gtest.h"
#include "../src/model/Image.h"

class TestPixelConversion : public ::testing::Test {
protected:
    void testHSVPixel(int r, int g, int b, double h, double s, double v);
};

TEST_F(TestPixelConversion, RGBtoHSV) {
    testHSVPixel(0, 0, 0,       0, 0, 0);       //black
    testHSVPixel(255, 255, 255, 0, 0, 1);       //white
    testHSVPixel(255, 0, 0,     0, 1, 1);       //red
    testHSVPixel(0, 255, 0,     120, 1, 1);     //lime
    testHSVPixel(0, 0, 255,     240, 1, 1);     //blue
    testHSVPixel(255, 255, 0,   60, 1, 1);      //yellow
    testHSVPixel(0, 255, 255,   180, 1, 1);     //cyan
    testHSVPixel(255, 0, 255,   300, 1, 1);     //magenta
    testHSVPixel(191, 191, 191, 0, 0, 0.75);    //silver
    testHSVPixel(128, 128, 128, 0, 0, 0.50);    //gray
    testHSVPixel(128, 0, 0,     0, 1, 0.50);    //maroon
    testHSVPixel(128, 128, 0,   60, 1, 0.50);   //olive
    testHSVPixel(0, 128, 0,     120, 1, 0.50);  //green
    testHSVPixel(128, 0, 128,   300, 1, 0.50);  //purple
    testHSVPixel(0, 128, 128,   180, 1, 0.50);  //teal
    testHSVPixel(0, 0, 128,     240, 1, 0.50);  //navy
    testHSVPixel(132, 131, 137, 250, 0.044,0.537);  //random color
}

TEST_F(TestPixelConversion, PixelTransformation){
    RGBPixel rgbP(0, 255, 255);               //cyan
    HSVPixel hsvGenerated = rgbP.toHSV();          //180, 1, 1

    //reducing saturation
    hsvGenerated.setSaturation(0.2);    //180, 0.2, 1
    ASSERT_EQ(RGBPixel(204,255,255), hsvGenerated.toRGB());

    //reducing value
    hsvGenerated.setValue(0.6);            //180, 0.2, 0.6
    ASSERT_EQ(RGBPixel(122,153,153), hsvGenerated.toRGB());

    //changing hue
    hsvGenerated.setHue(240);               //240, 0.2, 0.6
    ASSERT_EQ(RGBPixel(122,122,153), hsvGenerated.toRGB());
}

TEST_F(TestPixelConversion, TestImageRGBtoHSV) {
    std::ifstream origFile("../../test/testImage/Vd-Orig.ppm");

    if(origFile.is_open()){
        try {
            Image<> origImg;
            origFile >> origImg;

            Image<HSVPixel> conv = origImg.convert<HSVPixel>();

            Image<RGBPixel> back = conv.convert<RGBPixel>();

            if(origImg == back)
                GTEST_SUCCEED();
            else
                GTEST_FAIL();

            origFile.close();
        }catch(ImageException &e){
            cout << e.what() << "\nTerminated";
        }
    }
    else
        GTEST_FAIL();
}

void TestPixelConversion::testHSVPixel(int r, int g, int b, double h, double s, double v){
    RGBPixel rgbP(r,g,b);
    HSVPixel hsvP(h,s,v);

    //transform RGB -> HSV
    HSVPixel hsvGenerated = rgbP.toHSV();
    ASSERT_EQ(hsvP, hsvGenerated);

    //transform HSV -> RGB
    RGBPixel rgbGenerated = hsvP.toRGB();
    ASSERT_EQ(rgbP, rgbGenerated);
}