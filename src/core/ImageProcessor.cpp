//
// Created by tommaso on 18/05/20.
//

#ifndef PHOTOMAKERAPP_IMAGEPROCESSOR_CPP
#define PHOTOMAKERAPP_IMAGEPROCESSOR_CPP

#include <cmath>
#include "../model/Image.h"
#include "../model/KernelMatrix.h"

// OTHER METHODS

inline int reflect(const int m, const int x){
    // method to prevent index-out-of-range in a buffer
    if(x < 0)   return -x-1;
    if(x >= m)  return 2*m-x-1;
}

namespace ImageProcessor {
    template<typename T, typename = std::enable_if<std::is_base_of<AbstractPixel, T>::value>>
    Image<T> crop(const Image<T> &img, int x1, int y1, int x2, int y2);

    template<typename T, typename = std::enable_if<std::is_base_of<AbstractPixel, T>::value>>
    Image<T> overlap(const Image<T> &img, const Image<T> &topImg, int x, int y);

// CONVOLUTION

    inline Image<RGBPixel> computeConvolution(const Image<RGBPixel> &img, const KernelMatrix &kernel) {
        Image<RGBPixel> newimg = img.cloneInfo();

        int kernelDim = kernel.getDim();
        int dev = kernelDim / 2;
        int width = img.getWidth();
        int height = img.getHeight();

        double *kernelBuf = kernel.getKernel();
        RGBPixel *newBuff = newimg.getBuffer();
        RGBPixel *imgBuff = img.getBuffer();

        RGBPixel pixelVal;
        double kernelVal;

        for (int r = 0; r < height; r++) {
            for (int c = 0; c < width; c++) {
                int pr = 0, pg = 0, pb = 0;
                for (int i = 0; i < kernelDim; i++) {
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

    inline Image<HSVPixel> computeConvolution(const Image<HSVPixel> &img, const KernelMatrix &kernel) {
        return computeConvolution(img.convert<RGBPixel>(), kernel).convert<HSVPixel>();
    }

    inline Image<RGBPixel> computeConvolution(const Image<RGBPixel> &img, const KernelMatrix &kernel,
            int x1, int y1, int x2, int y2) {
        Image<> cropImg = ImageProcessor::crop(img, y1, x1, y2, x2);
        Image<> convImg = ImageProcessor::computeConvolution(cropImg, kernel);
        return ImageProcessor::overlap(img, convImg, x1, y1);
    }

// HUE (HSV HUE)

    inline Image<HSVPixel> adjustHue(const Image<HSVPixel> &img, double delta) {
        if (delta < 0) delta += 360;
        else if (delta > 360) delta = fmod(delta, 360);

        Image<HSVPixel> newimg = img;
        HSVPixel *newbuff = newimg.getBuffer();
        for (int i = 0; i < img.getHeight() * img.getWidth(); i++) {
            newbuff[i].setHue(newbuff[i].getHue() + delta);
        }

        return newimg;
    }

    inline Image<RGBPixel> adjustHue(const Image<RGBPixel> &img, const double delta) {
        return adjustHue(img.convert<HSVPixel>(), delta).convert<RGBPixel>();
    }

// SATURATION (HSV SATURATION)

    inline Image<HSVPixel> adjustSaturation(const Image<HSVPixel> &img, double delta) {
        if (delta < -1) delta = -1;
        else if (delta > 1) delta = 1;

        Image<HSVPixel> newimg = img;
        HSVPixel *newbuff = newimg.getBuffer();
        for (int i = 0; i < img.getHeight() * img.getWidth(); i++) {
            newbuff[i].setSaturation(newbuff[i].getSaturation() * (1 + delta));
        }

        return newimg;
    }

    inline Image<RGBPixel> adjustSaturation(const Image<RGBPixel> &img, const double delta) {
        return adjustSaturation(img.convert<HSVPixel>(), delta).convert<RGBPixel>();
    }

// BRIGHTNESS (HSV VALUE)

    inline Image<HSVPixel> adjustValue(const Image<HSVPixel> &img, double delta) {
        if (delta < -1) delta = -1;
        else if (delta > 1) delta = 1;

        Image<HSVPixel> newimg = img;
        HSVPixel *newbuff = newimg.getBuffer();
        for (int i = 0; i < img.getHeight() * img.getWidth(); i++) {
            newbuff[i].setValue(newbuff[i].getValue() + delta);
        }

        return newimg;
    }

    inline Image<RGBPixel> adjustValue(const Image<RGBPixel> &img, const double delta) {
        return adjustValue(img.convert<HSVPixel>(), delta).convert<RGBPixel>();
    }

//  CROP

    template<typename T, typename>
    Image<T> crop(const Image<T> &img, int x1, int y1, int x2, int y2) {
        if ((x2 > x1) && (y2 > y1) &&
            (x1 >= 0) && (y1 >= 0) &&
            (x2 <= img.getHeight()) && (y2 <= img.getWidth())) {
            int height = x2 - x1;
            int width = y2 - y1;
            Image<T> newimg(width, height);

            T *newbuff = new T[width * height];
            T *buff = img.getBuffer();
            for (int i = x1; i < x2; i++) {
                for (int j = y1; j < y2; j++) {
                    newbuff[(i - x1) * width + (j - y1)] = buff[i * img.getWidth() + j];
                }
            }
            newimg.setBuffer(newbuff);

            return newimg;
        } else
            throw ImageException("Dimensions for crop are not valid.");
    }

//  OVERLAP

    template<typename T, typename>
    Image<T> overlap(const Image<T> &img, const Image<T> &topImg, int x, int y) {
        if ((x >= 0) && (y >= 0) && (x < img.getWidth()) && (y < img.getHeight())) {
            int height = img.getHeight();
            int width = img.getWidth();
            Image<T> newimg(width, height);

            T *newbuff = new T[width * height];
            T *oldbuff = img.getBuffer();
            T *topbuff = topImg.getBuffer();

            int maxWidth = (topImg.getWidth()+x > width) ? width : topImg.getWidth()+x;
            int maxHeight = (topImg.getHeight()+y > height) ? height : topImg.getHeight()+y;
            for (int i = 0; i < height; i++) {
                for (int j = 0; j < width; j++) {
                    if((i >= y && i < maxHeight) && (j >= x && j < maxWidth))
                        newbuff[i * width + j] = topbuff[(i-y) * topImg.getWidth() + (j-x)];
                    else
                        newbuff[i * width + j] = oldbuff[i * width + j];
                }
            }
            newimg.setBuffer(newbuff);

            return newimg;
        } else
            throw ImageException("Coordinates for overlap are not valid.");
    }

//  FLIP

    template<typename T, typename = std::enable_if<std::is_base_of<AbstractPixel, T>::value>>
    Image<T> flip(const Image<T> &img) {
        Image<T> newimg = img.cloneInfo();
        int height = img.getHeight();
        int width = img.getWidth();

        T *newbuff = new T[height * width];
        T *buff = img.getBuffer();
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                newbuff[(height - i - 1) * width + j] = buff[i * img.getWidth() + j];
            }
        }
        newimg.setBuffer(newbuff);

        return newimg;
    }

//  MIRROR

    template<typename T, typename = std::enable_if<std::is_base_of<AbstractPixel, T>::value>>
    Image<T> mirror(const Image<T> &img) {
        Image<T> newimg = img.cloneInfo();
        int height = img.getHeight();
        int width = img.getWidth();

        T *newbuff = new T[height * width];
        T *buff = img.getBuffer();
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                newbuff[i * width + (width - j - 1)] = buff[i * img.getWidth() + j];
            }
        }
        newimg.setBuffer(newbuff);

        return newimg;
    }


//TODO implementa filtro su ritaglio

//TODO rotazione (90 gradi)

};

#endif //PHOTOMAKERAPP_IMAGEPROCESSOR_CPP