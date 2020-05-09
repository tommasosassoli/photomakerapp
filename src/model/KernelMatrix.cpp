//
// Created by tommaso on 22/04/20.
//

#include "KernelMatrix.h"
#include "../core/ImageException.h"

KernelMatrix::KernelMatrix(double *kernel, const int dim) {
    setDim(dim);
    KernelMatrix::kernel = kernel;
}

int KernelMatrix::getDim() const {
    return dim;
}

double *KernelMatrix::getKernel() const {
    return kernel;
}

void KernelMatrix::setDim(int length) {
    if(length > 0 && (length % 2 != 0))
        KernelMatrix::dim = length;
    else
        throw ImageException("Kernel dim not valid");
}