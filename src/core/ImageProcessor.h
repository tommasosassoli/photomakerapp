//
// Created by tommaso on 26/03/20.
//

#ifndef KERNELIMAGE_IMAGEPROCESSOR_H
#define KERNELIMAGE_IMAGEPROCESSOR_H

#include "KernelMatrix.h"
#include "Image.h"

class ImageProcessor {
public:
    ImageProcessor(ImageProcessor &ip) = delete;

    ~ImageProcessor();

    //Image computeConvolution(const Image &img, KernelMatrix &kernel);//TODO implementa la convoluzione

    ImageProcessor operator=(ImageProcessor &ip) = delete;
};

#endif //KERNELIMAGE_IMAGEPROCESSOR_H
