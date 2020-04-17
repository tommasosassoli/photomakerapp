#include <fstream>
#include <iostream>
#include <string>
#include "core/Image.h"
#include "core/ImageProcessor.h"
#include "core/KernelTemplate.h"

int main() {
    std::string path = std::string(std::getenv("HOME")) + std::string("/Pictures/procione.ppm");
    std::ifstream imgFile(path);

    if(imgFile.is_open()){
        try {
            Image i;
            imgFile >> i;

            ImageProcessor imgProc(KernelTemplate::laplatian8, 9);
            Image sharpImg = imgProc.applyConvolution(i);

            std::string path2 = std::string(std::getenv("HOME")) + std::string("/Pictures/generated_procione.ppm");
            std::ofstream outSharpFile(path2);
            outSharpFile << sharpImg;
            outSharpFile.close();

            imgFile.close();
        }catch(ImageException &e){
            cout << e.what() << "\nTerminated";
        }

    }
    return 0;
}
