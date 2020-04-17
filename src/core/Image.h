//
// Created by tommaso on 20/03/20.
//

#ifndef IMAGEPARSER_IMAGE_H
#define IMAGEPARSER_IMAGE_H

#include <istream>
#include "Pixel.h"
#include "PixelMatrix.h"
#include "ImageException.h"

class Image {
private:
    const std::string format = "P3";
    int width;
    int height;
    int maxVal;
    Pixel **buffer;

    int reflect(const int m, const int x) const;

public:
    explicit Image(int width = 0, int height = 0, int maxVal = 0);

    Image(const Image& that);

    ~Image();

    int getWidth() const;

    void setWidth(int width);

    int getHeight() const;

    void setHeight(int height);

    int getMaxVal() const;

    void setMaxVal(int maxVal);

    Pixel **getBuffer() const;

    void setBuffer(Pixel **buffer);

    /**
        Return a PixelMatrix that contains a square matrix with pointers
        to Pixels of the Image, takes by a position in the Image Pixels matrix.
        @param [in] i i-index in the Image.
        @param [in] j j-index in the Image.
        @return The function takes back a square matrix of Pixels that should be convolutional multiplying with
        an image kernel.
     */
    PixelMatrix getSubMatrix(const int i, const int j) const;

    /**
     * The function validate a pixel. It set the value between a range (0 and max value possible for an Image).
     * @param pixel by reference.
     * @return a Pixel.
     */
    void validatePixel(Pixel &p);

    /**
        Print a formatted output for the Image.
     */
    std::string toString();

    Image &operator=(const Image &that);

    friend std::ostream &operator<<(std::ostream &os, const Image &image);

    friend std::istream &operator>>(std::istream &is, Image &image) throw (ImageException);

    friend bool operator==(const Image& p1, const Image& p2);
};

#endif //IMAGEPARSER_IMAGE_H
