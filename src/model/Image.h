//
// Created by tommaso on 20/03/20.
//

#ifndef IMAGEPARSER_IMAGE_H
#define IMAGEPARSER_IMAGE_H

#include <istream>
#include <sstream>
#include "../core/ImageException.h"
#include "RGBPixel.h"
#include "HSVPixel.h"

enum imgFormat {P3 = 3, P6 = 6};

template<typename TPixel = RGBPixel>
class Image {
    static_assert(std::is_base_of<AbstractPixel, TPixel>::value, "TPixel must extend AbstractPixel");
public:
    explicit Image(int width = 0, int height = 0){
        setWidth(width);
        setHeight(height);
    }

    Image(const Image& that) {// deep copy of the image
        format = that.format;
        setHeight(that.height);
        setWidth(that.width);
        TPixel *pixels = new TPixel[height * width];
        for(int i = 0; i < height * width; i++){
            pixels[i] = that.buffer[i];
        }
        buffer = pixels;
    }

    Image<TPixel>& operator=(Image<TPixel>&& other) {
        if(this != &other) {
            delete[] buffer;
            width = 0;
            height = 0;
            format = P3;

            format = other.format;
            width = other.width;
            height = other.height;
            buffer = other.buffer;

            other.format = P3;
            other.width = 0;
            other.height = 0;
            other.buffer = nullptr;
        }
        return *this;
    }

    Image<TPixel>* clone(){
        return new Image(*this);
    }

    Image<TPixel> cloneInfo() const{
        Image<TPixel> i(this->width, this->height);
        i.format = this->format;
        i.setBuffer(new TPixel[this->height * this->width]);
        return i;
    }

    ~Image(){
        if(buffer != nullptr)
            delete[] buffer;
    }

    template <typename T>
    Image<T> convert() const;

    int getWidth() const{
        return width;
    }

    int getHeight() const{
        return height;
    }

    TPixel *getBuffer() const{
        return buffer;
    }

    void setBuffer(TPixel *buffer){
        if(buffer != nullptr)
            Image::buffer = buffer;
    }

    bool operator==(const Image<TPixel>& p) const{
        if((this->getHeight() == p.getHeight()) &&
           (this->getWidth() == p.getWidth()) &&
           this->format == p.format){
            int eq = 0;
            TPixel* thisBuff = this->getBuffer();
            TPixel* pBuff = p.getBuffer();
            for(int i = 0; i < p.getHeight() * p.getWidth(); i++)
                if (thisBuff[i] == pBuff[i])
                    eq++;
            return (eq == p.getHeight() * p.getWidth());
        }else
            return false;
    }

    friend std::ostream &operator<<(std::ostream &os, const Image &image){
        os << "P" << image.format << "\n"
           << image.width << " "
           << image.height << "\n"
           << "255" << "\n";
        if (image.buffer != nullptr) {
            if (image.format == P3) {
                for (int i = 0; i < image.height; i++) {
                    for (int j = 0; j < image.width; j++)
                        os << image.buffer[i * image.width + j];
                    os << "\n";
                }
            } else {    //P6
                int buffSize = 3 * image.width * image.height;
                char *pixelData = new char[buffSize];

                for (int i = 0, j = 0; i < buffSize; i += 3, j++) {
                    pixelData[i] = image.buffer[j].getR();
                    pixelData[i + 1] = image.buffer[j].getG();
                    pixelData[i + 2] = image.buffer[j].getB();
                }

                os.write(pixelData, buffSize);
            }
        }
        return os;
    }

