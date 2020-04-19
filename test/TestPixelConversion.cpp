//
// Created by tommaso on 18/04/20.
//

#include "gtest/gtest.h"
#include "../src/core/Pixel.h"
#include "../src/core/HSVPixel.h"

class TestPixelConversion : public ::testing::Test {
protected:
    void testHSVPixel(int r, int g, int b, int h, int s, int v);
};

TEST_F(TestPixelConversion, RGBtoHSV) {
    testHSVPixel(0, 0, 0, 0, 0, 0);              //black
    testHSVPixel(255, 255, 255, 0, 0, 100);      //white
    testHSVPixel(255, 0, 0, 0, 100, 100);        //red
    testHSVPixel(0, 255, 0, 120, 100, 100);      //lime
    testHSVPixel(0, 0, 255, 240, 100, 100);      //blue
    testHSVPixel(255, 255, 0, 60, 100, 100);     //yellow
    testHSVPixel(0, 255, 255, 180, 100, 100);    //cyan
    testHSVPixel(255, 0, 255, 300, 100, 100);    //magenta
    testHSVPixel(191, 191, 191, 0, 0, 75);       //silver
    testHSVPixel(128, 128, 128, 0, 0, 50);       //gray
    testHSVPixel(128, 0, 0, 0, 100, 50);         //maroon
    testHSVPixel(128, 128, 0, 60, 100, 50);      //olive
    testHSVPixel(0, 128, 0, 120, 100, 50);       //green
    testHSVPixel(128, 0, 128, 300, 100, 50);     //purple
    testHSVPixel(0, 128, 128, 180, 100, 50);     //teal
    testHSVPixel(0, 0, 128, 240, 100, 50);       //navy
}

TEST_F(TestPixelConversion, PixelTransformation){
    Pixel p(0, 255, 255);               //cyan
    HSVPixel hsvGenerated = p.toHSV();          //180, 1, 1

    //reducing saturation
    hsvGenerated.setSaturation(20);    //180, 0.2, 1
    ASSERT_EQ(Pixel(204,255,255), p);

    //reducing value
    hsvGenerated.setValue(60);            //180, 0.2, 0.6
    ASSERT_EQ(Pixel(122,153,153), p);

    //changing hue
    hsvGenerated.setHue(240);               //240, 0.2, 0.6
    ASSERT_EQ(Pixel(122,122,153), p);
}

void TestPixelConversion::testHSVPixel(int r, int g, int b, int h, int s, int v){
    Pixel p(r,g,b);
    HSVPixel hsvP(h,s,v);

    //transform RGB -> HSV
    HSVPixel hsvGenerated = p.toHSV();
    ASSERT_EQ(hsvP, hsvGenerated);

    //transform HSV -> RGB (comeback)
    hsvGenerated.updateRGBPixel();
    ASSERT_EQ(Pixel(r,g,b), p);
}