//
// Created by tommaso on 26/03/20.
//

#ifndef KERNELIMAGE_IMAGEPROCESSOR_H
#define KERNELIMAGE_IMAGEPROCESSOR_H

#include <cmath>
#include "../model/KernelMatrix.h"
#include "../model/Image.h"

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

    template <typename T, typename = std::enable_if<std::is_base_of<AbstractPixel, T>::value>>
    static Image<T> cut(const Image<T> &img, const int x1, const int y1, const int x2, const int y2);

    template <typename T, typename = std::enable_if<std::is_base_of<AbstractPixel, T>::value>>
    static Image<T> flip(const Image<T> &img);

    template <typename T, typename = std::enable_if<std::is_base_of<AbstractPixel, T>::value>>
    static Image<T> mirror(const Image<T> &img);

    ImageProcessor operator=(ImageProcessor &ip) = delete;

private:
    static int reflect(const int m, const int x);
};

//  CUT

template<typename T, typename>
Image<T> ImageProcessor::cut(const Image<T> &img, const int x1, const int y1, const int x2, const int y2) {//TODO crop
    if((x2 > x1) && (y2 > y1) &&
       (x1 >= 0) && (y1 >= 0) &&
       (x2 < img.getHeight()) && (y2 < img.getWidth())){
        int height = x2 - x1;
        int width = y2 - y1;
        Image<T> newimg(width, height);

        T* newbuff = new T[width * height];
        T* buff = img.getBuffer();
        for(int i = x1; i < x2; i++){
            for(int j = y1; j < y2; j++){
                newbuff[(i - x1) * width + (j - y1)] = buff[i * img.getWidth() + j];
            }
        }
        newimg.setBuffer(newbuff);

        return newimg;
    } else
        throw ImageException("Dimensions for cut are not valid.");
}


template<typename T, typename>
Image<T> ImageProcessor::flip(const Image<T> &img) {
    Image<T> newimg = img.cloneInfo();
    int height = img.getHeight();
    int width = img.getWidth();

    T* newbuff = new T[height * width];
    T* buff = img.getBuffer();
    for(int i = 0; i < height; i++){
        for(int j = 0; j < width; j++){
                newbuff[(height - i - 1) * width + j] = buff[i * img.getWidth() + j];
        }
    }
    newimg.setBuffer(newbuff);

    return newimg;
}

template<typename T, typename>
Image<T> ImageProcessor::mirror(const Image<T> &img) {
    Image<T> newimg = img.cloneInfo();
    int height = img.getHeight();
    int width = img.getWidth();

    T* newbuff = new T[height * width];
    T* buff = img.getBuffer();
    for(int i = 0; i < height; i++){
        for(int j = 0; j < width; j++){
            newbuff[i * width + (width - j - 1)] = buff[i * img.getWidth() + j];
        }
    }
    newimg.setBuffer(newbuff);

    return newimg;
}

#endif //KERNELIMAGE_IMAGEPROCESSOR_H
