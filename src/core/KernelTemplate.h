//
// Created by tommaso on 28/03/20.
//

#ifndef KERNELIMAGE_KERNELTEMPLATE_H
#define KERNELIMAGE_KERNELTEMPLATE_H

#include "Pixel.h"

class KernelTemplate {
public:
    static Pixel identity[9];
    static Pixel laplatian4[9];
    static Pixel laplatian8[9];
    static Pixel sharpen[9];
    //static Pixel boxBlur[9];
    //static const Pixel gaussianBlur5x5[9];

public:
    KernelTemplate() = delete;
};


#endif //KERNELIMAGE_KERNELTEMPLATE_H
