//
// Created by tommaso on 22/04/20.
//

#ifndef PHOTOMAKERAPP_KERNELMATRIX_H
#define PHOTOMAKERAPP_KERNELMATRIX_H

class KernelMatrix {
private:
    int dim;
    double *kernel {nullptr};

    void setDim(const int dim);

public:
    /**
     * @param arr: pointer to an array of double
     * @param dim: dimension of the matrix. If the matrix is 3x3, the dim is 3. The dim must be ODD.
     * */
    KernelMatrix(double *arr, const int dim);

    int getDim() const;

    double *getKernel() const;
};


#endif //PHOTOMAKERAPP_KERNELMATRIX_H
