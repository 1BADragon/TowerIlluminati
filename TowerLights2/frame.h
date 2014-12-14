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
    Pixel ** grid;
    qint64 timeStamp;
};

#endif // FRAME_H
