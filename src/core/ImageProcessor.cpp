//
// Created by tommaso on 26/03/20.
//

#include "ImageProcessor.h"

Image<RGBPixel> ImageProcessor::computeConvolution(const Image<RGBPixel> &img, const KernelMatrix &kernel) {
    Image<RGBPixel> newimg = img.cloneInfo();

    int kernelDim = kernel.getDim();
    int dev = kernelDim / 2;
    int width = img.getWidth();
    int height = img.getHeight();

    double* kernelBuf = kernel.getKernel();
    RGBPixel* newBuff = newimg.getBuffer();
    RGBPixel* imgBuff = img.getBuffer();

    RGBPixel pixelVal;
    double kernelVal;

    for(int r = 0; r < height; r++){
        for(int c = 0; c < width; c++){
            int pr = 0, pg = 0, pb = 0;
            for(int i = 0; i < kernelDim; i++) {
                for (int j = 0; j < kernelDim; j++) {
                    pixelVal = imgBuff[reflect(height, r + i - dev) * width + reflect(width, c + j - dev)];
                    kernelVal = kernelBuf[(kernelDim - i - 1) * kernelDim + (kernelDim - j - 1)];

                    pr += pixelVal.getR() * kernelVal;
                    pg += pixelVal.getG() * kernelVal;
                    pb += pixelVal.getB() * kernelVal;
                }
            }
            newBuff[r * width + c] = RGBPixel(pr, pg, pb);
        }
    }
    return newimg;
}

Image<HSVPixel> ImageProcessor::computeConvolution(const Image<HSVPixel> &img, const KernelMatrix &kernel) {
    return ImageProcessor::computeConvolution(img.convert<RGBPixel>(), kernel).convert<HSVPixel>();
}

int ImageProcessor::reflect(const int m, const int x){
    // method to prevent index-out-of-range in a buffer
    if(x < 0)   return -x-1;
    if(x >= m)  return 2*m-x-1;
}


