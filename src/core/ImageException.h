//
// Created by tommaso on 23/03/20.
//

#ifndef IMAGEPARSER_IMAGEEXCEPTION_H
#define IMAGEPARSER_IMAGEEXCEPTION_H

#include <string>
#include <stdexcept>

using namespace std;

class ImageException : public runtime_error {
public:
    ImageException(const string &message = "") : runtime_error(message.c_str()) {}
};


#endif //IMAGEPARSER_IMAGEEXCEPTION_H
