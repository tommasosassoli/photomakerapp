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

    template <typename T, typename = std::enable_if<std::is_base_of<AbstractPixel, T>::value>>
    static Image<T> computeConvolution(const Image<T> &img, const KernelMatrix &kernel);

    template <typename T, typename = std::enable_if<std::is_base_of<AbstractPixel, T>::value>>
    static Image<T> adjustHue(const Image<T> &img, double delta);

    template <typename T, typename = std::enable_if<std::is_base_of<AbstractPixel, T>::value>>
    static Image<T> adjustSaturation(const Image<T> &img, double delta);

    template <typename T, typename = std::enable_if<std::is_base_of<AbstractPixel, T>::value>>
    static Image<T> adjustValue(const Image<T> &img, double delta);

    ImageProcessor operator=(ImageProcessor &ip) = delete;

private:
    static int reflect(const int m, const int x);
};

#endif //KERNELIMAGE_IMAGEPROCESSOR_H
