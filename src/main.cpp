#include <fstream>
#include <iostream>
#include "core/Image.h"

int main() {
    std::string path = std::string(std::getenv("HOME")) + std::string("/Pictures/animal.ppm");
    std::ifstream imgFile(path);

    if(imgFile.is_open()){
        try {
            Image<HSVPixel> i;
            imgFile >> i;

            /*ImageProcessor imgProc(KernelTemplate::laplatian8, 9);
            Image sharpImg = imgProc.applyConvolution(i);*/

            std::string path2 = std::string(std::getenv("HOME")) + std::string("/Pictures/generated_animal.ppm");
            std::ofstream outFile(path2);
            outFile << i;

            outFile.close();
            imgFile.close();
        }catch(ImageException &e){
            std::cout << e.what() << "\nTerminated";
        }

    }
    return 0;
}
