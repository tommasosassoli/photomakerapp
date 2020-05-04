//
// Created by tommaso on 18/04/20.
//

#ifndef PHOTOMAKERAPP_HSVPIXEL_H
#define PHOTOMAKERAPP_HSVPIXEL_H

#include "RGBPixel.h"
#include "AbstractPixel.h"

class RGBPixel;

class HSVPixel : public AbstractPixel{
public:
    /**
    * @param h: degrees (eg. 120 (°))
    * @param s: percentage (eg. 100 (%))
    * @param v: percentage (eg. 50 (%))*/
    explicit HSVPixel(double h = 0, double s = 0, double v = 0);

    explicit HSVPixel(const RGBPixel &p);

    RGBPixel toRGB();

    /**
     * @return degrees (between 0° and 360°)*/
    double getHue() const;

    /**
     * @param hue: degrees (between 0° and 360°)*/
    void setHue(double hue);

    /**
     * @return range between 0.0 and 1.0 */
    double getSaturation() const;

    /**
     * @param saturation: range between 0.0 and 1.0 */
    void setSaturation(double saturation);

    /**
     * @return range between 0.0 and 1.0 */
    double getValue() const;

    /**
     * @param saturation: range between 0.0 and 1.0 */
    void setValue(double value);

    bool isEqual(AbstractPixel const &p) const override;

    std::ostream& toOutputStream(std::ostream &os) override;

private:
    double hue;
    double saturation;
    double value;

    bool static checkval(double v1, double v2);
};


#endif //PHOTOMAKERAPP_HSVPIXEL_H
