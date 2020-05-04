//
// Created by tommaso on 28/03/20.
//

#ifndef KERNELIMAGE_KERNELTEMPLATE_H
#define KERNELIMAGE_KERNELTEMPLATE_H

#include "pixels/RGBPixel.h"

class KernelTemplate {
public:
    static double identity[9];
    static double laplatian4[9];
    static double laplatian8[9];
    static double sharpen[9];
    //static RGBPixel boxBlur[9];
    //static const RGBPixel gaussianBlur5x5[9];

public:
    KernelTemplate() = delete;
};


#endif //KERNELIMAGE_KERNELTEMPLATE_H
