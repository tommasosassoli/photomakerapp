//
// Created by tommaso on 26/03/20.
//

#include "ImageProcessor.h"

ImageProcessor::ImageProcessor(Pixel *arr, const int length) {
    kernel = new PixelMatrix(arr, length);
}

ImageProcessor::~ImageProcessor() {
    delete kernel;
}

Image ImageProcessor::applyConvolution(const Image &img) {
    Image newimg = img;     //deep copy

    PixelMatrix submatrix;
    Pixel **newbuffer = newimg.getBuffer();

    for(int i = 0; i < newimg.getHeight(); i++)
        for(int j = 0; j < newimg.getWidth(); j++){
            submatrix = img.getSubMatrix(i, j);
            newbuffer[i][j] = submatrix * (*kernel);     //convolution
            newimg.validatePixel(newbuffer[i][j]);
        }
    return newimg;
}