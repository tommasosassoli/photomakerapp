//
// Created by tommaso on 20/03/20.
//

#include "Image.h"
#include "ImageException.h"

Image::Image(int width, int height, int maxVal) : width(width), height(height), maxVal(maxVal){
    Image::buffer = nullptr;
}

/// Perform the deep copy of the image
Image::Image(const Image &that) : Image(that.width, that.height, that.maxVal){
    // deep copy of the image
    Pixel **pixels = new Pixel*[height];
    for(int j = 0; j < height; j++){
        pixels[j] = new Pixel[width];
    }
    for(int i = 0; i < height; i++){
        for(int j = 0; j < width; j++){
            pixels[i][j] = that.buffer[i][j];
        }
    }

    buffer = pixels;
}

Image::~Image() {
    if( buffer != nullptr) {
        for (int i = 0; i < this->height; i++)
            delete[] buffer[i];
        delete[] buffer;
    }
}

int Image::getWidth() const {
    return width;
}

void Image::setWidth(int width) {
    Image::width = width;
}

int Image::getHeight() const {
    return height;
}

void Image::setHeight(int height) {
    Image::height = height;
}

int Image::getMaxVal() const {
    return maxVal;
}

void Image::setMaxVal(int maxVal) {
    Image::maxVal = maxVal;
}

Pixel **Image::getBuffer() const {
    return buffer;
}

void Image::setBuffer(Pixel **buffer) {
    Image::buffer = buffer;
}

PixelMatrix Image::getSubMatrix(const int x, const int y) const {
    PixelMatrix pm;
    int dev = pm.getDimension() / 2;
    for(int i = -dev; i <= dev; i++)
        for(int j = -dev; j <= dev; j++)
            pm.set(i+dev, j+dev, &buffer[reflect(height, x + i)][reflect(width, y + j)]);
    return pm;
}

int Image::reflect(const int m, const int x) const{
    if(x < 0)   return -x-1;
    if(x >= m)  return 2*m-x-1;
}


void Image::validatePixel(Pixel &p) {
    if(p.getR() < 0)        p.setR(0);
    if(p.getG() < 0)        p.setG(0);
    if(p.getB() < 0)        p.setB(0);
    if(p.getR() > maxVal)   p.setR(maxVal);
    if(p.getG() > maxVal)   p.setG(maxVal);
    if(p.getB() > maxVal)   p.setB(maxVal);
    //return p;
}

std::string Image::toString() {
    std::string str;
    str = "width: " + std::to_string(this->width) +
    " height: " + std::to_string(this->height) +
    " maxVal: " + std::to_string(this->maxVal) + " buffer: ";
    for(int i = 0; i < this->height; i++) {
        str += "\n";
        for(int j = 0; j < this->width; j++)
            str += this->buffer[i][j].toString() + "  ";
    }
    return str;
}

std::ostream &operator<<(std::ostream &os, const Image &image) {
    os << image.format << "\n"
       << image.width << " "
       << image.height << "\n"
       << image.maxVal << "\n";
    if (image.buffer != nullptr) {
        for (int i = 0; i < image.height; i++) {
            for (int j = 0; j < image.width; j++)
                os << image.buffer[i][j] << " ";
            os << "\n";
        }
    }
    return os;
}

std::istream &operator>>(std::istream &is, Image &image) throw(ImageException){
    std::string format;
    is >> format;
    if(format == "P3"){                                     //check file format (.ppm)
        std::string h_s, w_s, maxVal_s;
        is >> w_s >> h_s >> maxVal_s;

        image.width = std::stoi(w_s);
        image.height = std::stoi(h_s);
        image.maxVal = std::stoi(maxVal_s);

        if((image.height > 0) && (image.width > 0) && (image.maxVal > 0)){      //check image dimensions
            Pixel **pixels = new Pixel*[image.height];      //pixel matrix
            for(int j = 0; j < image.height; j++){
                pixels[j] = new Pixel[image.width];
            }

            for(int i = 0; i < image.height; i++){          //pixel reading
                for(int j = 0; j < image.width; j++){
                    Pixel p;
                    is >> p;
                    if (!is.fail())                         //check fail case
                        pixels[i][j] = p;
                    else {
                        for(int k = 0; k < image.height; k++)
                            delete[] pixels[i];
                        delete[] pixels;
                        throw ImageException("File corrupted.");
                    }
                }
            }
            image.buffer = pixels;                      //store pixels array: END
            return is;
        }
        throw ImageException("File malformed.");
    }
    throw ImageException("File format not supported.");
}

Image &Image::operator=(const Image &that) {
    width = that.width;
    height = that.height;
    maxVal = that.maxVal;

    // deep copy of the image
    Pixel **pixels = new Pixel*[height];
    for(int j = 0; j < height; j++){
        pixels[j] = new Pixel[width];
    }
    for(int i = 0; i < height; i++){
        for(int j = 0; j < width; j++){
            pixels[i][j] = that.buffer[i][j];
        }
    }

    buffer = pixels;
    return *this;
}

bool operator==(const Image &p1, const Image &p2) {
    if((p1.getHeight() == p2.getHeight()) &&
    (p1.getWidth() == p2.getWidth()) &&
    (p1.getMaxVal() == p2.getMaxVal())){
        int eq = 0;
        for(int i = 0; i < p1.getHeight(); i++)
            for(int j = 0; j < p1.getWidth(); j++) {
                if (p1.getBuffer()[i][j] == p2.getBuffer()[i][j])
                    eq++;
            }
        return (eq == p1.getHeight()*p1.getWidth());
    }else
        return false;
}
