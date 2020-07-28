//
// Created by tommaso on 28/07/20.
//

#ifndef PHOTOMAKERAPP_FILEHANDLER_CPP
#define PHOTOMAKERAPP_FILEHANDLER_CPP

#include <QtCore/QFileInfo>
#include <QtGui/QImage>
#include <fstream>
#include "../model/Image.h"

namespace FileHandler {
    Image<> loadImageFromFile(std::string path) {   // file extension conversion provided
        bool isTmpPath = false;

        QFileInfo f(path.c_str());
        if(f.suffix() != "ppm") {
            QImage tmpImg(path.c_str());
            path = path + "_pma_temp.ppm";
            tmpImg.save(path.c_str());
            isTmpPath = true;
        }

        std::ifstream imgFile(path);

        if(imgFile.is_open()) {
            try {
                Image<> i;
                imgFile >> i;

                imgFile.close();

                if(isTmpPath) {
                    QFile file(path.c_str());
                    file.remove();
                }
                return i;
            } catch (ImageException &e) {
                throw runtime_error("Cannot open file");
            }
        }
    }

    void saveImageToFile(std::string path, Image<>* img) {  // file extension conversion provided
        bool isTmpPath = false;
        std::string origPath = path;

        QFileInfo f(path.c_str());
        if(f.suffix() != "ppm") {
            path = path + "_pma_temp_out.ppm";
            isTmpPath = true;
        }

        std::ofstream outFile(path);

        if(outFile.is_open()){
            if(img != nullptr) {
                outFile << *img;
                outFile.close();
            } else
                throw runtime_error("No image opened");
        } else
            throw runtime_error("Cannot save the file");

        if(isTmpPath) {
            QImage tmpImg(path.c_str());
            tmpImg.save(origPath.c_str());

            QFile file(path.c_str());
            file.remove();
        }
    }
}

#endif //PHOTOMAKERAPP_FILEHANDLER_CPP