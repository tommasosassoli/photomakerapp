//
// Created by tommaso on 24/03/20.
//

#include "gtest/gtest.h"
#include "../src/core/Image.h"

/// Test for the class Image.
/// @test for submatrix: TopLeft, CenterRight, Center, BottomLeft.
/// @test for Image class: copy.
class TestRectangleImage : public ::testing::Test {
protected:
    Image img;
    virtual void SetUp() {
        istringstream s("P3 5 3 1  "
                        "1 0 0  0 1 0  0 1 1  1 0 1  1 1 1  "
                        "0 0 1  1 1 1  0 0 0  0 0 1  1 0 0  "
                        "0 0 0  0 1 1  1 0 1  0 1 0  0 0 0");
        s >> img;
    }
};

TEST_F(TestRectangleImage, getSubMatrixTopLeft) {
    PixelMatrix pm;         //hypothetical result TOP LEFT square
    Pixel *arr = new Pixel[9];
    arr[0] = Pixel(1,0,0);      pm.set(0,0,&arr[0]);
    arr[1] = Pixel(1,0,0);      pm.set(0,1,&arr[1]);
    arr[2] = Pixel(0,1,0);      pm.set(0,2,&arr[2]);
    arr[3] = Pixel(1,0,0);      pm.set(1,0,&arr[3]);
    arr[4] = Pixel(1,0,0);      pm.set(1,1,&arr[4]);
    arr[5] = Pixel(0,1,0);      pm.set(1,2,&arr[5]);
    arr[6] = Pixel(0,0,1);      pm.set(2,0,&arr[6]);
    arr[7] = Pixel(0,0,1);      pm.set(2,1,&arr[7]);
    arr[8] = Pixel(1,1,1);      pm.set(2,2,&arr[8]);

    PixelMatrix pmres = img.getSubMatrix(0,0);
    ASSERT_EQ(pm, pmres);

    delete[] arr;
}

TEST_F(TestRectangleImage, getSubMatrixCenterRight) {
    PixelMatrix pm;         //hypothetical result CENTER RIGHT square
    Pixel *arr = new Pixel[9];
    arr[0] = Pixel(1,0,1);      pm.set(0,0,&arr[0]);
    arr[1] = Pixel(1,1,1);      pm.set(0,1,&arr[1]);
    arr[2] = Pixel(1,1,1);      pm.set(0,2,&arr[2]);
    arr[3] = Pixel(0,0,1);      pm.set(1,0,&arr[3]);
    arr[4] = Pixel(1,0,0);      pm.set(1,1,&arr[4]);
    arr[5] = Pixel(1,0,0);      pm.set(1,2,&arr[5]);
    arr[6] = Pixel(0,1,0);      pm.set(2,0,&arr[6]);
    arr[7] = Pixel(0,0,0);      pm.set(2,1,&arr[7]);
    arr[8] = Pixel(0,0,0);      pm.set(2,2,&arr[8]);

    PixelMatrix pmres = img.getSubMatrix(1,4);
    ASSERT_EQ(pm, pmres);

    delete[] arr;
}

TEST_F(TestRectangleImage, getSubMatrixCenter) {
    PixelMatrix pm;         //hypothetical result CENTER square
    Pixel *arr = new Pixel[9];
    arr[0] = Pixel(0,1,0);      pm.set(0,0,&arr[0]);
    arr[1] = Pixel(0,1,1);      pm.set(0,1,&arr[1]);
    arr[2] = Pixel(1,0,1);      pm.set(0,2,&arr[2]);
    arr[3] = Pixel(1,1,1);      pm.set(1,0,&arr[3]);
    arr[4] = Pixel(0,0,0);      pm.set(1,1,&arr[4]);
    arr[5] = Pixel(0,0,1);      pm.set(1,2,&arr[5]);
    arr[6] = Pixel(0,1,1);      pm.set(2,0,&arr[6]);
    arr[7] = Pixel(1,0,1);      pm.set(2,1,&arr[7]);
    arr[8] = Pixel(0,1,0);      pm.set(2,2,&arr[8]);

    PixelMatrix pmres = img.getSubMatrix(1,2);
    ASSERT_EQ(pm, pmres);

    delete[] arr;
}

TEST_F(TestRectangleImage, getSubMatrixBottomLeft) {
    PixelMatrix pm;         //hypothetical result BOTTOM LEFT square
    Pixel *arr = new Pixel[9];
    arr[0] = Pixel(0,0,1);      pm.set(0,0,&arr[0]);
    arr[1] = Pixel(0,0,1);      pm.set(0,1,&arr[1]);
    arr[2] = Pixel(1,1,1);      pm.set(0,2,&arr[2]);
    arr[3] = Pixel(0,0,0);      pm.set(1,0,&arr[3]);
    arr[4] = Pixel(0,0,0);      pm.set(1,1,&arr[4]);
    arr[5] = Pixel(0,1,1);      pm.set(1,2,&arr[5]);
    arr[6] = Pixel(0,0,0);      pm.set(2,0,&arr[6]);
    arr[7] = Pixel(0,0,0);      pm.set(2,1,&arr[7]);
    arr[8] = Pixel(0,1,1);      pm.set(2,2,&arr[8]);

    PixelMatrix pmres = img.getSubMatrix(2,0);
    ASSERT_EQ(pm, pmres);

    delete[] arr;
}

TEST_F(TestRectangleImage, imageCopy) {
    Image i2 = img;

    ostringstream imgOut;
    ostringstream i2Out;
    imgOut << img;
    i2Out << i2;

    ASSERT_EQ(i2Out.str(), imgOut.str());
}
