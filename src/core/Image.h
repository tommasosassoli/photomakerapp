//
// Created by tommaso on 20/03/20.
//

#ifndef IMAGEPARSER_IMAGE_H
#define IMAGEPARSER_IMAGE_H

#include <istream>
#include "ImageException.h"
#include "pixels/RGBPixel.h"

template<typename TPixel = RGBPixel>
class Image {
    static_assert(std::is_base_of<AbstractPixel, TPixel>::value, "TPixel must be extend AbstractPixel");
public:
    explicit Image(int width = 0, int height = 0){
        setWidth(width);
        setHeight(height);
    }

    Image(const Image& that){// deep copy of the image
        TPixel *pixels = new TPixel[height * width];
        for(int i = 0; i < height * width; i++){
            pixels[i] = that.buffer[i];
        }
        buffer = pixels;
    }

    Image* clone(){
        return new Image(*this);
    }

    ~Image(){
        delete[] buffer;
    }

    Image convert(){    //TODO check conversion
        if(std::is_same<TPixel, RGBPixel>::value) {
            Image<HSVPixel> img(this->width, this->height);
            HSVPixel *pixels = new HSVPixel[height * width];
            for(int i = 0; i < height * width; i++){
                pixels[i] = dynamic_cast<RGBPixel>(this->buffer[i]).toHSV();
            }
            img.setBuffer(pixels);
        } else if (std::is_same<TPixel, HSVPixel>::value){
            Image<RGBPixel> img(this->width, this->height);
            RGBPixel *pixels = new RGBPixel[height * width];
            for(int i = 0; i < height * width; i++){
                pixels[i] = dynamic_cast<HSVPixel>(this->buffer[i]).toRGB();
            }
            img.setBuffer(pixels);
        } else {
            throw ImageException("Conversion not valid.");
        }
    }

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

    bool isRGBImage(){
        return (std::is_same<TPixel, RGBPixel>::value);
    }

    bool operator==(const Image& p) const{
        if((this->getHeight() == p.getHeight()) &&
           (this->getWidth() == p.getWidth())){
            int eq = 0;
            for(int i = 0; i < p.getHeight() * p.getWidth(); i++)
                if (this->getBuffer()[i] == p.getBuffer()[i])
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

    friend std::istream &operator>>(std::istream &is, Image &image) throw (ImageException){
        std::string format;
        is >> format;
        if(format == "P3"){                     //check file format (.ppm)
            std::string h_s, w_s, maxVal_s;
            is >> w_s >> h_s >> maxVal_s;

            image.width = std::stoi(w_s);
            image.height = std::stoi(h_s);
            int maxVal = std::stoi(maxVal_s);

            if((image.height > 0) && (image.width > 0) && (maxVal > 0) && (maxVal <= 255)){      //check image dimensions
                RGBPixel *pixels = new RGBPixel[image.width * image.height];      //pixel matrix

                for(int i = 0; i < image.width * image.height; i++){
                    RGBPixel p;
                    is >> p;
                    if (!is.fail())      //check fail case
                        pixels[i] = p;
                    else {
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

    int reflect(const int m, const int x) const{
        if(x < 0)   return -x-1;
        if(x >= m)  return 2*m-x-1;
    }

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
};

#endif //IMAGEPARSER_IMAGE_H
