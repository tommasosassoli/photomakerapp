//
// Created by tommaso on 28/03/20.
//

#include "KernelTemplate.h"

RGBPixel KernelTemplate::identity[9] {
        0, 0, 0,
        0, 1, 0,
        0, 0, 0
};

RGBPixel KernelTemplate::laplatian4[9] {
        0,  1,  0,
        1, -4,  1,
        0,  1,  0
};

RGBPixel KernelTemplate::laplatian8[9] {
        -1, -1, -1,
        -1,  8, -1,
        -1, -1, -1
};

RGBPixel KernelTemplate::sharpen[9] {
         0, -1,  0,
        -1,  5, -1,
         0, -1,  0
};
