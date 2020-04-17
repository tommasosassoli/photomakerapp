//
// Created by tommaso on 26/03/20.
//

#ifndef KERNELIMAGE_IMAGEPROCESSOR_H
#define KERNELIMAGE_IMAGEPROCESSOR_H

#include "PixelMatrix.h"
#include "Image.h"

class ImageProcessor {
private:
    PixelMatrix *kernel;

public:
    ImageProcessor(Pixel *arr, const int length);

    ImageProcessor(ImageProcessor &ip) = delete;

    ~ImageProcessor();

    Image applyConvolution(const Image &img);

    ImageProcessor operator=(ImageProcessor &ip) = delete;
};


#endif //KERNELIMAGE_IMAGEPROCESSOR_H
