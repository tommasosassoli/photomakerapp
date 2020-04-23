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

    bool operator==(const AbstractPixel& p) const;

    virtual bool isEqual(const AbstractPixel &p) const = 0;

private:
    virtual std::ostream& toOutputStream(std::ostream &os) = 0;
};


#endif //PHOTOMAKERAPP_ABSTRACTPIXEL_H
