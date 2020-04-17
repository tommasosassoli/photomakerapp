//
// Created by tommaso on 25/03/20.
//

#ifndef KERNELIMAGE_PIXELMATRIX_H
#define KERNELIMAGE_PIXELMATRIX_H

#include "Pixel.h"

/**
 * This class contains a matrix of pointers to Pixels. The matrix has a standard dimension (This must be the same
 * for all PixelMatrix to makes convolution possible).
 * @param dimension is set to 3 x 3.
 */
class PixelMatrix {
private:
    const static int DIM = 3;       //should be odd to find the center the matrix
    Pixel* matrix[DIM][DIM];

public:
    PixelMatrix();

    /**
     * Takes an array of Pixel that should be the kernel to apply at the image. The array passed must have the
     * standard dimension of a PixelMatrix.
     * @param arr array of Pixel.
     * @param length length of the array.
     * @throw ImageException if the length of the array doesn't match with the standard dimension of the PixelMatrix.
     */
    explicit PixelMatrix(Pixel *arr, const int length);

    int getDimension() const;

    Pixel get(const int i, const int j) const;

    /// set a Pixel in the pixel matrix
    /// @param [in] i i-index
    /// @param [in] j j-index
    /// @param [in] p pointer to a Pixel
    void set(const int i, const int j, Pixel* p);

    /// operator* computes the convolution between two PixelMatrix with same dimensions
    friend Pixel operator*(const PixelMatrix& pm1, const PixelMatrix& pm2);

    friend bool operator==(const PixelMatrix& pm1, const PixelMatrix& pm2);
};


#endif //KERNELIMAGE_PIXELMATRIX_H
