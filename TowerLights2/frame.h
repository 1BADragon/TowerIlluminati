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
    void setFullGridPixelColor(int x, int y, QColor c);
    void setTowerGridPixel(int x, int y, QColor c);
    Pixel *FullGridPixel(int x, int y);
    Pixel *TowerGridPixel(int x, int y);
    void applyVector(int x, int y);

private:
    Pixel* fullGrid[20][12];
    Pixel* towerGrid[10][4];
    qint64 timeStamp;
};

#endif // FRAME_H
