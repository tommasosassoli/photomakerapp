//
// Created by tommaso on 28/03/20.
//

#ifndef KERNELIMAGE_KERNELTEMPLATE_H
#define KERNELIMAGE_KERNELTEMPLATE_H

#include "pixels/RGBPixel.h"

class KernelTemplate {
public:
    static RGBPixel identity[9];
    static RGBPixel laplatian4[9];
    static RGBPixel laplatian8[9];
    static RGBPixel sharpen[9];
    //static RGBPixel boxBlur[9];
    //static const RGBPixel gaussianBlur5x5[9];

public:
    KernelTemplate() = delete;
};


#endif //KERNELIMAGE_KERNELTEMPLATE_H
