//
// Created by tommaso on 27/03/20.
//

#include "gtest/gtest.h"
#include "../Pixel.h"
#include "../PixelMatrix.h"

TEST(TestPixelMatrix, constructorWithArray) {
    Pixel pArr[9] = {Pixel(0,0,0), Pixel(1,1,1),Pixel(1,1,1),
                     Pixel(1,1,1),Pixel(1,1,1),Pixel(1,1,1),
                     Pixel(1,1,1),Pixel(1,1,1),Pixel(1,0,1) };

    PixelMatrix pm(pArr, 9);
    ASSERT_NO_THROW(pm);
}
