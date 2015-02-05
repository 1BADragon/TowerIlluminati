#ifndef FRAME_H
#define FRAME_H

#include "pixel.h"
#include <QtGlobal>

#define FULLGRIDWIDTH 12
#define FULLGRIDHEIGHT 20
#define TOWERWIDTH 4
#define TOWERHEIGHT 10

class Frame
{
public:
    Frame();
    Frame( const Frame& original);
    void setTimeStamp(qint64 time);
    qint64 getTimeStamp();
    void setPixel(int x, int y, QColor c);
    Pixel *getPixel(int x, int y);

private:
    Pixel* fullGrid[12][20];
    Pixel* towerGrid[4][10];
    qint64 timeStamp;
};

#endif // FRAME_H
