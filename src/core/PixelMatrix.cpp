//
// Created by tommaso on 25/03/20.
//

#include "PixelMatrix.h"
#include "ImageException.h"

PixelMatrix::PixelMatrix() {
}

PixelMatrix::PixelMatrix(Pixel *arr, const int length) {
    if(length == DIM*DIM) {
        for (int i = 0; i < DIM; i++) {
            for (int j = 0; j < DIM; j++) {
                matrix[i][j] = &arr[i * DIM + j];
            }
        }
    } else
        throw ImageException("The length of the array must be: " + DIM*DIM);
}

int PixelMatrix::getDimension() const {
    return PixelMatrix::DIM;
}

Pixel PixelMatrix::get(const int i, const int j) const {
    return *matrix[i][j];
}

void PixelMatrix::set(const int i, const int j, Pixel* p) {
    matrix[i][j] = p;
}

//TODO specialize pixelmatrix with kernelmatrix (custom dim and moltip.) and customize operator*
Pixel operator*(const PixelMatrix &pm1, const PixelMatrix &pm2) {
    Pixel res;
    for (int i = 0; i < PixelMatrix::DIM; i++)
        for (int j = 0; j < PixelMatrix::DIM; j++) {
            res = res + pm1.get(i, j) * pm2.get(PixelMatrix::DIM-1-i, PixelMatrix::DIM-1-j);
        }
    return res;
}

bool operator==(const PixelMatrix &pm1, const PixelMatrix &pm2) {
    int nEq = 0;
    for (int i = 0; i < PixelMatrix::DIM; i++)
        for (int j = 0; j < PixelMatrix::DIM; j++)
            if(*pm1.matrix[i][j] == *pm2.matrix[i][j]) nEq++;
    return (nEq == (PixelMatrix::DIM*PixelMatrix::DIM)) ? true : false;
}

