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

    static Image<RGBPixel> computeConvolution(const Image<RGBPixel> &img, const KernelMatrix &kernel);

    static Image<HSVPixel> computeConvolution(const Image<HSVPixel> &img, const KernelMatrix &kernel);

    ImageProcessor operator=(ImageProcessor &ip) = delete;

private:
    static int reflect(const int m, const int x);
};

#endif //KERNELIMAGE_IMAGEPROCESSOR_H
