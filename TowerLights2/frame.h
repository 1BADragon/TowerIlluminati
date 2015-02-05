#ifndef FRAME_H
#define FRAME_H

#include "pixel.h"
#include <QtGlobal>

class Frame
{
public:
    Frame();

private:
    Pixel ** fullGrid;
    Pixel ** towergrid;
    qint64 timeStamp;
};

#endif // FRAME_H
