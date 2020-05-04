//
// Created by tommaso on 20/03/20.
//

#ifndef IMAGEPARSER_PIXEL_H
#define IMAGEPARSER_PIXEL_H

#include <istream>
#include "HSVPixel.h"
#include "AbstractPixel.h"

class HSVPixel;

/**
 * Class that represent 3-channel pixel.
 * */
class RGBPixel : public AbstractPixel{
public:
    explicit RGBPixel(int R = 0, int G = 0, int B = 0);

    explicit RGBPixel(const HSVPixel &p);

    ~RGBPixel();

    HSVPixel toHSV();

    int getR() const;

    void setR(int r);

    int getG() const;

    void setG(int g);

    int getB() const;

    void setB(int b);

    bool isEqual(AbstractPixel const &p) const override;

    friend std::istream &operator>>(std::istream &is, RGBPixel &pixel);

    std::ostream& toOutputStream(std::ostream &os) override;

private:
    unsigned char R;
    unsigned char G;
    unsigned char B;
};


#endif //IMAGEPARSER_PIXEL_H