    friend std::istream &operator>>(std::istream &is, Image &image) {
        std::stringstream ss;
        preprocessStream(is, ss);
        std::string format;
        ss >> format;

        if (format == "P3" || format == "P6") {
            std::string h_s, w_s, maxVal_s;
            ss >> w_s >> h_s >> maxVal_s;

            image.width = std::stoi(w_s);
            image.height = std::stoi(h_s);
            int maxVal = std::stoi(maxVal_s);

            if ((image.height > 0) && (image.width > 0) && (maxVal > 0) && (maxVal <= 255)) {   //check image dimensions
                TPixel *pixels = new TPixel[image.width * image.height];      //pixel matrix

                if (format == "P3") {                     //check file format (.ppm)
                    image.format = P3;
                    for (int i = 0; i < image.width * image.height; i++) {
                        try {
                            pixels[i] = Image::getPixelFromStream(ss);
                        } catch (ImageException &e) {
                            delete[] pixels;
                            throw ImageException("File corrupted.");
                        }
                    }
                    image.buffer = pixels;   //store pixels array: END
                    return is;

                } else if (format == "P6") {
                    image.format = P6;
                    ss.ignore(2, '\n'); //ignore the \n after the maxVal

                    int buffSize = 3 * image.width * image.height;
                    char *pixelData = new char[buffSize];
                    ss.read(pixelData, buffSize);

                    unsigned char r, g, b;
                    for (int i = 0, j = 0; i < buffSize; i += 3, j++) {
                        r = pixelData[i];
                        g = pixelData[i + 1];
                        b = pixelData[i + 2];

                        pixels[j] = getPixelFromRGBValue(r, g, b);
                    }
                    image.buffer = pixels;   //store pixels array: END
                    delete[] pixelData;
                    return is;
                }
            }
            throw ImageException("File malformed.");
        }
        throw ImageException("File format not supported.");
    }

private:
    imgFormat format {P3};
    int width;
    int height;
    TPixel *buffer {nullptr};

    void setWidth(int width){
        if(width < 0)
            width = 0;
        Image::width = width;
    }

    void setHeight(int height){
        if(height < 0)
            height = 0;
        Image::height = height;
    }

    static void preprocessStream(std::istream& is, std::stringstream& os){
        char c;
        int endlNum = 0;
        while(!is.eof()) {
            c = is.get();
            if(endlNum < 3) {
                if (c == 35)
                    is.ignore(4095, '\n');
                else
                    os.put(c);

                if (c == 10)
                    endlNum++;
            } else
                os.put(c);
        }
    }

    static TPixel getPixelFromStream(std::istream& is);
    static TPixel getPixelFromRGBValue(unsigned char r, unsigned char g, unsigned char b);
};

template <>
inline HSVPixel Image<HSVPixel>::getPixelFromStream(std::istream& is){
    RGBPixel p;
    is >> p;
    if (!is.fail()){      //check fail case
        return p.toHSV();
    } else {
        throw ImageException("Pixel reading not possible.");
    }
}

template <>
inline RGBPixel Image<RGBPixel>::getPixelFromStream(std::istream& is){
    RGBPixel p;
    is >> p;
    if (!is.fail()){      //check fail case
        return p;
    } else {
        throw ImageException("Pixel reading not possible.");
    }
}

template<>
inline RGBPixel Image<RGBPixel>::getPixelFromRGBValue(unsigned char r, unsigned char g, unsigned char b) {
    return RGBPixel(r, g, b);
}

template<>
inline HSVPixel Image<HSVPixel>::getPixelFromRGBValue(unsigned char r, unsigned char g, unsigned char b) {
    return RGBPixel(r, g, b).toHSV();
}

template<> template <>
inline Image<HSVPixel> Image<RGBPixel>::convert() const {        //RGB -> HSV
    Image<HSVPixel> img(this->width, this->height);
    HSVPixel *pixels = new HSVPixel[height * width];
    if(this->buffer != nullptr) {
        for (int i = 0; i < height * width; i++) {
            pixels[i] = this->buffer[i].toHSV();
        }
        img.setBuffer(pixels);
    }
    return img;
}

template<> template <>
inline Image<RGBPixel> Image<HSVPixel>::convert() const {        //HSV -> RGB
    Image<RGBPixel> img(this->width, this->height);
    RGBPixel *pixels = new RGBPixel[height * width];
    if(this->buffer != nullptr) {
        for (int i = 0; i < height * width; i++) {
            pixels[i] = this->buffer[i].toRGB();
        }
        img.setBuffer(pixels);
    }
    return img;
}


#endif //IMAGEPARSER_IMAGE_H
