//
// Created by tommaso on 22/04/20.
//

#ifndef PHOTOMAKERAPP_ABSTRACTPIXEL_H
#define PHOTOMAKERAPP_ABSTRACTPIXEL_H

#include <ostream>

class AbstractPixel {
public:
    virtual ~AbstractPixel();

    // out << pixel (cannot be virtual)
    friend std::ostream &operator<<(std::ostream &os, AbstractPixel &p);

    bool operator==(AbstractPixel const &p) const;

private:
    virtual std::ostream& toOutputStream(std::ostream &os) = 0;

    virtual bool isEqual(AbstractPixel const &p) const = 0;
};


#endif //PHOTOMAKERAPP_ABSTRACTPIXEL_H
