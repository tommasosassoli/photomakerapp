//
// Created by tommaso on 26/03/20.
//

#include <cmath>
#include "ImageProcessor.h"

// CONVOLUTION
template <>
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

template <>
Image<HSVPixel> ImageProcessor::computeConvolution(const Image<HSVPixel> &img, const KernelMatrix &kernel) {
    return ImageProcessor::computeConvolution(img.convert<RGBPixel>(), kernel).convert<HSVPixel>();
}

// HUE (HSV HUE)

template<>
Image<HSVPixel> ImageProcessor::adjustHue(const Image<HSVPixel> &img, double delta) {
    if(delta < 0) delta += 360;
    else if (delta > 360) delta = fmod(delta, 360);

    Image<HSVPixel> newimg = img;
    HSVPixel* newbuff = newimg.getBuffer();
    for(int i = 0; i < img.getHeight() * img.getWidth(); i++){
        newbuff[i].setHue(newbuff[i].getHue() + delta);
    }

    return newimg;
}

template<>
Image<RGBPixel> ImageProcessor::adjustHue(const Image<RGBPixel> &img, const double delta) {
    return ImageProcessor::adjustHue(img.convert<HSVPixel>(), delta).convert<RGBPixel>();
}

// SATURATION (HSV SATURATION)

template<>
Image<HSVPixel> ImageProcessor::adjustSaturation(const Image<HSVPixel> &img, double delta) {
    if(delta < -1) delta = -1;
    else if (delta > 1) delta = 1;

    Image<HSVPixel> newimg = img;
    HSVPixel* newbuff = newimg.getBuffer();
    for(int i = 0; i < img.getHeight() * img.getWidth(); i++){
        newbuff[i].setSaturation(newbuff[i].getSaturation() * ( 1 + delta));
    }

    return newimg;
}

template<>
Image<RGBPixel> ImageProcessor::adjustSaturation(const Image<RGBPixel> &img, const double delta) {
    return ImageProcessor::adjustSaturation(img.convert<HSVPixel>(), delta).convert<RGBPixel>();
}

// BRIGHTNESS (HSV VALUE)

template<>
Image<HSVPixel> ImageProcessor::adjustValue(const Image<HSVPixel> &img, double delta) {
    if(delta < -1) delta = -1;
    else if (delta > 1) delta = 1;

    Image<HSVPixel> newimg = img;
    HSVPixel* newbuff = newimg.getBuffer();
    for(int i = 0; i < img.getHeight() * img.getWidth(); i++){
        newbuff[i].setValue(newbuff[i].getValue() + delta);
    }

    return newimg;
}

template<>
Image<RGBPixel> ImageProcessor::adjustValue(const Image<RGBPixel> &img, const double delta) {
    return ImageProcessor::adjustValue(img.convert<HSVPixel>(), delta).convert<RGBPixel>();
}

// OTHER METHODS

int ImageProcessor::reflect(const int m, const int x){
    // method to prevent index-out-of-range in a buffer
    if(x < 0)   return -x-1;
    if(x >= m)  return 2*m-x-1;
}




