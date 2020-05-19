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

template<typename TPixel = RGBPixel>
class Image {
    static_assert(std::is_base_of<AbstractPixel, TPixel>::value, "TPixel must be extend AbstractPixel");
public:
    explicit Image(int width = 0, int height = 0){
        setWidth(width);
        setHeight(height);
    }

    Image(const Image& that) {// deep copy of the image
        setHeight(that.height);
        setWidth(that.width);
        TPixel *pixels = new TPixel[height * width];
        for(int i = 0; i < height * width; i++){
            pixels[i] = that.buffer[i];
        }
        buffer = pixels;
    }

    Image<TPixel>* clone(){
        return new Image(*this);
    }

    Image<TPixel> cloneInfo() const{
        Image<TPixel> i(this->width, this->height);
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
           (this->getWidth() == p.getWidth())){
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
        os << image.format << "\n"
           << image.width << " "
           << image.height << "\n"
           << "255" << "\n";
        if (image.buffer != nullptr) {
            for (int i = 0; i < image.height; i++) {
                for (int j = 0; j < image.width; j++)
                    os << image.buffer[i * image.width + j];
                os << "\n";
            }
        }
        return os;
    }

    friend std::istream &operator>>(std::istream &is, Image &image) {
        std::stringstream ss;
        preprocessStream(is, ss);
        std::string format;
        ss >> format;
        if (format == "P3") {                     //check file format (.ppm)
            std::string h_s, w_s, maxVal_s;
            ss >> w_s >> h_s >> maxVal_s;

            image.width = std::stoi(w_s);
            image.height = std::stoi(h_s);
            int maxVal = std::stoi(maxVal_s);

            if ((image.height > 0) && (image.width > 0) && (maxVal > 0) && (maxVal <= 255)) {   //check image dimensions
                TPixel *pixels = new TPixel[image.width * image.height];      //pixel matrix

                for (int i = 0; i < image.width * image.height; i++) {
                    try{
                        pixels[i] = Image::getPixelFromStream(ss);
                    } catch (ImageException &e){
                        delete[] pixels;
                        throw ImageException("File corrupted.");
                    }
                }
                image.buffer = pixels;   //store pixels array: END
                return is;
            }
            throw ImageException("File malformed.");
        }
        throw ImageException("File format not supported.");
    }

private:
    const std::string format {"P3"};
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
        while(!is.eof()){
            c = is.get();
            if(c == 35)
                is.ignore(4095, '\n');
            else
                os.put(c);
        }
    }

    static TPixel getPixelFromStream(std::istream& is);
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
