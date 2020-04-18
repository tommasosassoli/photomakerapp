//
// Created by tommaso on 18/04/20.
//

#include "PixelUtil.h"

int PixelUtil::maxRGB(int r, int g, int b) {
    int max = r;
    if(g > max)
        max = g;
    if(b > max)
        max = b;
    return max;
}
