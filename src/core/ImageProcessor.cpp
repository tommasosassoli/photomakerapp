//
// Created by tommaso on 26/03/20.
//

#include "ImageProcessor.h"

/*Image computeConvolution(const Image &img, KernelMatrix &kernel) {
    Image newimg = img;     //deep copy

    int dim = kernel->getDimension();
    //PixelMatrix submatrix;
    RGBPixel **newbuffer = newimg.getBuffer();

    for(int i = 0; i < newimg.getHeight(); i++)
        for(int j = 0; j < newimg.getWidth(); j++){
            PixelMatrix submatrix = img.getSubMatrix(i, j, dim);
            newbuffer[i][j] = kernel->computeConvolution(submatrix);     //convolution
            newimg.validatePixel(newbuffer[i][j]);
        }
    return newimg;
}*/